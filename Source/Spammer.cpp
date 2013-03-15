//////////////////////////
// Spammer Implementation/AI
// Note: Spammers haven't appeared yet in the game
//       So I'm not going tocomment anything further
/////////////////////////////

#include "Spammer.h"

unsigned short Spammer::count;

Spammer::Spammer(void)
{
}

Spammer::Spammer(Point GridLocation)
	: Character(Text("Assets/Creatures/Spammer"))
{
	this->setPosition(GridLocation.getNormalCoords());
	Type = SPAMMER;

	if (count == 0)
		isExample = true;
}

Spammer::~Spammer(void)
{
}

void Spammer::attack(float currentTime, Character *Target)
{
	Character::attack(currentTime, Target);
}

void Spammer::damage(short amount, Character *Attacker)
{
	Character::damage(amount, Attacker);
}

void Spammer::fireWeapon(void)
{
}

void Spammer::incrementCount(void)
{
	count++;
}

void Spammer::kill(Character *Killer)
{
	Character::kill(Killer);
}

void Spammer::update(float currentTime, std::vector<Character*> Defenders)
{
	if (!isExample)
		Character::update(currentTime, Defenders);
	else
		updateCost(count);
}