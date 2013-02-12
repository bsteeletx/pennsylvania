#include "Floor.h"

Floor::Floor(void)
{
}


Floor::~Floor(void)
{
}

Floor::Floor(float width, float height)
	: Plane(width, height)
{
	setPosition(Point(50.0f, 100.0f, 0.0f));
}

void Floor::setTexture(Image Texture)
{
	setImage(Texture, 0);
}

/*Point Floor::getCenter(void)
{
	return Bottom.getCenter();
}*/