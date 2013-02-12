#pragma once

#include "Object.h"
#include "Image.h"

class Ceiling :
	public Plane
{
public:
	Ceiling(void);
	~Ceiling(void);
	Ceiling(float width, float height);

	void setTexture(Image Texture);

private:
	//Plane Sky;
};

