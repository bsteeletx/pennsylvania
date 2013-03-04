//////////////////////////
// Spammer Implementation/AI
// Note: Spammers haven't appeared yet in the game
//       So I'm not going tocomment anything further
/////////////////////////////

#include "Spammer.h"


Spammer::Spammer(void)
{
}

Spammer::Spammer(Point GridLocation)
	: Character(Text("Assets/Creatures/Spammer"))
{
	this->setPosition(GridLocation.getNormalCoords());
	Type = SPAMMER;
}

Spammer::~Spammer(void)
{
}

void Spammer::attack(Character *Target)
{
	Character::attack(Target);
}

void Spammer::damage(short amount, Character *Attacker)
{
	Character::damage(amount, Attacker);
}

void Spammer::fireWeapon(void)
{
}


void Spammer::kill(Character *Killer)
{
	Character::kill(Killer);
}

void Spammer::update(std::vector<Character*> Defenders)
{
	Character::update(Defenders);
}