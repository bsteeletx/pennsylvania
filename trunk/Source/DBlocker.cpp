//////////////////////////
// D-Blocker Implementation/AI
// Not currently in game, so none of the following would be useful for comments
///////////////////////////

#include "DBlocker.h"

unsigned short DBlocker::count;

DBlocker::DBlocker(void)
{

}

DBlocker::DBlocker(Point GridLocation)
	: Character(Text("CreatureData/DBlocker"))
{
	setPosition(GridLocation.getNormalCoords());
	Type = DBLOCKER;

	if (count == 0)
		isExample = true;
}

DBlocker::~DBlocker(void)
{
}

void DBlocker::attack(float currentTime, Character *Target)
{
	Character::attack(currentTime, Target);
}

void DBlocker::damage(short amount, Character *Attacker)
{
	Character::damage(amount, Attacker);
}

void DBlocker::fireWeapon(void)
{
}

void DBlocker::incrementCount(void)
{
	count++;
}

void DBlocker::kill(Character *Killer)
{
	Character::kill(Killer);
}

void DBlocker::update(float currentTime, std::vector<Character*> Defenders)
{
	if (!isExample)
		Character::update(currentTime, Defenders);
	else
		updateCost(count);
}