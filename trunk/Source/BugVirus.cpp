//////////////////////////
// Bug Virus Implementation/AI
// Not in game yet, so nothing really works
////////////////////////

#include "BugVirus.h"


BugVirus::BugVirus(void)
{

}

BugVirus::BugVirus(Point GridLocation)
	: Character(Text("CreatureData/Bug"))
{
	setPosition(GridLocation.getNormalCoords());
	Type = BUG_VIRUS;
}

BugVirus::~BugVirus(void)
{
}

void BugVirus::attack(Character *Target)
{
	Character::attack(Target);
}

void BugVirus::damage(short amount, Character *Attacker)
{
	Character::damage(amount, Attacker);
}

void BugVirus::fireWeapon(void)
{
}

void BugVirus::kill(Character *Killer)
{
	Character::kill(Killer);
}

void BugVirus::update(std::vector<Character*> Defenders)
{
	Character::update(Defenders);
}