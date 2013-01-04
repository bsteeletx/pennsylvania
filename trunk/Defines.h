#pragma once

/////////////PLATFORM DEFINITIONS
#define TABLET 0
#define MOBILE 1
#define PC 2

#define IOS 0
#define ANDROID 1
#define WINDOWS 2

#define PLATFORM PC
#define OS WINDOWS
///////////////////////MISC
#define DEMOBUILD 0
#define GRIDGAME 1
#define SECONDS 1000
///////////////////ASPECT RATIOS, add more when needed
#if PLATFORM == PC
#define ASPECT (float) 1024/768
#endif
///////////////////STATES
enum GameStates
{
	LOADING,
	MENU,
	OPTIONS,
	LEVEL_LOAD,
	LEVEL_INIT,
	PLAYING
};
//////////////////LANGUAGES
#define ENGLISH 0
#define FRENCH 1
#define ITALIAN 2
#define GERMAN 3
#define SPANISH 4
//////////////////SHAPES
#define NOSHAPE 0
#define CIRCLE 1
#define BOX 2
#define POLYGON 3
///////////////////CREATURE TYPES
enum Creature
{
	INFORMATION_NODE,
	MINER_VIRUS,
	THIEF_VIRUS,
	DBLOCKER,
	BUG_VIRUS,
	SPAMMER,
	NORT
};
//////////////////ANIMATION TYPES
enum CharacterState
{
	POSE,
	IDLE,
	MOVING,
	ATTACKING,
	DEATH
};
///////////////////Collision Groups
enum CollisionGroup
{
	EXAMPLES,
	GODS,
	GHOSTS,
	MORTALS
};
////////////////GRID STYLE, IF APPLICABLE
#if (GRIDGAME)
	#define XMAX 8
	#define YMAX 4
	#define XBEG 5.0f
	#define YBEG 17.5f
	#define SPOT_WIDTH 10.5f
	#define SPOT_HEIGHT 13.5f
#endif