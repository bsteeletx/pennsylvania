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

void Spammer::attack(Character &Target)
{
	Target.damage(attackAmount);
}

void Spammer::damage(short amount)
{
	hitPoints -= amount;
}

void Spammer::update(void)
{
}