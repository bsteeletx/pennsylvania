#include "Point.h"
#include "agk.h"
#include "Defines.h"

Point::Point()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	minValue = -100.0f;
	maxValue = 200.0f;
}

Point::Point(float loc_x, float loc_y, float loc_z, float lowValue, float hiValue)
{
	x = loc_x;
	y = loc_y;
	z = loc_z;
	minValue = lowValue;
	maxValue = hiValue;
}

Point::~Point(void)
{
}

void Point::floor(void)
{
	x = agk::Floor(x);
	y = agk::Floor(x);
	z = agk::Floor(x);
}

float Point::getMaxValue(void)
{
	return maxValue;
}

float Point::getMinValue(void)
{
	return minValue;
}

float Point::getX(void)
{
	return x;
}

float Point::getY(void)
{
	return y;
}

float Point::getZ(void)
{
	return z;
}

Point Point::getGridCoords(void)
{
	float xLoc = (x - XBEG)/SPOT_WIDTH;
	float yLoc = (y - YBEG)/SPOT_HEIGHT;

	return Point((int) xLoc, (int) yLoc);
}

Point Point::getNormalCoords(void)
{
	float xLoc = x;
	float yLoc = y;

	xLoc = xLoc*SPOT_WIDTH + XBEG;
	yLoc = yLoc*SPOT_HEIGHT + YBEG;

	if (xLoc < XBEG)
		xLoc = XBEG;
	if (yLoc < YBEG - SPOT_HEIGHT)
		yLoc = YBEG - SPOT_HEIGHT;
	if (xLoc > XMAX*SPOT_WIDTH + XBEG)
		xLoc = XMAX*SPOT_WIDTH + XBEG;
	if (yLoc > YMAX*SPOT_HEIGHT + YBEG)
		yLoc = YMAX*SPOT_HEIGHT + YBEG;

	return Point(xLoc, yLoc);
}

void Point::setCoordsAsGridCoords(void)
{
	x = (int) ((x - XBEG)/SPOT_WIDTH);
	y = ((y - YBEG)/SPOT_HEIGHT);

	if (y < 0.0f)
		y = -1.0f;
	else
		y = (int) y;
}

void Point::setCoords(float loc_x, float loc_y, float loc_z)
{
	float values[3] = {loc_x, loc_y, loc_z};
	
	containCoords(values);

	x = values[0];
	y = values[1];
	z = values[2];
}

void Point::setX(float loc_x)
{
	x = containCoord(loc_x);
}

void Point::setY(float loc_y)
{
	y = containCoord(loc_y);
}

void Point::setZ(float loc_z)
{
	z = containCoord(loc_z);
}

float Point::containCoord(float coord)
{
	if (coord < minValue)
		return minValue;
	else if (coord > maxValue)
		return maxValue;
	else
		return coord;
}

void Point::containCoords(float coords[])
{
	for (int i = 0; i < 3; i++)
		coords[i] = containCoord(coords[i]);
}