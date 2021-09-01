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



set(SPRDVanillaRendererIncludeDirectories
	${SharedDir}
	${SPDir}
	"${SPDir}/rd-vanilla"
	"${GSLIncludeDirectory}"
	)

# Defines
set(SPRDVanillaDefines ${SharedDefines} "RENDERER" "_JK2EXE" "JK2_MODE")

# Modular Renderer crap (let's hope this works..)

# Files



# Transparently use either bundled or system jpeg.
list(APPEND SPRDVanillaRendererIncludeDirectories ${JPEG_INCLUDE_DIR})
list(APPEND SPRDVanillaRendererLibraries          ${JPEG_LIBRARIES})

# Transparently use either bundled or system libpng.  Order is important --
# libpng used zlib, so it must come before it on the linker command line.
list(APPEND SPRDVanillaRendererIncludeDirectories ${PNG_INCLUDE_DIRS})
list(APPEND SPRDVanillaRendererLibraries          ${PNG_LIBRARIES})

# Transparently use either bundled or system zlib.
list(APPEND SPRDVanillaRendererIncludeDirectories ${ZLIB_INCLUDE_DIR})
list(APPEND SPRDVanillaRendererLibraries          ${ZLIB_LIBRARIES})

# Transparently use our bundled minizip.
list(APPEND SPRDVanillaRendererIncludeDirectories ${MINIZIP_INCLUDE_DIRS})
list(APPEND SPRDVanillaRendererLibraries          ${MINIZIP_LIBRARIES})

# Transparantly make use of all renderer directories
list(APPEND SPRDVanillaRendererIncludeDirectories "${SPDir}/rd-common")
list(APPEND SPRDVanillaRendererIncludeDirectories "${SPDir}/rd-vanilla")

set(SPRDVanillaRendererIncludeDirectories ${SPRDVanillaRendererIncludeDirectories} ${OPENGL_INCLUDE_DIR})
set(SPRDVanillaRendererLibraries ${SPRDVanillaRendererLibraries} ${OPENGL_LIBRARIES})

set(SPRDVanillaRendererIncludeDirectories ${SPRDVanillaRendererIncludeDirectories} ${OpenJKLibDir})

# Misc files
set(SPRDVanillaCommonFiles
	"${SPDir}/qcommon/matcomp.cpp"
	"${SPDir}/qcommon/q_shared.cpp"
	"${SPDir}/qcommon/q_shared.h"
	"${SPDir}/qcommon/ojk_i_saved_game.h"
	"${SPDir}/qcommon/ojk_saved_game_class_archivers.h"
	"${SPDir}/qcommon/ojk_saved_game_helper.h"
	"${SPDir}/qcommon/ojk_saved_game_helper_fwd.h"
	"${SPDir}/qcommon/ojk_scope_guard.h"
		${SharedCommonFiles}
	)
source_group("common" FILES ${SPRDVanillaCommonFiles})
set(SPRDVanillaFiles ${SPRDVanillaFiles} ${SPRDVanillaCommonFiles})

# Misc files
set(SPRDVanillaCommonSafeFiles
		${SharedCommonSafeFiles}

	)
source_group("common/safe" FILES ${SPRDVanillaCommonSafeFiles})
set(SPRDVanillaFiles ${SPRDVanillaFiles} ${SPRDVanillaCommonSafeFiles})


# GHOUL 2
add_library(SPRDVanillaG2 	"${SPDir}/rd-vanilla/G2_API.cpp"
							"${SPDir}/rd-vanilla/G2_bolts.cpp"
							"${SPDir}/rd-vanilla/G2_bones.cpp"
							"${SPDir}/rd-vanilla/G2_misc.cpp"
							"${SPDir}/rd-vanilla/G2_surfaces.cpp")

set_target_properties(SPRDVanillaG2 PROPERTIES COMPILE_DEFINITIONS "${SPRDVanillaDefines}")
set_target_properties(SPRDVanillaG2 PROPERTIES INCLUDE_DIRECTORIES "${SPRDVanillaRendererIncludeDirectories}")



add_library(SPRDVanillaRenderer	"${SPDir}/rd-vanilla/tr_arb.cpp"
								"${SPDir}/rd-vanilla/tr_backend.cpp"
								"${SPDir}/rd-vanilla/tr_bsp.cpp"
								"${SPDir}/rd-vanilla/tr_cmds.cpp"
								"${SPDir}/rd-vanilla/tr_curve.cpp"
								"${SPDir}/rd-vanilla/tr_draw.cpp"
								"${SPDir}/rd-vanilla/tr_ghoul2.cpp"
								"${SPDir}/rd-vanilla/tr_image.cpp"
								"${SPDir}/rd-vanilla/tr_init.cpp"
								"${SPDir}/rd-vanilla/tr_light.cpp"
								"${SPDir}/rd-vanilla/tr_main.cpp"
								"${SPDir}/rd-vanilla/tr_marks.cpp"
								"${SPDir}/rd-vanilla/tr_mesh.cpp"
								"${SPDir}/rd-vanilla/tr_model.cpp"
								"${SPDir}/rd-vanilla/tr_quicksprite.cpp"
								"${SPDir}/rd-vanilla/tr_scene.cpp"
								"${SPDir}/rd-vanilla/tr_shade.cpp"
								"${SPDir}/rd-vanilla/tr_shade_calc.cpp"
								"${SPDir}/rd-vanilla/tr_shader.cpp"
								"${SPDir}/rd-vanilla/tr_shadows.cpp"
								"${SPDir}/rd-vanilla/tr_skin.cpp"
								"${SPDir}/rd-vanilla/tr_sky.cpp"
								"${SPDir}/rd-vanilla/tr_stl.cpp"
								"${SPDir}/rd-vanilla/tr_subs.cpp"
								"${SPDir}/rd-vanilla/tr_surface.cpp"
								"${SPDir}/rd-vanilla/tr_surfacesprites.cpp"
								"${SPDir}/rd-vanilla/tr_world.cpp"
								"${SPDir}/rd-vanilla/tr_WorldEffects.cpp")

set_target_properties(SPRDVanillaRenderer PROPERTIES COMPILE_DEFINITIONS "${SPRDVanillaDefines}")
set_target_properties(SPRDVanillaRenderer PROPERTIES INCLUDE_DIRECTORIES "${SPRDVanillaRendererIncludeDirectories}")



add_library(SPRDCommon 	"${SPDir}/rd-common/tr_font.cpp"
						"${SPDir}/rd-common/tr_image_load.cpp"
						"${SPDir}/rd-common/tr_image_jpg.cpp"
						"${SPDir}/rd-common/tr_image_tga.cpp"
						"${SPDir}/rd-common/tr_image_png.cpp"
						"${SPDir}/rd-common/tr_noise.cpp")

set_target_properties(SPRDCommon PROPERTIES COMPILE_DEFINITIONS "${SPRDVanillaDefines}")
set_target_properties(SPRDCommon PROPERTIES INCLUDE_DIRECTORIES "${SPRDVanillaRendererIncludeDirectories}")




add_library(${JK2SPVanillaRenderer} SHARED ${SPRDVanillaFiles})
if(NOT MSVC)
	# remove "lib" prefix for .so/.dylib files
	set_target_properties(${JK2SPVanillaRenderer} PROPERTIES PREFIX "")
endif()

if(WIN32)
	install(TARGETS ${JK2SPVanillaRenderer}
		RUNTIME
		DESTINATION ${JK2InstallDir}
		COMPONENT ${JK2SPClientComponent})
else(WIN32)
	if(MakeApplicationBundles AND BuildJK2SPEngine)
		install(TARGETS ${JK2SPVanillaRenderer}
			LIBRARY
			DESTINATION "${JK2InstallDir}/${JK2SPEngine}.app/Contents/MacOS/"
			COMPONENT ${JK2SPClientComponent})
	else()
		install(TARGETS ${JK2SPVanillaRenderer}
			LIBRARY
			DESTINATION ${JK2InstallDir}
			COMPONENT ${JK2SPClientComponent})
	endif()
endif()


set_target_properties(${JK2SPVanillaRenderer} PROPERTIES COMPILE_DEFINITIONS "${SPRDVanillaDefines}")

# Hide symbols not explicitly marked public.
set_property(TARGET ${JK2SPVanillaRenderer} APPEND PROPERTY COMPILE_OPTIONS ${OPENJK_VISIBILITY_FLAGS})

set_target_properties(${JK2SPVanillaRenderer} PROPERTIES INCLUDE_DIRECTORIES "${SPRDVanillaRendererIncludeDirectories}")
set_target_properties(${JK2SPVanillaRenderer} PROPERTIES PROJECT_LABEL "JK2 SP Vanilla Renderer")

target_link_libraries(${JK2SPVanillaRenderer}
						${SPRDVanillaRendererLibraries}
						SPRDCommon
						SPRDVanillaRenderer
						SPRDVanillaG2)
