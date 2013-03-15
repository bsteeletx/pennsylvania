#pragma once
#include "Character.h"

#define DBLOCKER_HEIGHT 25
#define DBLOCKER_WIDTH 25
#define DBLOCKER_COUNT 24
#define DBLOCKER_PATHFILE "Creatures/DBlocker.png"

class DBlocker :
	public Character
{
public:
	DBlocker(void);
	~DBlocker(void);

	DBlocker::DBlocker(Point Location);

	void attack(float currentTime, Character *Target) override;
	
	void damage(short amount, Character *Attacker) override;

	void fireWeapon(void) override;

	void incrementCount(void) override;

	void kill(Character *Killer) override;
	
	void update(float currentTime, std::vector<Character*> Defenders) override;

private:
	static unsigned short count;
};

