#pragma once
#include "Character.h"

class BugVirus :
	public Character
{
public:
	BugVirus(void);
	~BugVirus(void);

	BugVirus::BugVirus(Point Location);

	void attack(Character *Target) override;
	
	void damage(short amount, Character *Attacker) override;

	void fireWeapon(void) override;

	void kill(Character *Killer) override;

	void update(std::vector<Character*> Defenders) override;

private:

};

