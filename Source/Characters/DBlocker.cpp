//////////////////////////
// D-Blocker Implementation/AI
// Not currently in game, so none of the following would be useful for comments
///////////////////////////

#include "DBlocker.h"


DBlocker::DBlocker(void)
{

}

DBlocker::DBlocker(Point GridLocation)
	: Character(Text("Creatures/DBlocker"))
{
	this->setPosition(GridLocation.getNormalCoords());
	Type = DBLOCKER;
}

DBlocker::~DBlocker(void)
{
}

void DBlocker::attack(Character &Target)
{
	Target.damage(attackAmount);
}

void DBlocker::damage(short amount)
{
	hitPoints -= amount;
}