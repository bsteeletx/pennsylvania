#include "Wall.h"
#include "agk.h"

Wall::Wall(void)
	: Plane()
{
}


Wall::~Wall(void)
{
}

Wall::Wall(float width, float height, Point Location, Point Rotation)
	: Plane(width, height)
{
	setPosition(Location);
	setRotation(Rotation.getX(), Rotation.getY(), Rotation.getZ());
}