//////////////////////////
// Bug Virus Implementation/AI
// Not in game yet, so nothing really works
////////////////////////

#include "BugVirus.h"

unsigned short BugVirus::count;

BugVirus::BugVirus(void)
{

}

BugVirus::BugVirus(Point GridLocation)
	: Character(Text("CreatureData/Bug"))
{
	setPosition(GridLocation.getNormalCoords());
	Type = BUG_VIRUS;

	if (count == 0)
		isExample = true;
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
		updateCost(count);
}