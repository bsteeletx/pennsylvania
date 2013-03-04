/////////////////////
// Fog.cpp describes Fog stuff
// May need to be updated a lot once we have a level with fog in it
/////////////////////

#include "Fog.h"
#include "agk.h"

/////////////////////
// Default Constructor
// Input: None
// Output: None
//////////////////
Fog::Fog(void)
{
}

//////////////////
// Destructor
// Input: None
// Output: None
////////////////
Fog::~Fog(void)
{
}

//////////////////////////////////////
// Get Visible
// Input: Location of the fog to get visibility, in grid points
// Output: Boolean whether that part of the fogbank is visible or not
///////////////////////////////////////
bool Fog::getVisible(Point Location)
{
	return FogBank[(int)Location.getX()][(int)Location.getY()].getVisible();
}

/////////////////////////////
// Initialize Fog
// Input: None
// Output: None
//////////////////////////////
void Fog::initFog(void)
{
	//Load Fog asset
	FogSprite = Sprite("Assets/fog.png");

	//Set up fog in all locations
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Point Location((float) i, (float) j);

			FogBank[i][j] = AnimatedSprite(64, 128, 11, FogSprite.getSpriteNumber());
			FogBank[i][j].setDepth(10);
			FogBank[i][j].setSize(10.0f);
			FogBank[i][j].setPosition(Location.getNormalCoords());
			//Setting the frame to 9 is old code, this needs to be changed to something more appropriate
			FogBank[i][j].setFrame(9);
		}
	}

	//If you do not set the fog's visibility to false, it will get drawn right away, and that looks weird
	FogSprite.setVisible(false);
}

//////////////////////////////////////
// Remove Fog
// Input: Grid Location of fog to be removed
// Output: None
// Result: A bank of fog is removed at the grid location
///////////////////////////////////////
void Fog::removeFog(Point Location)
{
	FogBank[(int)Location.getX()][(int)Location.getY()].play(0.5f, false, 10, 11);
}

////////////////////////////
// Update of fog
// Input: None
// Output: None
// Result: Funciton checks through all of the individual fog banks to see if they need to be removed
/////////////////////////////
void Fog::update(void)
{
	//global bool to determine whether all the fog is gone or not
	fogIsGone = true;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//If fogbank has reached frame 11, it is done animating
			//this is old code and should be updated to reflect reality
			if (FogBank[i][j].getCurrentFrame() == 11)
				FogBank[i][j].setVisible(false);
			else
			{
				if (FogBank[i][j].getVisible())
					fogIsGone = false;
			}
		}
	}
}

////////////////////////////////////////////////
// Get the Last Visible Column
// Input: None
// Output: the value of the largest column that still has fog visible
////////////////////////////////////////////////
unsigned short Fog::getLastVisibleColumn(void)
{
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 4; j >= 0; j--)
		{
			if (FogBank[i][j].getVisible())
				return i;
		}
	}
	
	//9 is our default value where every bit of fog is gone
	return 9;
}

///////////////////////////////
// Are all of the fog banks gone?
// Input: None
// Output: Boolean that says whether the fog is gone or not
////////////////////////////
bool Fog::isFogGone(void)
{
	return fogIsGone;
}