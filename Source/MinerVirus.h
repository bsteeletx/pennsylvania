#pragma once
#include "Character.h"
#include "Timer.h"

class MinerVirus :
	public Character
{
public:
	MinerVirus(void);
	~MinerVirus(void);
	MinerVirus::MinerVirus(Point Location);

	//member methods
	void attack(float currentTime, Character *Target) override;
	
	void damage(short amount, Character *Attacker) override;
	void drainHealth(void);

	void fireWeapon(void) override;

	void incrementCount(void) override;
	void incrementTime(float currentTime) override;

	void kill(Character *Killer) override;
	
	void toggleAlpha(void);

	void update(float currentTime, std::vector<Character*> Defenders) override;

private:

	static unsigned short count;
	static float time;

	float difference;

	unsigned short ID;

	float lastDrainTime;

	float blinkTime;
};

