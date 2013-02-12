/////////////////////////
// LaserHit.cpp is our particle effect for when a laser hits an object
// It probably needs some art love, but looks good for now
//////////////////////////

#include "LaserHit.h"

////////////////////////////
// Default Constructor
// Inputs: None
// Outputs: None
//////////////////////////////
LaserHit::LaserHit(void)
{
}

//////////////////////////
// Default Destructor
// Inputs: None
// Outputs: None
//////////////////////////
LaserHit::~LaserHit(void)
{
}

/////////////////////////////////////////////////////////
// Laser Hit Constructor
// Inputs: Location for Hit
// Outputs: None
// Notes (1/1/13): Constructors should only initialize values, not call functions
///////////////////////////////////////////////////////////
LaserHit::LaserHit(Point Location)
	: Particles(Location.getX(), Location.getY())
{
	setVisible(false);
}

////////////////////////////////////////////
// Local Set Visibility
// Inputs: boolean to set visibility as true or false
// Outputs: None
// Needed to write this to start the Particles
////////////////////////////////////////////
void LaserHit::setVisiblity(bool isVisible)
{
	setVisible(isVisible);

	if (isVisible)
	{
		setVelocityRange(20.0f, 30.0f);
		setSize(0.25f);
		setLife(0.15f);
		setFrequency(100.0f);
		setDirection(-1.0f, 0.0f);
		addColorKeyFrame(0.1f, RGBA(255, 0, 0, 128));
		setDepth(8000);
	}
}

//////////////////////////////////////////////
// Local set Position
// Inputs: Location for particles
// Outputs: None
/////////////////////////////////////////////
void LaserHit::setPosition(Point Location)
{
	Particles::setPosition(Location);
}