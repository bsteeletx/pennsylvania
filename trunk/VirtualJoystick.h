#pragma once
#include "Point.h"
#include "Image.h"
class VirtualJoystick
{
public:
	VirtualJoystick();
	~VirtualJoystick(void);
	VirtualJoystick(unsigned short joystickNumber, Point Location, float size);

	bool getExists(void);
	float getX(void);
	float getY(void);

	void setActive(bool active);
	void setAlpha(unsigned short alphaInner, unsigned short alphaOuter);
	void setDeadZone(float play);
	void setImageInner(Image Object);
	void setImageOuter(Image Object);
	void setPosition(Point Location);
	void setSize(float size);
	void setVisible(bool visible);
private:
	unsigned short joystickID;
};