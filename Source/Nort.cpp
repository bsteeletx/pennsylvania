//////////////////////
// Nort Implementation/AI
///////////////////////////
#include "Nort.h"

///////////////////////
// Nort Default Constructor
// Input: None
// Result: Nort Object with nothing set (this should at least set up the variables to 0's and NULLS
/////////////////////////
Nort::Nort(void)
{

}

/////////////////////////////////
// Nort Constructor
// Input: Grid Location Point where the Nort is to be placed
// Result: Nort created and placed in the correct location
// Note: Should just set the variables in the constructor
//       Do all of the placement in an init funciton
////////////////////////////////
Nort::Nort(Point GridLocation)
	: Character(Text("CreatureData/Nort"))
{
	setPosition(GridLocation.getNormalCoords());
	Type = NORT;
	Weapon = new Laser(GridLocation.getNormalCoords());
	Weapon->setVisible(false);
	Weapon->setPosition(getX() + 15.0f, getY() + 5.75f);
	isExample = false;
	setCollisionGroup((int) MORTALS);
	hasRangedWeapon = true;
}

//////////////////////////
// Nort Destructor
// Input: None
// Result: Destruction of Nort
////////////////////
Nort::~Nort(void)
{
}

//////////////////////////////////////
// Nort Attack (override from base)
// Input: Pointer to Character that is the target of the attack
// Result: Nothing special for Nort, use base attack
/////////////////////////////////////
void Nort::attack(Character *Target)
{
	Character::attack(Target);
}

///////////////////////////////////
// Nort damage (override from base)
// Input: amound of damage to be taken
// Result: Nothing special for Nort, use base damage
///////////////////////////////////
void Nort::damage(short amount)
{
	Character::damage(amount);
}

///////////////////////////////////////
// Nort Kill (override from base)
// Input: Pointer to the Charcter who killed the Nort
// Result: Nothing special for Nort, use base Klll
//////////////////////////////////
void Nort::kill(Character *Killer)
{
	Character::kill(Killer);
}

///////////////////////////////////////////////////////////
// Nort Update (override from base)
// Input: Vector of Defenders--in this case, attackers as Norts are defenders
// Result: Move the Laser weapon to the appropriate location, and turn it on if attacking
void Nort::update(std::vector<Character*> Defenders)
{
	if (getState() == ATTACKING)
	{
		if (getCurrentTarget() != NULL)
		{
			Weapon->setPosition(this->getX() + 10.0f, Weapon->getY());
			Weapon->turnOn(this, getCurrentTarget());
		}
	}
	else
		Weapon->turnOff();

	//do normal base update
	if (getVisible())
		Character::update(Defenders);
}