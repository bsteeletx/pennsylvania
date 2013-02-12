#include "Ceiling.h"


Ceiling::Ceiling(void)
{
}


Ceiling::~Ceiling(void)
{
}

Ceiling::Ceiling(float width, float height)
	: Plane(width, height)
{
	setPosition(Point(-50.0f, 100.0f, 50.0f));
}

void Ceiling::setTexture(Image Texture)
{
	setImage(Texture, 0);
}