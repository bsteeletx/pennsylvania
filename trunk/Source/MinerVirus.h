#pragma once
#include "Character.h"

#define FOG_COLUMN_REMOVAL_TIME 6

class MinerVirus :
	public Character
{
public:
	MinerVirus(void);
	~MinerVirus(void);
	MinerVirus::MinerVirus(Point Location);

	//member methods
	void attack(Character *Target) override;
	
	void damage(short amount, Character *Attacker) override;

	void fireWeapon(void) override;

	void incrementCount(void) override;

	void kill(Character *Killer) override;
	
	void update(std::vector<Character*> Defenders) override;

private:

	static unsigned short count;
};

