#include "Sun.h"
#include "Point.h"
#include "RGBA.h"

Sun::Sun(void)
	: PointLight(Point(50.0f, 100.0f, 50.0f), 50.0f, RGBA(255, 255, 0))
{

}


Sun::~Sun(void)
{
}
