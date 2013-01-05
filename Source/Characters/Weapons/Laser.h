#pragma once
#include "Sprite.h"
#include "..\Character.h"
#include "LaserHit.h"

class Laser 
	: public Sprite
{
public:
	Laser(void);
	~Laser(void);
	Laser(Point SparkleLocation);

	void turnOff(void);
	void turnOn(Character *Attacker, Character *Target);

	float getWidth(Character *Attacker, Character *Target);

private:
	LaserHit *Sparkle;
};

