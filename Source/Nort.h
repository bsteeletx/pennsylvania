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

	void attack(Character *Target) override;
	void damage(short amount) override;
	void kill(Character *Killer) override;
	void update(std::vector<Character*> Defenders) override;

protected:
	Laser *Weapon;
};

