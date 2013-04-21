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
#define RECTANGLE 2
#define POLYGON 3
///////////////////CREATURE TYPES
enum Creature
{
	NO_CREATURE,
	INFORMATION_NODE,
	MINER_VIRUS,
	THIEF_VIRUS,
	BUG_VIRUS,
	DBLOCKER,
	SPAMMER,
	NORT
};
//////////////////ANIMATION TYPES
enum CharacterState
{
	MENU_TOOMUCH,
	MENU_AVAILABLE,
	MENU_HIDDEN,
	SELECTED,
	IDLE,
	MOVING,
	ATTACKING,
	DEATH,
	FADEOUT
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
	#define XBEG 7.0f
	#define YBEG 23.0f
	#define SPOT_WIDTH 10.0f
	#define SPOT_HEIGHT 13.6f
	#define SPOT_BORDER_Y 0.0f
	#define SPOT_BORDER_X 0.0f
	#define MENU_BORDER 2.0f
	#define XBEG_MENU 7.25f
	#define MENU_Y 7.5f
	#define MENU_WIDTH 10.0f//70/10.24f
	#define MENU_HEIGHT 12.5f //54/7.68f
	#define MENU_BORDER_WIDTH 100/10.24f
	#define MENU_CREATURE_WIDTH 5.5875263f
#endif
/////////////////Facebook download states
enum DownloadState
{
	NOACTIVITY,
	DOWNLOADING,
	FINISHED,
	ERRORSTATE
};
//////////////////Orientations
enum Orientation
{
	NONE, //orientation does not return 0
	PORTRAIT,
	REV_PORTRAIT,
	LANDSCAPE,
	REV_LANDSCAPE
};
/////////////////TextInputState was opposite of what you'd expect
enum TextInputState
{
	USING,
	NOTUSING
};
//////////////////3D Shapes
enum ObjectType
{
	BOX,
	CONE,
	CYLINDER,
	PLANE,
	SPHERE
};
//////////////////Cull Modes
enum CullMode
{
	BOTH,
	FRONT,
	BACK
};
////////////////Depth Read Mode
enum DepthMode
{
	NEVER,
	LESS,
	EQUAL,
	LESS_OR_EQUAL,
	GREATER,
	NOT_EQUAL,
	GREATER_OR_EQUAL,
	ALWAYS
};
////////////////Transparency Modes
enum TransparencyMode
{
	NO_TRANSPARENCY,
	BLENDED,
	ADDITIVE
};
//////////////////Ray Cast Modes
enum RayCastMode
{
	PHYSICS,
	PHYSICS_CATEGORY,
	PHYSICS_GROUP,
	SPRITE,
	SPRITE_CATEGORY,
	SPRITE_GROUP,
	SPRITE_SINGLE
};
/////////////////Offset States
enum OffsetStates
{
	MENU_BAR,
	IN_GAME,
	INTRO
}; 
//////////////////App Store Game ID
#define IOS_GAME_ID ""