#pragma once
#include "Character.h"
#include "Text.h"

class ThiefVirus :
	public Character
{
public:
	ThiefVirus(void);
	~ThiefVirus(void);
	ThiefVirus::ThiefVirus(Point Location);

	//member methods
	void attack(Character *Target) override;
	
	void damage(short amount, Character *Attacker) override;

	void fireWeapon(void) override;

	void incrementCount(void) override;

	void kill(Character *Killer) override;
	
	void update(std::vector<Character*> Defenders) override;

protected:

	static unsigned short count;
};

