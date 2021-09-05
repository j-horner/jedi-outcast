/*
===========================================================================
Copyright (C) 1999 - 2005, Id Software, Inc.
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
Copyright (C) 2013 - 2015, OpenJK contributors

This file is part of the OpenJK source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

// Filename:-	weapons.h
//
// Note that this is now included from both server and game modules, so don't include any other header files
//	within this one that might break stuff...

#pragma once

#include "../qcommon/q_shared.h"

enum class weapon_t
{
	WP_NONE,

	// Player weapons
	WP_SABER,			// player and NPC weapon
	WP_BLASTER_PISTOL,	// player and NPC weapon
	WP_BLASTER,			// player and NPC weapon
	WP_DISRUPTOR,		// player and NPC weapon
	WP_BOWCASTER,		// NPC weapon - player can pick this up, but never starts with them
	WP_REPEATER,		// NPC weapon - player can pick this up, but never starts with them
	WP_DEMP2,			// NPC weapon - player can pick this up, but never starts with them
	WP_FLECHETTE,		// NPC weapon - player can pick this up, but never starts with them
	WP_ROCKET_LAUNCHER,	// NPC weapon - player can pick this up, but never starts with them
	WP_THERMAL,			// player and NPC weapon
	WP_TRIP_MINE,		// NPC weapon - player can pick this up, but never starts with them
	WP_DET_PACK,		// NPC weapon - player can pick this up, but never starts with them
	WP_CONCUSSION,		// NPC weapon - player can pick this up, but never starts with them

	//extras
	WP_MELEE,			// player and NPC weapon - Any ol' melee attack

	//when in atst
	WP_ATST_MAIN,
	WP_ATST_SIDE,

	// These can never be gotten directly by the player
	WP_STUN_BATON,		// stupid weapon, should remove

	//NPC weapons
	WP_BRYAR_PISTOL,	// NPC weapon - player can pick this up, but never starts with them

	WP_EMPLACED_GUN,

	WP_BOT_LASER,		// Probe droid	- Laser blast

	WP_TURRET,			// turret guns

	WP_TIE_FIGHTER,

	WP_RAPID_FIRE_CONC,

	WP_JAWA,
	WP_TUSKEN_RIFLE,
	WP_TUSKEN_STAFF,
	WP_SCEPTER,
	WP_NOGHRI_STICK,

	//# #eol
	WP_NUM_WEAPONS
};

constexpr static auto WP_NUM_WEAPONS = static_cast<int>(weapon_t::WP_NUM_WEAPONS);

// AMMO_NONE must be first and AMMO_MAX must be last, cause weapon load validates based off of these vals
enum class ammo_t
{
	AMMO_NONE,
	AMMO_FORCE,		// AMMO_PHASER
	AMMO_BLASTER,	// AMMO_STARFLEET,
	AMMO_POWERCELL,	// AMMO_ALIEN,
	AMMO_METAL_BOLTS,
	AMMO_ROCKETS,
	AMMO_EMPLACED,
	AMMO_THERMAL,
	AMMO_TRIPMINE,
	AMMO_DETPACK,
	AMMO_MAX
};

constexpr static auto AMMO_MAX = static_cast<int>(ammo_t::AMMO_MAX);

struct weaponData_s {
	char	classname[32];		// Spawning name
	char	weaponMdl[64];		// Weapon Model
	char	firingSnd[64];		// Sound made when fired
	char	altFiringSnd[64];	// Sound made when alt-fired

	char	stopSnd[64];		// Sound made when weapon stops firing
	char	chargeSnd[64];		// sound to start when the weapon initiates the charging sequence
	char	altChargeSnd[64];	// alt sound to start when the weapon initiates the charging sequence
	char	selectSnd[64];		// the sound to play when this weapon gets selected

	int		ammoIndex;			// Index to proper ammo slot
	int		ammoLow;			// Count when ammo is low

	int		energyPerShot;		// Amount of energy used per shot
	int		fireTime;			// Amount of time between firings
	int		range;				// Range of weapon

	int		altEnergyPerShot;	// Amount of energy used for alt-fire
	int		altFireTime;		// Amount of time between alt-firings
	int		altRange;			// Range of alt-fire

	char	weaponIcon[64];		// Name of weapon icon file
	int		numBarrels;			// how many barrels should we expect for this weapon?

	char	missileMdl[64];		// Missile Model
	char	missileSound[64];	// Missile flight sound
	float  	missileDlight;		// what is says
	vec3_t 	missileDlightColor;	// ditto

	char	alt_missileMdl[64];		// Missile Model
	char	alt_missileSound[64];	// Missile sound
	float  	alt_missileDlight;		// what is says
	vec3_t 	alt_missileDlightColor;	// ditto

	char	missileHitSound[64];	// Missile impact sound
	char	altmissileHitSound[64];	// alt Missile impact sound
	void	*func;
	void	*altfunc;

	char	mMuzzleEffect[64];
	int		mMuzzleEffectID;
	char	mAltMuzzleEffect[64];
	int		mAltMuzzleEffectID;

	int		damage;
	int		altDamage;
	int		splashDamage;
	int		altSplashDamage;
	float	splashRadius;
	float	altSplashRadius;
};


struct ammoData_s
{
	char	icon[64];	// Name of ammo icon file
	int		max;		// Max amount player can hold of ammo
};

// Bryar Pistol
//--------
constexpr static auto BRYAR_PISTOL_VEL = 1800;
constexpr static auto BRYAR_PISTOL_DAMAGE = 14;
constexpr static auto BRYAR_CHARGE_UNIT = 200.0f;	// bryar charging gives us one more unit every 200ms--if you change this, you'll have to do the same in bg_pmove

// E11 Blaster
//---------
constexpr static auto BLASTER_MAIN_SPREAD = 0.5f;
constexpr static auto BLASTER_ALT_SPREAD = 1.5f;
constexpr static auto BLASTER_NPC_SPREAD = 0.5f;
constexpr static auto BLASTER_VELOCITY = 2300;
constexpr static auto BLASTER_NPC_VEL_CUT = 0.5f;
constexpr static auto BLASTER_NPC_HARD_VEL_CUT = 0.7f;
constexpr static auto BLASTER_DAMAGE = 20;
constexpr static auto BLASTER_NPC_DAMAGE_EASY = 6;
constexpr static auto BLASTER_NPC_DAMAGE_NORMAL = 12; // 14
constexpr static auto BLASTER_NPC_DAMAGE_HARD = 16; // 18

// Tenloss Disruptor
//----------
constexpr static auto  DISRUPTOR_MAIN_DAMAGE = 14;
constexpr static auto  DISRUPTOR_NPC_MAIN_DAMAGE_EASY = 5;
constexpr static auto  DISRUPTOR_NPC_MAIN_DAMAGE_MEDIUM = 10;
constexpr static auto  DISRUPTOR_NPC_MAIN_DAMAGE_HARD = 15;

constexpr static auto  DISRUPTOR_ALT_DAMAGE = 12;
constexpr static auto  DISRUPTOR_NPC_ALT_DAMAGE_EASY = 15;
constexpr static auto  DISRUPTOR_NPC_ALT_DAMAGE_MEDIUM = 25;
constexpr static auto  DISRUPTOR_NPC_ALT_DAMAGE_HARD = 30;
constexpr static auto  DISRUPTOR_ALT_TRACES = 3;		// can go through a max of 3 entities
constexpr static auto  DISRUPTOR_CHARGE_UNIT = 150.0f;	// distruptor charging gives us one more unit every 150ms--if you change this, you'll have to do the same in bg_pmove

// Wookie Bowcaster
//----------
constexpr static auto 	BOWCASTER_DAMAGE = 45;
constexpr static auto 	BOWCASTER_VELOCITY = 1300;
constexpr static auto 	BOWCASTER_NPC_DAMAGE_EASY = 12;
constexpr static auto 	BOWCASTER_NPC_DAMAGE_NORMAL = 24;
constexpr static auto 	BOWCASTER_NPC_DAMAGE_HARD = 36;
constexpr static auto  BOWCASTER_SPLASH_DAMAGE = 0;
constexpr static auto  BOWCASTER_SPLASH_RADIUS = 0;
constexpr static auto  BOWCASTER_SIZE = 2;

constexpr static auto  BOWCASTER_ALT_SPREAD = 5.0f;
constexpr static auto  BOWCASTER_VEL_RANGE = 0.3f;
constexpr static auto  BOWCASTER_CHARGE_UNIT = 200.0f;	// bowcaster charging gives us one more unit every 200ms--if you change this, you'll have to do the same in bg_pmove

// Heavy Repeater
//----------
constexpr static auto  REPEATER_SPREAD = 1.4f;
constexpr static auto  REPEATER_NPC_SPREAD = 0.7f;
constexpr static auto 	REPEATER_DAMAGE = 8;
constexpr static auto 	REPEATER_VELOCITY = 1600;
constexpr static auto 	REPEATER_NPC_DAMAGE_EASY = 2;
constexpr static auto 	REPEATER_NPC_DAMAGE_NORMAL = 4;
constexpr static auto 	REPEATER_NPC_DAMAGE_HARD = 6;

constexpr static auto  REPEATER_ALT_SIZE = 3;	// half of bbox size
constexpr static auto 	REPEATER_ALT_DAMAGE = 60;
constexpr static auto  REPEATER_ALT_SPLASH_DAMAGE = 60;
constexpr static auto  REPEATER_ALT_SPLASH_RADIUS = 128;
constexpr static auto 	REPEATER_ALT_VELOCITY = 1100;
constexpr static auto 	REPEATER_ALT_NPC_DAMAGE_EASY = 15;
constexpr static auto 	REPEATER_ALT_NPC_DAMAGE_NORMAL = 30;
constexpr static auto 	REPEATER_ALT_NPC_DAMAGE_HARD = 45;

// DEMP2
//----------
constexpr static auto 	DEMP2_DAMAGE = 15;
constexpr static auto 	DEMP2_VELOCITY = 1800;
constexpr static auto 	DEMP2_NPC_DAMAGE_EASY = 6;
constexpr static auto 	DEMP2_NPC_DAMAGE_NORMAL = 12;
constexpr static auto 	DEMP2_NPC_DAMAGE_HARD = 18;
constexpr static auto 	DEMP2_SIZE = 2;		// half of bbox size

constexpr static auto  DEMP2_ALT_DAMAGE = 15;
constexpr static auto  DEMP2_CHARGE_UNIT = 500.0f;	// demp2 charging gives us one more unit every 500ms--if you change this, you'll have to do the same in bg_pmove
constexpr static auto  DEMP2_ALT_RANGE = 4096;
constexpr static auto  DEMP2_ALT_SPLASHRADIUS = 256;

// Golan Arms Flechette
//---------
constexpr static auto  FLECHETTE_SHOTS = 6;
constexpr static auto  FLECHETTE_SPREAD = 4.0f;
constexpr static auto  FLECHETTE_DAMAGE = 15;
constexpr static auto  FLECHETTE_VEL = 3500;
constexpr static auto  FLECHETTE_SIZE = 1;

constexpr static auto  FLECHETTE_ALT_DAMAGE = 20;
constexpr static auto  FLECHETTE_ALT_SPLASH_DAM = 20;
constexpr static auto  FLECHETTE_ALT_SPLASH_RAD = 128;

// NOT CURRENTLY USED
constexpr static auto  FLECHETTE_MINE_RADIUS_CHECK = 200;
constexpr static auto  FLECHETTE_MINE_VEL = 1000;
constexpr static auto  FLECHETTE_MINE_DAMAGE = 100;
constexpr static auto  FLECHETTE_MINE_SPLASH_DAMAGE = 200;
constexpr static auto  FLECHETTE_MINE_SPLASH_RADIUS = 200;

// Personal Rocket Launcher
//---------
constexpr static auto 	ROCKET_VELOCITY = 900;
constexpr static auto 	ROCKET_DAMAGE = 100;
constexpr static auto 	ROCKET_SPLASH_DAMAGE = 100;
constexpr static auto 	ROCKET_SPLASH_RADIUS = 160;
constexpr static auto  ROCKET_NPC_DAMAGE_EASY = 20;
constexpr static auto  ROCKET_NPC_DAMAGE_NORMAL = 40;
constexpr static auto  ROCKET_NPC_DAMAGE_HARD = 60;
constexpr static auto  ROCKET_SIZE = 3;

constexpr static auto 	ROCKET_ALT_VELOCITY = (ROCKET_VELOCITY*0.5);
constexpr static auto  ROCKET_ALT_THINK_TIME = 100;

// Concussion Rifle
//---------
//primary
constexpr static auto 	CONC_VELOCITY = 3000;
constexpr static auto 	CONC_DAMAGE = 150;
constexpr static auto  CONC_NPC_SPREAD = 0.7f;
constexpr static auto 	CONC_NPC_DAMAGE_EASY = 15;
constexpr static auto 	CONC_NPC_DAMAGE_NORMAL = 30;
constexpr static auto 	CONC_NPC_DAMAGE_HARD = 50;
constexpr static auto 	CONC_SPLASH_DAMAGE = 50;
constexpr static auto 	CONC_SPLASH_RADIUS = 300;
//alt
constexpr static auto  CONC_ALT_DAMAGE = 225; //100
constexpr static auto  CONC_ALT_NPC_DAMAGE_EASY = 10;
constexpr static auto  CONC_ALT_NPC_DAMAGE_MEDIUM = 20;
constexpr static auto  CONC_ALT_NPC_DAMAGE_HARD = 30;

// Emplaced Gun
//--------------
constexpr static auto  EMPLACED_VEL = 6000;	// very fast;
constexpr static auto  EMPLACED_DAMAGE = 150;		// and very damaging
constexpr static auto  EMPLACED_SIZE = 5;		// make it easier to hit things

// ATST Main Gun
//--------------
constexpr static auto  ATST_MAIN_VEL = 4000;	//;
constexpr static auto  ATST_MAIN_DAMAGE = 25;		//;
constexpr static auto  ATST_MAIN_SIZE = 3;		// make it easier to hit things;

// ATST Side Gun
//---------------
constexpr static auto  ATST_SIDE_MAIN_DAMAGE = 75;
constexpr static auto  ATST_SIDE_MAIN_VELOCITY = 1300;
constexpr static auto  ATST_SIDE_MAIN_NPC_DAMAGE_EASY = 30;
constexpr static auto  ATST_SIDE_MAIN_NPC_DAMAGE_NORMAL = 40;
constexpr static auto  ATST_SIDE_MAIN_NPC_DAMAGE_HARD = 50;
constexpr static auto  ATST_SIDE_MAIN_SIZE = 4;
constexpr static auto  ATST_SIDE_MAIN_SPLASH_DAMAGE = 10;	// yeah, pretty small, either zero out or make it worth having?;
constexpr static auto  ATST_SIDE_MAIN_SPLASH_RADIUS = 16;	// yeah, pretty small, either zero out or make it worth having?;

constexpr static auto  ATST_SIDE_ALT_VELOCITY = 1100;
constexpr static auto  ATST_SIDE_ALT_NPC_VELOCITY = 600;
constexpr static auto  ATST_SIDE_ALT_DAMAGE = 130;

constexpr static auto  ATST_SIDE_ROCKET_NPC_DAMAGE_EASY = 30;
constexpr static auto  ATST_SIDE_ROCKET_NPC_DAMAGE_NORMAL = 50;
constexpr static auto  ATST_SIDE_ROCKET_NPC_DAMAGE_HARD = 90;

constexpr static auto 	ATST_SIDE_ALT_SPLASH_DAMAGE = 130;
constexpr static auto 	ATST_SIDE_ALT_SPLASH_RADIUS = 200;
constexpr static auto  ATST_SIDE_ALT_ROCKET_SIZE = 5;
constexpr static auto  ATST_SIDE_ALT_ROCKET_SPLASH_SCALE = 0.5f;	// scales splash for NPC's

// Stun Baton
//--------------
constexpr static auto  STUN_BATON_DAMAGE = 22;
constexpr static auto  STUN_BATON_ALT_DAMAGE = 22;
constexpr static auto  STUN_BATON_RANGE = 25;

// Laser Trip Mine
//--------------
constexpr static auto  LT_DAMAGE = 150;
constexpr static auto  LT_SPLASH_RAD = 256.0f;
constexpr static auto  LT_SPLASH_DAM = 90;

constexpr static auto  LT_VELOCITY = 250.0f;
constexpr static auto  LT_ALT_VELOCITY = 1000.0f;

constexpr static auto  PROX_MINE_RADIUS_CHECK = 190;

constexpr static auto  LT_SIZE = 3.0f;
constexpr static auto  LT_ALT_TIME = 2000;
constexpr static auto 	LT_ACTIVATION_DELAY = 1000;
constexpr static auto 	LT_DELAY_TIME = 50;

// Thermal Detonator
//--------------
constexpr static auto  TD_DAMAGE = 100;
constexpr static auto  TD_NPC_DAMAGE_CUT = 0.6f;	// NPC thrown dets deliver only 60% of the damage that a player thrown one does;
constexpr static auto  TD_SPLASH_RAD = 128;
constexpr static auto  TD_SPLASH_DAM = 90;
constexpr static auto  TD_VELOCITY = 900;
constexpr static auto  TD_MIN_CHARGE = 0.15f;
constexpr static auto  TD_TIME = 4000;
constexpr static auto  TD_THINK_TIME = 300;		// don't think too often?;
constexpr static auto  TD_TEST_RAD = (TD_SPLASH_RAD * 0.8f); // no sense in auto-blowing up if exactly on the radius edge--it would hardly do any damage;

constexpr static auto  TD_ALT_DAMAGE = 100;
constexpr static auto  TD_ALT_SPLASH_RAD = 128;
constexpr static auto  TD_ALT_SPLASH_DAM = 90;
constexpr static auto  TD_ALT_VELOCITY = 600;
constexpr static auto  TD_ALT_MIN_CHARGE = 0.15f;
constexpr static auto  TD_ALT_TIME = 3000;

// Tusken Rifle Shot
//--------------
constexpr static auto  TUSKEN_RIFLE_VEL = 3000;	// fast;
constexpr static auto  TUSKEN_RIFLE_DAMAGE_EASY = 20;		// damaging;
constexpr static auto  TUSKEN_RIFLE_DAMAGE_MEDIUM = 30;		// very damaging;
constexpr static auto  TUSKEN_RIFLE_DAMAGE_HARD = 50;		// extremely damaging;
