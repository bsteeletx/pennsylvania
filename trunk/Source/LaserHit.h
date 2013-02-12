#pragma once
#include "MyParticles.h"

class LaserHit :
	public Particles
{
public:
	LaserHit(void);
	~LaserHit(void);
	LaserHit(Point Location);

	void setPosition(Point Location);
	void setVisiblity(bool isVisible);
};

