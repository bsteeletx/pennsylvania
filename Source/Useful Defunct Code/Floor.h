#pragma once

#include "Object.h"
#include "Image.h"
#include "Point.h"

class Floor :
	public Plane
{
public:
	Floor(void);
	~Floor(void);
	Floor(float width, float height);

	//Point getCenter(void);

	void setTexture(Image Texture);

private:

	//Plane Bottom;
};

