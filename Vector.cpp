#include "Vector.h"

Vector::Vector(void)
{
}

Vector::Vector(Point Begin, Point End)
{
	Start = Begin;
	Finish = End;
}

Vector::~Vector(void)
{
}

Vector& Vector::operator= (const Vector& newVector)
{
	Start = newVector.Start;
	Finish = newVector.Finish;

	return *this;
}

/*bool operator== (Vector& First, Vector& Second)
{
	if (First.Start == Second.Start)
	{
		if (First.Finish == Second.Finish)
			return true;
	}

	return false;
}

bool operator!= (Vector& First, Vector& Second)
{
	if (First == Second)
		return false;
	
	return true;
}*/

Point Vector::getEndPoint(void)
{
	return Finish;
}

float Vector::getEndPointX(void)
{
	return Finish.getX();
}

float Vector::getEndPointY(void)
{
	return Finish.getY();
}

Point Vector::getStartPoint(void)
{
	return Start;
}

float Vector::getStartPointX(void)
{
	return Start.getX();
}

float Vector::getStartPointY(void)
{
	return Start.getY();
}

void Vector::setStartPoint(Point Begin)
{
	Start = Begin;
}

void Vector::setFinishPoint(Point End)
{
	Finish = End;
}

void Vector::setVectorPoints(Point Begin, Point End)
{
	Start = Begin;
	Finish = End;
}