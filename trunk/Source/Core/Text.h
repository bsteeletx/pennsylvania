#pragma once

#include "Point.h"
#include "RGBA.h"
#include "Image.h"
#include <string>

class Image;

class Text
{
public:
	Text();
	~Text();
	Text(const char* textString);
	Text(unsigned int assignedTextNumber, const char* textString);
	Text(std::string textString);
	
	Text& operator= (const Text& newText);
	Text& operator+= (const Text& addText);
	bool operator== (const Text otherText);
	bool operator!= (const Text otherText);
	
	void fixToScreen(bool toScreen);

	char getChar(unsigned int index);
	float getCharAngle(unsigned int index);
	float getCharAngleInRad(unsigned int index);
	unsigned short getCharColorAlpha(unsigned int index);
	unsigned short getCharColorBlue(unsigned int index);
	unsigned short getCharColorGreen(unsigned int index);
	unsigned short getCharColorRed(unsigned int index);
	float getCharX(unsigned int index);
	float getCharY(unsigned int index);
	unsigned short getColorAlpha(void);
	unsigned short getColorBlue(void);
	unsigned short getColorGreen(void);
	unsigned short getColorRed(void);
	unsigned int getDepth(void);
	short getDelimiterIndex(char separator);
	bool getExists(void);
	bool getHitTest(Point Location);
	unsigned int getLength(void);
	float getLineSpacing(void);
	unsigned int getNextID(void);
	float getSize(void);
	float getSpacing(void);
	const char* getString(void);
	float getTotalHeight(void);
	float getTotalWidth(void);
	bool getVisible(void);
	float getX();
	float getY();

	void print(bool newLineAtEnd = true);
	
	void setAlignment(unsigned short mode);
	void setCharAngle(unsigned int index, float angle);
	void setCharAngleInRad(unsigned int index, float angle);
	void setCharColor(unsigned int index, RGBA Value);
	void setCharColorAlpha(unsigned int index, unsigned short alpha);
	void setCharColorBlue(unsigned int index, unsigned short blue);
	void setCharColorGreen(unsigned int index, unsigned short green);
	void setCharColorRed(unsigned int index, unsigned short red);
	void setCharPosition(unsigned int index, Point Location);
	void setCharX(unsigned int index, float x);
	void setCharY(unsigned int index, float y);
	void setColor(RGBA value);
	void setColorAlpha(unsigned short alpha);
	void setColorBlue(unsigned short blue);
	void setColorGreen(unsigned short green);
	void setColorRed(unsigned short red);
	void setDefaultMagFilter(bool linear);
	void setDefaultMinFilter(bool linear);
	void setDepth(unsigned int depth);
	void setExtendedFontImage(Image Object);
	void setFontImage(Image Object);
	void setLineSpacing(float spacing);
	void setMaxWidth(float width);
	void setPosition(Point Location);
	void setPrintColor(RGBA Value);
	void setPrintSize(float size);
	void setPrintSpacing(float space);
	void setScissor(Point TopLeft, Point BottomRight);
	void setSize(float size);
	void setSpacing(float spacing);
	void setString(const char* string);
	void setVisible(bool visible);
	void setX(float x);
	void setY(float y);
	bool splitAtDelimeter(Text *Part1, Text *Part2, char delimeter);

protected:
	unsigned int textNumber;
	char storedString[64];
	
	bool _Alignment(unsigned short mode);
	bool _Color(unsigned short value);
	bool _Depth(unsigned int value);
	bool _Index(unsigned int value);
	bool _NotNegativeFloat(float value);
};