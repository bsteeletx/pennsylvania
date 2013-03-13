#pragma once
#include "Character.h"

class Spammer :
	public Character
{
public:
	Spammer(void);
	~Spammer(void);

	Spammer::Spammer(Point Location);

	void attack(Character *Target) override;
	
	void damage(short amount, Character *Attacker) override;

	void fireWeapon(void) override;

	void incrementCount(void) override;

	void kill(Character *Killer) override;
	
	void update(std::vector<Character*> Defenders) override;

private:
	static unsigned short count;
};

