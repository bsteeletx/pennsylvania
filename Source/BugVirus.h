#pragma once
#include "Character.h"

class BugVirus :
	public Character
{
public:
	BugVirus(void);
	~BugVirus(void);

	BugVirus::BugVirus(Point Location);

	void attack(float currentTime, Character *Target) override;
	
	void damage(short amount, Character *Attacker) override;

	void incrementCount(void) override;
	void incrementTime(float currentTime) override {};

	void fireWeapon(void) override;

	void kill(Character *Killer) override;

	void update(float currentTime, std::vector<Character*> Defenders) override;

private:

	static unsigned short count;
};

