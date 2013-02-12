#pragma once
#include "Object.h"
class Selector :
	public Plane
{
public:
	Selector(void);
	~Selector(void);
	Selector(Image Object);

	Point getGridPosition(void);
	
	void setGridPosition(Point Location);

private:
	Image Texture;
};

