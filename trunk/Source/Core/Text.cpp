#include "agk.h"
#include "Text.h"
#include "Image.h"

Text::Text(void)
{
	textNumber = 0;
}

Text::~Text(void)
{
//	if (getExists())
//		agk::DeleteText(textNumber);
}

Text::Text(std::string textString)
{
	char newString[64] = {NULL};

	for (int i = 0; i < textString.size(); i++)
		newString[i] = textString[i];
	
	textNumber = agk::CreateText(newString);
	strcpy(storedString, newString);

	setVisible(false);
}

Text::Text(const char* textString)
{
	textNumber = agk::CreateText(textString);
	strcpy(storedString, textString);

	setVisible(false);
}

Text::Text(unsigned int assignedTextNumber, const char* textString)
{
	agk::CreateText(assignedTextNumber, textString);
	textNumber = assignedTextNumber;

	setVisible(false);
}

Text& Text::operator= (const Text& newText)
{
	Text ReturnText(newText);
	
	if (this != &newText)
	{
		if (getExists())
			agk::DeleteText(textNumber);
		else
			textNumber = ReturnText.textNumber;

		setString(ReturnText.getString());
	}

	return *this;
}

bool Text::operator!= (const Text otherText)
{
	if (strcmp(storedString, otherText.storedString) == 0) //same
		return false;

	return true;
}

Text& Text::operator+= (const Text& newText)
{
	char returnString[32];
	Text AddedText(newText);	

	strcpy(returnString, this->getString());
	strcat(returnString, AddedText.getString());

	setString(returnString);

	return *this;
}

bool Text::operator== (const Text otherText)
{
	if (strcmp(storedString, otherText.storedString) == 0) //same
		return true;

	return false;
}

void Text::fixToScreen(bool toScreen)
{
	if (toScreen)
		agk::FixTextToScreen(textNumber, 1);
	else
		agk::FixTextToScreen(textNumber, 0);
}

char Text::getChar(unsigned int index)
{
	if (_Index(index))
	{
		char textString[64];
		strcpy(textString, getString());
		return textString[index];
	}

	return '`';
}

float Text::getCharAngle(unsigned int index)
{
	if (_Index(index))
		return agk::GetTextCharAngle(textNumber, index);

	return 0.0f;
}

float Text::getCharAngleInRad(unsigned int index)
{
	if (_Index(index))
		return agk::GetTextCharAngleRad(textNumber, index);

	return 0.0f;
}

unsigned short Text::getCharColorAlpha(unsigned int index)
{
	if (_Index(index))
		return (unsigned short) agk::GetTextCharColorAlpha(textNumber, index);

	return 0;
}

unsigned short Text::getCharColorBlue(unsigned int index)
{
	if (_Index(index))
		return (unsigned short) agk::GetTextCharColorBlue(textNumber, index);

	return 0;
}

unsigned short Text::getCharColorGreen(unsigned int index)
{
	if (_Index(index))
		return (unsigned short) agk::GetTextCharColorGreen(textNumber, index);

	return 0;
}

unsigned short Text::getCharColorRed(unsigned int index)
{
	if (_Index(index))
		return (unsigned short) agk::GetTextCharColorRed(textNumber, index);

	return 0;
}

float Text::getCharX(unsigned int index)
{
	if (_Index(index))
		return agk::GetTextCharX(textNumber, index);

	return 0.0f;
}

float Text::getCharY(unsigned int index)
{
	if (_Index(index))
		return agk::GetTextCharY(textNumber, index);

	return 0.0f;
}

unsigned short Text::getColorAlpha(void)
{
	return (unsigned short) agk::GetTextColorAlpha(textNumber);
}

unsigned short Text::getColorBlue(void)
{
	return (unsigned short) agk::GetTextColorBlue(textNumber);
}

unsigned short Text::getColorGreen(void)
{
	return (unsigned short) agk::GetTextColorGreen(textNumber);
}

unsigned short Text::getColorRed(void)
{
	return (unsigned short) agk::GetTextColorRed(textNumber);
}

short Text::getDelimiterIndex(char separator)
{
	for (int i = 0; i < getLength(); i++)
	{
		if (storedString[i] == separator)
			return i;
	}

	return -1;
}

unsigned int Text::getDepth(void)
{
	return agk::GetTextDepth(textNumber);
}

bool Text::getExists(void)
{
	if (agk::GetTextExists(textNumber) == 1)
		return true;

	return false;
}

bool Text::getHitTest(Point Location)
{
	if (agk::GetTextHitTest(textNumber,Location.getX(), Location.getY()) == 1)
		return true;
	
	return false;
}

unsigned int Text::getLength(void)
{
	return strlen(storedString);
}

unsigned int Text::getNextID(void)
{
	int i = 1;

	while (agk::GetTextExists(i) == 1)
		i++;

	return i;
}

float Text::getLineSpacing(void)
{
	return agk::GetTextLineSpacing(textNumber);
}

float Text::getSize(void)
{
	return agk::GetTextSize(textNumber);
}

float Text::getSpacing(void)
{
	return agk::GetTextSpacing(textNumber);
}

const char* Text::getString(void)
{
	return storedString;
}

float Text::getTotalHeight(void)
{
	return agk::GetTextTotalHeight(textNumber);
}

float Text::getTotalWidth(void)
{
	return agk::GetTextTotalWidth(textNumber);
}

bool Text::getVisible(void)
{
	if (agk::GetTextVisible(textNumber) == 1)
		return true;

	return false;
}

float Text::getX(void)
{
	return agk::GetTextX(textNumber);
}

float Text::getY(void)
{
	return agk::GetTextY(textNumber);
}

void Text::print(bool newLineAtEnd)
{
	if (newLineAtEnd)
		agk::Print(getString());
	else
		agk::PrintC(getString());
}

void Text::setAlignment(unsigned short mode)
{
	if (_Alignment(mode))
		agk::SetTextAlignment(textNumber, mode);
}

void Text::setCharAngle(unsigned int index, float angle)
{
	if (_Index(index))
		agk::SetTextCharAngle(textNumber, index, angle);
}

void Text::setCharAngleInRad(unsigned int index, float angle)
{
	if (_Index(index))
		agk::SetTextCharAngleRad(textNumber, index, angle);
}

void Text::setCharColor(unsigned int index, RGBA Value)
{
	agk::SetTextCharColor(textNumber, index, Value.getRed(), Value.getGreen(), Value.getBlue(), Value.getAlpha());
}

void Text::setCharColorAlpha(unsigned int index, unsigned short alpha)
{
	if (_Index(index))
	{
		if (_Color(alpha))
			agk::SetTextCharColorAlpha(textNumber, index, alpha);
	}
}

void Text::setCharColorBlue(unsigned int index, unsigned short blue)
{
	if (_Index(index))
	{
		if (_Color(blue))
			agk::SetTextCharColorBlue(textNumber, index, blue);
	}
}

void Text::setCharColorGreen(unsigned int index, unsigned short green)
{
	if (_Index(index))
	{
		if (_Color(green))
			agk::SetTextCharColorGreen(textNumber, index, green);
	}
}

void Text::setCharColorRed(unsigned index, unsigned short red)
{
	if (_Index(index))
	{
		if (_Color(red))
			agk::SetTextCharColorRed(textNumber, index, red);
	}
}

void Text::setCharX(unsigned index, float x)
{
	if (_Index(index))
		agk::SetTextCharX(textNumber, index, x);
}

void Text::setCharY(unsigned index, float y)
{
	if (_Index(index))
		agk::SetTextCharY(textNumber, index, y);
}

void Text::setColor(RGBA Value)
{
	agk::SetTextColor(textNumber, Value.getRed(), Value.getGreen(), Value.getBlue(), Value.getAlpha());
}

void Text::setColorAlpha(unsigned short alpha)
{
	if (_Color(alpha))
		agk::SetTextColorAlpha(textNumber, alpha);
}

void Text::setColorBlue(unsigned short blue)
{
	if (_Color(blue))
		agk::SetTextColorAlpha(textNumber, blue);
}

void Text::setColorGreen(unsigned short green)
{
	if (_Color(green))
		agk::SetTextColorAlpha(textNumber, green);
}

void Text::setColorRed(unsigned short red)
{
	if (_Color(red))
		agk::SetTextColorAlpha(textNumber, red);
}

void Text::setDefaultMagFilter(bool linear)
{
	if (linear)
		agk::SetDefaultMagFilter(1);
	else
		agk::SetDefaultMagFilter(0);
}

void Text::setDefaultMinFilter(bool linear)
{
	if (linear)
		agk::SetDefaultMinFilter(1);
	else
		agk::SetDefaultMinFilter(0);
}

void Text::setDepth(unsigned int depth)
{
	if (_Depth(depth))
		agk::SetTextDepth(textNumber, depth);
}

void Text::setExtendedFontImage(Image Object)
{
	agk::SetTextExtendedFontImage(textNumber, Object.getImageNumber());
}

void Text::setFontImage(Image Object)
{
	agk::SetTextFontImage(textNumber, Object.getImageNumber());
}

void Text::setLineSpacing(float spacing)
{
	if (_NotNegativeFloat(spacing))
		agk::SetTextLineSpacing(textNumber, spacing);
}

void Text::setMaxWidth(float width)
{
	if (_NotNegativeFloat(width))
		agk::SetTextMaxWidth(textNumber, width);
}

void Text::setPosition(Point Location)
{
	agk::SetTextPosition(textNumber, Location.getX(), Location.getY());
}

void Text::setPrintColor(RGBA Value)
{
	agk::SetPrintColor(Value.getRed(), Value.getGreen(), Value.getBlue(), Value.getAlpha());
}

void Text::setPrintSize(float size)
{
	if (_NotNegativeFloat(size))
		agk::SetPrintSize(size);
}

void Text::setPrintSpacing(float space)
{
	if (_NotNegativeFloat(space))
		agk::SetPrintSpacing(space);
}

void Text::setScissor(Point TopLeft, Point BottomRight)
{
	agk::SetTextScissor(textNumber, TopLeft.getX(), TopLeft.getY(), BottomRight.getX(), BottomRight.getY());
}

void Text::setSize(float size)
{
	if (_NotNegativeFloat(size))
		agk::SetTextSize(textNumber, size);
}

void Text::setSpacing(float spacing)
{
	if (_NotNegativeFloat(spacing))
		agk::SetTextSpacing(textNumber, spacing);
}

void Text::setString(const char* string)
{
	agk::SetTextString(textNumber, string);
	
	strcpy(storedString, string);
}

void Text::setVisible(bool visible)
{
	if (visible)
		agk::SetTextVisible(textNumber, 1);
	else
		agk::SetTextVisible(textNumber, 0);
}

void Text::setX(float x)
{
	agk::SetTextX(textNumber, x);
}

void Text::setY(float y)
{
	agk::SetTextY(textNumber, y);
}

bool Text::splitAtDelimeter(Text *Part1, Text *Part2, char delimeter)
{
	short index = getDelimiterIndex(delimeter);
	short j = 0;

	if (index == -1)
		return false;

	for (int i = 0; i < index; i++)
		Part1->storedString[i] = storedString[i];

	Part1->storedString[index] = '\0';

	for (int i = index + 1; i < getLength(); i++)
		Part2->storedString[j++] = storedString[i];

	Part2->storedString[j] = '\0';

	return true;
}

bool Text::_Alignment(unsigned short mode)
{
	if (mode < 3)
		return true;
	
	return false;
}

bool Text::_Color(unsigned short value)
{
	if (value > 255)
		return false;

	return true;
}

bool Text::_Depth(unsigned int number)
{
	if (number > 10000)
		return false;

	return true;
}

bool Text::_Index(unsigned int value)
{
	if (value >= 0)
	{
		if (value < getLength())
			return true;
	}

	return false;
}

bool Text::_NotNegativeFloat(float value)
{
	if (value >= 0.0f)
		return true;

	return false;
}