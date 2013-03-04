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
	: Projectile()
{
	damageAmount = 0;
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
Laser::Laser(Vector Speed, unsigned short damage, Character *Owner)
	: Projectile(Text("Assets/Creatures/NortLaser.jpg"), Speed, 5.0f)
{
	//setColor((RGBA(255, 0, 0, 192)));
	//setDepth(8000);
	damageAmount = damage;
	Holder = Owner;
}

////////////////////////////////////////////////////////////////
// Activate Laser
// Input: Needs source of projectile
// Output: None
////////////////////////////////////////////////////////////////
void Laser::fireWeapon(void)
{
	Point Offset = Holder->getPosition();
		
	Projectile::clone(Offset.addPoint(Point(7.0f, 7.0f)));
}

////////////////////////////////////////////////////////////////
// Get Width
// Input: Two Characters
// Output: Distance between those characters
// Finds and returns the distance between two characters
//////////////////////////////////////////////////////////////
/*float Laser::getWidth(Character *Attacker, Character *Target)
{
	return Attacker->getDistanceFrom(*Target) - 5.0f;
}*/

void Laser::update(std::vector<Character*> Defenders)
{
	int targetHit = Projectile::update(Defenders);

	if (targetHit != -1)
	{
		Point SparklePos = Defenders[targetHit]->getPosition();
		//Get the position of the Target and assign it to SparklePos
		
		//Modify the value a bit to make it look better (this may not work for every game)
		SparklePos.setY(SparklePos.getY() + 5.0f);
		SparklePos.setX(SparklePos.getX() + 2.5f);

		Sparkle = new LaserHit(SparklePos);
		Sparkle->setVisible(true);

		Defenders[targetHit]->damage(damageAmount, Holder);
	}
}