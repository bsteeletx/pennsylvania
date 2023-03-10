///////////////////////////
// Thief Virus Implementation/AI
//////////////////////////
#include "ThiefVirus.h"

unsigned short ThiefVirus::count;
unsigned short ThiefVirus::cost;

///////////////////////////////
// Default Constructor
// Input: None
// Result: ThiefVirus Object Created
////////////////////////////////////////
ThiefVirus::ThiefVirus(void)
	: Character(Text("Assets/Creatures/Thief"))
{
	Type = THIEF_VIRUS;
}

///////////////////////////////////////////////
// Constructor
// Input: Grid Location where Thief Virus will be placed
// Output: Thief Virus Object created at a certain point
// Note: Probably should have an initialization that places the thief at a point, not during creation
/////////////////////////////////////////////
ThiefVirus::ThiefVirus(Point GridLocation)
	: Character(Text("CreatureData/Thief"))
{
	setPosition(GridLocation.getNormalCoords());
	Type = THIEF_VIRUS;

	if (count == 0)
	{
		isExample = true;
		count++;
	}

	OffsetAmounts[MENU_BAR] = Point(-0.01f, -0.01f);
	OffsetAmounts[IN_GAME] = Point(getWidth()/4.0f + 0.5f, getHeight()/4.0f + 3.0f);
	OffsetAmounts[INTRO] = Point(10.0f, 7.5f);
}

///////////////////////////////////
// Destructor
// Input: None
// Result: Thief Virus destroyed
////////////////////////////////
ThiefVirus::~ThiefVirus(void)
{
}

/////////////////////////////////////////////
// Attack (override of base attack)
// Input: Character object who is the target
// Result: Check to see if the target is an information node
//         If it isn't (thieves can only attack information nodes) disregard the attack
////////////////////////////////////////////
void ThiefVirus::attack(float currentTime, Character *Target)
{
	if (Target->getCreatureType() == INFORMATION_NODE)
	{
		Character::attack(currentTime, Target);

		if (didDamage)
			this->kill((Character *) this);
	}
}

////////////////////////////////////////
// Damage (override of base damage)
// Input: Amount that the virus gets damaged
// Result: Call the base class damage as there are no special needs here
///////////////////////////////////////
void ThiefVirus::damage(short amount, Character *Attacker)
{
	Character::damage(amount, Attacker);
}

void ThiefVirus::fireWeapon(void)
{
}

unsigned short ThiefVirus::getCurrentCost(void)
{
	return ThiefVirus::cost;
}

void ThiefVirus::incrementCount(void)
{
	count++;
}

///////////////////////////////////////////////
// Kill (override of base kill)
// Input: Character who killed this creature
// Result: Call the base kill as nothing special needs to happen here
//////////////////////////////////////////
void ThiefVirus::kill(Character *KilledBy)
{
	Character::kill(KilledBy);
}

///////////////////////////////////////////////////////////////
// Update (override of base update)
// Input: List of Defenders in level
// Result: Call the base update as nothing special needs to happen here
/////////////////////////////////////////////////////////////
void ThiefVirus::update(float currentTime, std::vector<Character*> Defenders)
{
	if (!isExample)
		Character::update(currentTime, Defenders);
	else
	{
		updateCost(count);
		ThiefVirus::cost = Character::costCurrent;
	}
}