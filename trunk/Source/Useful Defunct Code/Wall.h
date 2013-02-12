#pragma once

#include "Object.h"

class Wall :
	public Plane
{
public:
	Wall(void);
	~Wall(void);
	Wall(float width, float height, Point Location, Point Rotation);
};

