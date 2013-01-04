#include "EditBox.h"
#include "agk.h"

EditBox::EditBox()
{
	boxID = agk::CreateEditBox();
}

EditBox::~EditBox()
{
//	if (getExists())
//		agk::DeleteEditBox(boxID);
}

EditBox::EditBox(unsigned int boxNumber)
{
	boxID = boxNumber;
	agk::CreateEditBox(boxID);
}

void EditBox::fixToScren(bool toScreen)
{
	if (toScreen)
		agk::FixEditBoxToScreen(boxID, 1);
	else
		agk::FixEditBoxToScreen(boxID, 0);
}

bool EditBox::getActive(void)
{
	if (agk::GetEditBoxActive(boxID) == 1)
		return true;

	return false;
}

bool EditBox::getChanged(void)
{
	if (agk::GetEditBoxChanged(boxID) == 1)
		return true;

	return false;
}

bool EditBox::getExists(void)
{
	if (agk::GetEditBoxExists(boxID) == 1)
		return true;

	return false;
}

bool EditBox::getHasFocus(void)
{
	if (agk::GetEditBoxHasFocus(boxID) == 1)
		return true;

	return false;
}

float EditBox::getHeight(void)
{
	return agk::GetEditBoxHeight(boxID);
}

unsigned int EditBox::getLines(void)
{
	return agk::GetEditBoxLines(boxID);
}

Text EditBox::getText(void)
{
	Text ReturnText(agk::GetEditBoxText(boxID));
	
	return ReturnText;
}

bool EditBox::getVisible(void)
{
	if (agk::GetEditBoxVisible(boxID) == 1)
		return true;

	return false;
}

float EditBox::getWidth(void)
{
	return agk::GetEditBoxWidth(boxID);
}

float EditBox::getX(void)
{
	return agk::GetEditBoxX(boxID);
}

float EditBox::getY(void)
{
	return agk::GetEditBoxY(boxID);
}

void EditBox::setActive(bool active)
{
	if (active)
		agk::SetEditBoxActive(boxID, 1);
	else
		agk::SetEditBoxActive(boxID, 0);
}

void EditBox::setBackgroundColor(RGBA Values)
{
	agk::SetEditBoxBackgroundColor(boxID, Values.getRed(), Values.getGreen(), Values.getBlue(), Values.getAlpha());
}

void EditBox::setBackgroundImage(Image Object)
{
	agk::SetEditBoxBackgroundImage(boxID, Object.getImageNumber());
}

void EditBox::setBorderColor(RGBA Values)
{
	agk::SetEditBoxBorderColor(boxID, Values.getRed(), Values.getGreen(), Values.getBlue(), Values.getAlpha());
}

void EditBox::setBorderImage(Image Object)
{
	agk::SetEditBoxBorderImage(boxID, Object.getImageNumber());
}

void EditBox::setBorderSize(float size)
{
	if (size >= 0.0f)
		agk::SetEditBoxBorderSize(boxID, size);
}

void EditBox::setCursorBlinkTime(float speedInSeconds)
{
	if (speedInSeconds > 0.0f)
		agk::SetEditBoxCursorBlinkTime(boxID, speedInSeconds);
}

void EditBox::setCursorColor(RGBA Values)
{
	agk::SetEditBoxCursorColor(boxID, Values.getRed(), Values.getGreen(), Values.getBlue());
}

void EditBox::setCursorWidth(float width)
{
	if (width > 0.0f)
		agk::SetEditBoxCursorWidth(boxID, width);
}

void EditBox::setDepth(unsigned int depth)
{
	if (depth <= 10000)
		agk::SetEditBoxDepth(boxID, depth);
}

void EditBox::setFocus(bool focus)
{
	if (focus)
		agk::SetEditBoxFocus(boxID, 1);
	else
		agk::SetEditBoxFocus(boxID, 0);
}

void EditBox::setFontImage(Image Object)
{
	agk::SetEditBoxFontImage(boxID, Object.getImageNumber());
}

void EditBox::setMaxChars(unsigned int max)
{
	agk::SetEditBoxMaxChars(boxID, max);
}

void EditBox::setMaxLines(unsigned int max)
{
	agk::SetEditBoxMaxLines(boxID, max);
}

void EditBox::setPosition(Point Location)
{
	agk::SetEditBoxPosition(boxID, Location.getX(), Location.getY());
}

void EditBox::setScissor(Point TopLeft, Point BottomRight)
{
	agk::SetEditBoxScissor(boxID, TopLeft.getX(), TopLeft.getY(), BottomRight.getX(), BottomRight.getY());
}

void EditBox::setSize(float width, float height)
{
	if (width > 0.0f)
	{
		if (height > 0.0f)
			agk::SetEditBoxSize(boxID, width, height);
	}
}

void EditBox::setText(Text Input)
{
	agk::SetEditBoxText(boxID, Input.getString());
}

void EditBox::setTextColor(Text Input)
{
	agk::SetEditBoxTextColor(boxID, Input.getColorRed(), Input.getColorGreen(), Input.getColorBlue());
}

void EditBox::setTextSize(Text Input)
{
	agk::SetEditBoxTextSize(boxID, Input.getSize());
}

void EditBox::setVisible(bool visible)
{
	if (visible)
		agk::SetEditBoxVisible(boxID, 1);
	else
		agk::SetEditBoxVisible(boxID, 0);
}

void EditBox::setWrapText(bool wrapText)
{
	if (wrapText)
		agk::SetEditBoxMultiLine(boxID, 1);
	else
		agk::SetEditBoxMultiLine(boxID, 0);
}