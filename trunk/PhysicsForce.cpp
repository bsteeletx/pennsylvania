#include "PhysicsForce.h"
#include "agk.h"

PhysicsForce::PhysicsForce(void)
{
	forceID = 0;
}

PhysicsForce::~PhysicsForce(void)
{
	//agk::DeletePhysicsForce(forceID);
}

PhysicsForce::PhysicsForce(Point Location, float power, float limit, float range, bool fade)
{
	if (fade)
		forceID = agk::CreatePhysicsForce(Location.getX(), Location.getY(), power, limit, range, 1);
	else
		forceID = agk::CreatePhysicsForce(Location.getX(), Location.getY(), power, limit, range, 1);
}

void PhysicsForce::setPosition(Point Location)
{
	agk::SetPhysicsForcePosition(forceID, Location.getX(), Location.getY());
}

void PhysicsForce::setPower(float powerInNewtons)
{
	agk::SetPhysicsForcePower(forceID, powerInNewtons);
}

void PhysicsForce::setRange(float range)
{
	agk::SetPhysicsForceRange(forceID, range);
}