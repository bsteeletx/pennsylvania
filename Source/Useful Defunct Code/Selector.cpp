#include "Selector.h"
#include "Defines.h"
#include "agk.h"

Selector::Selector(void)
{
}


Selector::~Selector(void)
{
}

Selector::Selector(Image Object)
	: Plane(SPOT_WIDTH, SPOT_HEIGHT)
{
	setImage(Object, 0);
	Texture = Object;
}

Point Selector::getGridPosition(void)
{
	return getLocation().getGridCoords();
}

void Selector::setGridPosition(Point Location)
{
	Location.setCoordsAsGridCoords();
	
	Location = Location.addPoint(Point(-5.0f, -2.0f, 0.0f));
	
	setPosition(Location.getNormalCoords());



	if (getZ() < 1.0f)
		moveLocalZ(1.0f);



	//setPosition(Point(24.444444f, 14.66667f, 1.0f));

	//moveLocalX(6.0f);

	//moveLocalY(1.0f);
	agk::PrintC("SELECTOR LOC: ");
	agk::PrintC(getX());
	agk::PrintC(", ");
	agk::PrintC(getY());
	agk::PrintC(", ");
	agk::Print(getZ());

	

}