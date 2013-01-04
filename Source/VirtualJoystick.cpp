#include "VirtualJoystick.h"
#include "agk.h"

VirtualJoystick::VirtualJoystick(void)
{
	joystickID = 0;
}

VirtualJoystick::~VirtualJoystick(void)
{
	//if (getExists())
	//	agk::DeleteVirtualJoystick(joystickID);
}

VirtualJoystick::VirtualJoystick(unsigned short joystickNumber, Point Location, float size)
{
	if (joystickNumber < 5)
	{
		if (joystickNumber)
			agk::AddVirtualJoystick(joystickNumber, Location.getX(), Location.getY(), size);
	}
}

bool VirtualJoystick::getExists(void)
{
	if (agk::GetVirtualJoystickExists(joystickID) == 1)
		return true;

	return false;
}

float VirtualJoystick::getX(void)
{
	return agk::GetVirtualJoystickX(joystickID);
}

float VirtualJoystick::getY(void)
{
	return agk::GetVirtualJoystickY(joystickID);
}

void VirtualJoystick::setActive(bool active)
{
	if (active)
		agk::SetVirtualJoystickActive(joystickID, 1);
	else
		agk::SetVirtualJoystickActive(joystickID, 0);
}

void VirtualJoystick::setAlpha(unsigned short alphaInner, unsigned short alphaOuter)
{
	if (alphaInner < 256)
	{
		if (alphaOuter < 256)
			agk::SetVirtualJoystickAlpha(joystickID, alphaInner, alphaOuter);
	}
}

void VirtualJoystick::setDeadZone(float play)
{
	if (play >= 0.0f)
	{
		if (play <= 1.0f)
			agk::SetVirtualJoystickDeadZone(play);
	}
}

void VirtualJoystick::setImageInner(Image Object)
{
	agk::SetVirtualJoystickImageInner(joystickID, Object.getImageNumber());
}

void VirtualJoystick::setImageOuter(Image Object)
{
	agk::SetVirtualJoystickImageOuter(joystickID, Object.getImageNumber());
}

void VirtualJoystick::setPosition(Point Location)
{
	agk::SetVirtualJoystickPosition(joystickID, Location.getX(), Location.getY());
}

void VirtualJoystick::setSize(float size)
{
	if (size >= 0.0f)
		agk::SetVirtualJoystickSize(joystickID, size);
}

void VirtualJoystick::setVisible(bool visible)
{
	if (visible)
		agk::SetVirtualJoystickVisible(joystickID, 1);
	else
		agk::SetVirtualJoystickVisible(joystickID, 0);
}