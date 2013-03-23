#pragma once
#include "Character.h"
#include "Laser.h"

class Nort :
	public Character
{
public:
	Nort(void);
	~Nort(void);

	Nort::Nort(Point Location);

	void attack(float currentTime, Character *Target) override;
	
	void damage(short amount, Character *Attacker) override;
	
	void fireWeapon(void) override;

	void incrementCount(void) override {};
	void incrementTime(float currentTime) override {};

	void kill(Character *Killer) override;
	
	void update(float currentTime, std::vector<Character*> Defenders) override;

protected:
	Laser *Weapon;
};

