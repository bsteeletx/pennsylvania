//////////////////////////
// D-Blocker Implementation/AI
// Not currently in game, so none of the following would be useful for comments
///////////////////////////

#include "DBlocker.h"


DBlocker::DBlocker(void)
{

}

DBlocker::DBlocker(Point GridLocation)
	: Character(Text("Assets/Creatures/DBlocker"))
{
	setPosition(GridLocation.getNormalCoords());
	Type = DBLOCKER;
}

DBlocker::~DBlocker(void)
{
}

void DBlocker::attack(Character *Target)
{
	Character::attack(Target);
}

void DBlocker::damage(short amount, Character *Attacker)
{
	Character::damage(amount, Attacker);
}

void DBlocker::fireWeapon(void)
{
}


void DBlocker::kill(Character *Killer)
{
	Character::kill(Killer);
}

void DBlocker::update(std::vector<Character*> Defenders)
{
	Character::update(Defenders);
}