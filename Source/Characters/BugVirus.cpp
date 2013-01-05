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
	this->setPosition(GridLocation.getNormalCoords());
	Type = BUG_VIRUS;
}

BugVirus::~BugVirus(void)
{
}

void BugVirus::attack(Character &Target)
{
	Target.damage(attackAmount);
}

void BugVirus::damage(short amount)
{
	hitPoints -= amount;
}

void BugVirus::update(void)
{
}