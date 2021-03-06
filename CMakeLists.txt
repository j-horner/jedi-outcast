#============================================================================
# Copyright (C) 2013 - 2018, OpenJK contributors
# 
# This file is part of the OpenJK source code.
# 
# OpenJK is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.
#============================================================================

cmake_minimum_required(VERSION 3.20.3)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")

set(ProjectName "JediOutcast" CACHE STRING "Project Name")
project(${ProjectName})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

cmake_path(SET CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
message("CMAKE_INSTALL_PREFIX: " ${CMAKE_INSTALL_PREFIX})

#=============================================================================
#
# Customizable options
#
#=============================================================================
option(BuildPortableVersion "Build portable version (does not read or write files from your user/home directory" OFF)

option(BuildJK2SPEngine "Whether to create projects for the jk2 SP engine (openjo_sp.exe)" ON)
option(BuildJK2SPGame "Whether to create projects for the jk2 sp gamecode mod (jk2gamex86.dll)" ON)
option(BuildJK2SPRdVanilla "Whether to create projects for the jk2 sp renderer (rdjosp-vanilla_x86.dll)" ON)


# Configure the use of bundled libraries.  By default, we assume the user is on
# a platform that does not require any bundling.
#
# Note that we always use the bundled copy of minizip, since it is modified to
# use Z_Malloc.

set(UseInternalOpenALDefault OFF)
set(UseInternalZlibDefault   OFF)
set(UseInternalPNGDefault    OFF)
set(UseInternalJPEGDefault   OFF)
set(UseInternalSDL2Default   OFF)

if(WIN32)
  set(UseInternalOpenALDefault ON)
  set(UseInternalZlibDefault   ON)
  set(UseInternalPNGDefault    ON)
  set(UseInternalJPEGDefault   ON)
  set(UseInternalSDL2Default   ON)
endif()

if(APPLE)
  set(UseInternalJPEGDefault ON)
endif()

option(UseInternalOpenAL "If set, use bundled OpenAL."  ${UseInternalOpenALDefault})
option(UseInternalZlib   "If set, use bundled zlib."    ${UseInternalZlibDefault})
option(UseInternalPNG    "If set, use bundled libpng."  ${UseInternalPNGDefault})
option(UseInternalJPEG   "If set, use bundled libjpeg." ${UseInternalJPEGDefault})
option(UseInternalSDL2   "If set, use bundled SDL2."    ${UseInternalSDL2Default})

# This option won't appear on non-Apple platforms.
if(APPLE)
  option(MakeApplicationBundles "Whether to build .app application bundles for engines built" ON)
endif()

#=============================================================================
#
# Custom CMake Modules needed
#
#=============================================================================
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/cmake/Modules")

#=============================================================================
#
# Architecture/OS defines
#
#=============================================================================
# ${Architecture} must match ARCH_STRING in q_platform.h,
# and is used in DLL names (jagamex86.dll, jagamex86.dylib, jagamei386.so).
if(WIN32)
	set(X86 ON)
	if(CMAKE_SIZEOF_VOID_P MATCHES "8")
		set(Architecture "x86_64")
		set(WIN64 TRUE)
	else()
		set(Architecture "x86")
		set(WIN64 FALSE)
	endif()
else()
	set(X86 OFF)
	if(CMAKE_SYSTEM_PROCESSOR MATCHES "^arm")
		set(Architecture "arm")
	elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^i.86$")
		set(X86 ON)
		if(APPLE)
			set(Architecture "x86")
		else()
			# e.g. Linux
			set(Architecture "i386")
		endif()
	elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^x86.64$")
		set(X86 ON)
		set(Architecture "x86_64")
	elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "powerpc")
		set(Architecture "ppc")
	elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "powerpc64")
		set(Architecture "ppc64")
	else()
		set(Architecture "${CMAKE_SYSTEM_PROCESSOR}")
	endif()
endif()

message(STATUS "Architecture is ${Architecture}")

#=============================================================================
#
# Binary names
#
#=============================================================================
set(JK2SPEngine "openjo_sp.${Architecture}")
set(JK2SPGame "jospgame${Architecture}")
set(JK2SPVanillaRenderer "rdjosp-vanilla_${Architecture}")


#=============================================================================
#
# Paths
#
#=============================================================================
set(SPDir "${CMAKE_SOURCE_DIR}/code")
set(JK2SPDir "${CMAKE_SOURCE_DIR}/codeJK2")
set(SharedDir ${CMAKE_SOURCE_DIR}/shared)
set(OpenJKLibDir "${CMAKE_SOURCE_DIR}/lib")

find_package(OpenGL REQUIRED)

find_package(gsl-lite CONFIG REQUIRED)
# target_link_libraries(main PRIVATE gsl::gsl-lite gsl::gsl-lite-v0 gsl::gsl-lite-v1)

set(GSLIncludeDirectory "${CMAKE_SOURCE_DIR}/external/vcpkg/packages/gsl-lite_x86-windows/include")

# set(GSLIncludeDirectory "${OpenJKLibDir}/gsl-lite/include")

include(InstallConfig)

#=============================================================================
#
# Compiler definitions/flags
#
#=============================================================================

# Operating system settings
if(WIN64)
	add_compile_definitions(WIN64)
endif()

if (APPLE)
	add_compile_definitions(MACOS_X)
endif()

if (NOT WIN32 AND NOT APPLE)
	add_compile_definitions(ARCH_STRING=${Architecture})
endif()

if(CMAKE_SYSTEM_NAME MATCHES "BSD")
	add_compile_definitions(IOAPI_NO_64)
endif()

set(CMAKE_CXX_STANDARD 20)

# Compiler settings
if(MSVC)
	add_compile_definitions(NOMINMAX _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE)

	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /arch:SSE2")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /DEBUG")

	# We don't try to control symbol visibility under MSVC.
	set(OPENJK_VISIBILITY_FLAGS "")
elseif (("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU") OR ("${CMAKE_C_COMPILER_ID}" MATCHES "Clang"))
	# I hope this doesn't come back to bite me in the butt later on.
	# Realistically though, can the C and CXX compilers be different?

	# Visibility can't be set project-wide -- it needs to be specified on a
	# per-target basis.  This is primarily due to the bundled copy of ZLib.
	# ZLib explicitly declares symbols hidden, rather than defaulting to hidden.
	#
	# Note that -fvisibility=hidden is stronger than -fvisibility-inlines-hidden.
	set(OPENJK_VISIBILITY_FLAGS "-fvisibility=hidden")

	# removes the -rdynamic flag at linking (which causes crashes for some reason)
	set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

	# additional flags for debug configuration
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb")

	if (X86)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse2")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
	endif()

	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
	
	if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-comment")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsigned-char")
		if (X86)
			# "x86 vm will crash without -mstackrealign since MMX
			# instructions will be used no matter what and they
			# corrupt the frame pointer in VM calls"
			# -ioquake3 Makefile
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mstackrealign")
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpmath=sse")
		endif()

		if(WIN32)
			# Link libgcc and libstdc++ statically
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")
		endif()
	elseif("${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-comment")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsigned-char")
	endif()

	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comment")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsigned-char")
		if (X86)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mstackrealign")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpmath=sse")
		endif()
	elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
		#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-writable-strings")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comment")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsigned-char")
	endif()
else()
	message(ERROR "Unsupported compiler")
endif()

add_compile_definitions($<$<CONFIG:Debug>:_DEBUG>)
add_compile_definitions($<$<NOT:$<CONFIG:Debug>>:FINAL_BUILD>)

if(BuildPortableVersion)
	set(BUILD_PORTABLE ON)
endif()

#=============================================================================
#
# Generate version file
#
#=============================================================================

# Reproducible builds
# https://reproducible-builds.org/specs/source-date-epoch/
if ("$ENV{SOURCE_DATE_EPOCH}" STREQUAL "")
	message(STATUS "SOURCE_DATE_EPOCH is not set: SOURCE_DATE will be set to the compile-time date")
else()
	execute_process(
		COMMAND "date" "--date=@$ENV{SOURCE_DATE_EPOCH}" "+%b %_d %Y"
		OUTPUT_VARIABLE SOURCE_DATE
		ERROR_QUIET
		OUTPUT_STRIP_TRAILING_WHITESPACE)
	message(STATUS "SOURCE_DATE_EPOCH is set ($ENV{SOURCE_DATE_EPOCH}): SOURCE_DATE set to \"${SOURCE_DATE}\"")
endif()

# Current Git SHA1 hash
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_HASH)
message(STATUS "Git revision is ${GIT_HASH}")

configure_file(shared/qcommon/q_version.h.in shared/qcommon/q_version.h @ONLY)


#=============================================================================
#
# Adding all of the projects
#
#=============================================================================
if(UseInternalJPEG)
  add_subdirectory(lib/jpeg-9a)
else()
  find_package(JPEG REQUIRED)
endif()

# works, but when game is launched, missing zlibd1.dll
# find_package(ZLIB REQUIRED)
if(UseInternalZlib)
  add_subdirectory(lib/zlib)
else()
  find_package(ZLIB REQUIRED)
endif()

if(UseInternalPNG)
  add_subdirectory(lib/libpng)
else()
  find_package(PNG REQUIRED)
endif()

# Always use bundled minizip (sets MINIZIP_{LIBRARIES,INCLUDE_DIR})
add_subdirectory(lib/minizip)

# Add projects
add_subdirectory(${SPDir})		# NOTE: Certain parts needed to build JK2 are specified in ${SPDir}, not ${JK2SPDir}...
if(BuildJK2SPGame)
	add_subdirectory("${JK2SPDir}/game")
endif()
