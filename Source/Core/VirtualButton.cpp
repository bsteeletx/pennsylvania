#include "VirtualButton.h"
#include "agk.h"

VirtualButton::VirtualButton(void)
{
	buttonID = 0;
}

VirtualButton::~VirtualButton(void)
{
	//if (getExists())
	//	agk::DeleteVirtualButton(buttonID);
}

VirtualButton::VirtualButton(unsigned short buttonNumber, Point Location, float size)
{
	if (buttonNumber < 13)
	{
		if (buttonNumber)
			agk::AddVirtualButton(buttonNumber, Location.getX(), Location.getY(), size);
	}
}

bool VirtualButton::getExists(void)
{
	if (agk::GetVirtualButtonExists(buttonID) == 1)
		return true;
	
	return false;
}

bool VirtualButton::getPressed(void)
{
	if (agk::GetVirtualButtonPressed(buttonID) == 1)
		return true;

	return false;
}

bool VirtualButton::getReleased(void)
{
	if (agk::GetVirtualButtonReleased(buttonID) == 1)
		return true;

	return false;
}

bool VirtualButton::getState(void)
{
	if (agk::GetVirtualButtonState(buttonID) == 1)
		return true;

	return false;
}

void VirtualButton::setActive(bool active)
{
	if (active)
		agk::SetVirtualButtonActive(buttonID, 1);
	else
		agk::SetVirtualButtonActive(buttonID, 0);
}

void VirtualButton::setAlpha(unsigned short alpha)
{
	if (alpha < 256)
		agk::SetVirtualButtonAlpha(buttonID, alpha);
}

void VirtualButton::setColor(RGBA Values)
{
	agk::SetVirtualButtonColor(buttonID, Values.getRed(), Values.getGreen(), Values.getBlue());
	setAlpha(Values.getAlpha());
}

void VirtualButton::setImageDown(Image Object)
{
	agk::SetVirtualButtonImageDown(buttonID, Object.getImageNumber());
}

void VirtualButton::setImageUp(Image Object)
{
	agk::SetVirtualButtonImageUp(buttonID, Object.getImageNumber());
}

void VirtualButton::setPosition(Point Location)
{
	agk::SetVirtualButtonPosition(buttonID, Location.getX(), Location.getY());
}

void VirtualButton::setScreenPosition(Point Location, float size)
{
	if (size >= 0.0f)
		agk::SetButtonScreenPosition(buttonID, Location.getX(), Location.getY(), size);
}

void VirtualButton::setSize(float size)
{
	if (size >= 0.0f)
		agk::SetVirtualButtonSize(buttonID, size);
}

void VirtualButton::setText(Text InnerLabel)
{
	agk::SetVirtualButtonText(buttonID, InnerLabel.getString());
}

void VirtualButton::setVisible(bool visible)
{
	if (visible)
		agk::SetVirtualButtonVisible(buttonID, 1);
	else
		agk::SetVirtualButtonVisible(buttonID, 0);
}