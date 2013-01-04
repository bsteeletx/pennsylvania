#pragma once

#include "Point.h"

class Vector
{

public:
	Vector(Point Begin, Point End);
	Vector();
	~Vector(void);

	Vector& operator= (const Vector& newVector);
	/*friend bool operator== (Vector& First, Vector& Second);
	friend bool operator!= (Vector& First, Vector& Second);*/

	Point getEndPoint(void);
	float getEndPointX(void);
	float getEndPointY(void);
	Point getStartPoint(void);
	float getStartPointX(void);
	float getStartPointY(void);
	
	void setStartPoint(Point Begin);
	void setFinishPoint(Point End);
	void setVectorPoints(Point Begin, Point End);

private:
	Point Start;
	Point Finish;
};