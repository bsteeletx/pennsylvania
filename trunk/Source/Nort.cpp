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
	Weapon = new Laser(Vector(Point(100.0f/1000.0f, 0.0f)), attackAmount, this);
	//Weapon->setPosition(getX() + 15.0f, getY() + 5.75f);
	isExample = false;
	setCollisionGroup((int) MORTALS);
	hasRangedWeapon = true;

	OffsetAmounts[MENU_BAR] = Point(getWidth()/4.0f, getHeight()/4.0f);
	OffsetAmounts[IN_GAME] = Point(getWidth()/4.0f, getHeight()/4.0f);
	OffsetAmounts[INTRO] = Point(getWidth()/4.0f, getHeight()/4.0f);
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
void Nort::attack(float currentTime, Character *Target)
{
	Character::attack(currentTime, Target);
}

///////////////////////////////////
// Nort damage (override from base)
// Input: amound of damage to be taken
// Result: Nothing special for Nort, use base damage
///////////////////////////////////
void Nort::damage(short amount, Character *Attacker)
{
	Character::damage(amount, Attacker);
}

/////////////////////////////
// Fire Weapon
// Input: none
// Result: ranged weapon fired
//////////////////////////////
void Nort::fireWeapon(void)
{
	if (getCurrentTarget() != NULL)
		Weapon->fireWeapon();
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
void Nort::update(float currentTime, std::vector<Character*> Defenders)
{
	//do normal base update
	if (getVisible())
	{
		Weapon->update(Defenders);
		Character::update(currentTime, Defenders);
	}
}