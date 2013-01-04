#pragma once

#include "Point.h"

class PhysicsForce
{
public:
	PhysicsForce();
	~PhysicsForce();
	PhysicsForce(Point Location, float power, float limit, float range, bool fade);

	void setPosition(Point Location);
	void setPower(float powerInNewtons);
	void setRange(float range);

private:
	unsigned int forceID;
};