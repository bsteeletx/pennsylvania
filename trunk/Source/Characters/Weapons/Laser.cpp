////////////////////////
// Laser Weapon for Nort
// Has a sprite for the laster
// And a particle for where it hits
//////////////////////////

#include "Laser.h"

//////////////////////////
// Default Constructor
// Input: None
// Output: None
////////////////////////////
Laser::Laser(void)
	: Sprite()
{
	setColor((RGBA(255, 0, 0, 192)));
	Sparkle = new LaserHit();
	setDepth(8000);
}

//////////////////////////
// Default Destructor
// Input: None
// Output: None
//////////////////////////
Laser::~Laser(void)
{
}

//////////////////////////////////////////
// Constructor
// Input: Location for where the particle effect should be
// Output: None
// Notes (1/2/13): Don't put functions in constructors! Save that for initialization!
///////////////////////////////////////
Laser::Laser(Point SparkleLocation)
	: Sprite()
{
	setColor((RGBA(255, 0, 0, 192)));
	Sparkle = new LaserHit(SparkleLocation);
	setDepth(8000);
}

////////////////////////////////////////////////////////////////
// Activate Laser
// Input: Needs the Character where the laser begins and the Target where the laser hits
// Output: None
////////////////////////////////////////////////////////////////
void Laser::turnOn(Character *Attacker, Character *Target)
{
	//Get the position of the Target and assign it to SparklePos
	Point SparklePos = Target->getPosition();

	//Modify the value a bit to make it look better (this may not work for every game)
	SparklePos.setY(SparklePos.getY() + 5.0f);
	SparklePos.setX(SparklePos.getX() + 2.5f);

	//Other initializing functions for laser weapon
	setVisible(true);
	setSize(getWidth(Attacker, Target), 1.0f);
	//Other initializing functions for laser particle effect
	Sparkle->setPosition(SparklePos);
	Sparkle->setVisiblity(true);
}


/////////////////////////////
// Shut off Laser
// Input: None
// Output: None
// Turns off Laser
////////////////////////////
void Laser::turnOff(void)
{
	//Turn off the visibility for both the laser and the sparkle effect
	setVisible(false);
	Sparkle->setVisiblity(false);
}

////////////////////////////////////////////////////////////////
// Get Width
// Input: Two Characters
// Output: Distance between those characters
// Finds and returns the distance between two characters
//////////////////////////////////////////////////////////////
float Laser::getWidth(Character *Attacker, Character *Target)
{
	return Attacker->getDistanceFrom(*Target) + 5.0f;
}