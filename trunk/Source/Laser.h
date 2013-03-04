#pragma once
#include "Sprite.h"
#include "Character.h"
#include "LaserHit.h"
#include "Projectile.h"
#include "Vector.h"
#include <vector>

class Laser 
	: public Projectile
{
public:
	Laser(void);
	~Laser(void);
	Laser(Vector Speed, unsigned short damage, Character *Owner);

	//float getWidth(Character *Attacker, Character *Target);
	
	void fireWeapon(void);

	void update(std::vector<Character*> Defenders);

private:
	LaserHit *Sparkle;
	Character *Holder;

	unsigned short damageAmount;
};

