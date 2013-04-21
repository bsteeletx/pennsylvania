//////////////////////////
// Bug Virus Implementation/AI
// Not in game yet, so nothing really works
////////////////////////

#include "BugVirus.h"

unsigned short BugVirus::count;
unsigned short BugVirus::cost;

BugVirus::BugVirus(void)
{

}

BugVirus::BugVirus(Point GridLocation)
	: Character(Text("CreatureData/Bug"))
{
	setPosition(GridLocation.getNormalCoords());
	Type = BUG_VIRUS;
	setCollisionGroup((int) MORTALS);

	if (count == 0)
	{
		isExample = true;
		count++;
	}

	OffsetAmounts[MENU_BAR] = Point(getWidth()/4.0f, getHeight()/4.0f);
	OffsetAmounts[IN_GAME] = Point(getWidth()/4.0f, getHeight()/4.0f);
	OffsetAmounts[INTRO] = Point(getWidth()/4.0f, getHeight()/4.0f);
}

BugVirus::~BugVirus(void)
{
}

void BugVirus::attack(float currentTime, Character *Target)
{
	Character::attack(currentTime, Target);
}

void BugVirus::damage(short amount, Character *Attacker)
{
	Character::damage(amount, Attacker);
}

void BugVirus::fireWeapon(void)
{
}

unsigned short BugVirus::getCurrentCost(void)
{
	return BugVirus::cost;
}

void BugVirus::incrementCount(void)
{
	count++;
}

void BugVirus::kill(Character *Killer)
{
	Character::kill(Killer);
}

void BugVirus::update(float currentTime, std::vector<Character*> Defenders)
{
	if (!isExample)
		Character::update(currentTime, Defenders);
	else
	{
		updateCost(count);
		BugVirus::cost = Character::costCurrent;
	}
}