#pragma once
#include "Point.h"
#include "Image.h"
#include "RGBA.h"
#include "Text.h"
class EditBox
{
public:
	EditBox();
	~EditBox(void);
	EditBox(unsigned int boxNumber);

	void fixToScren(bool toScreen);

	bool getActive(void);
	bool getChanged(void);
	bool getExists(void);
	bool getHasFocus(void);
	float getHeight(void);
	unsigned int getLines(void);
	Text getText(void);
	bool getVisible(void);
	float getWidth(void);
	float getX(void);
	float getY(void);

	void setActive(bool active);
	void setBackgroundColor(RGBA Values);
	void setBackgroundImage(Image Object);
	void setBorderColor(RGBA Values);
	void setBorderImage(Image Object);
	void setBorderSize(float size);
	void setCursorBlinkTime(float speedInSeconds);
	void setCursorColor(RGBA Values);
	void setCursorWidth(float width);
	void setDepth(unsigned int depth);
	void setFocus(bool focus);
	void setFontImage(Image Object);
	void setMaxChars(unsigned int max);
	void setMaxLines(unsigned int max);
	void setPosition(Point Location);
	void setScissor(Point TopLeft, Point BottomRight);
	void setSize(float width, float height);
	void setText(Text Input);
	void setTextColor(Text Input);
	void setTextSize(Text Input);
	void setVisible(bool visible);
	void setWrapText(bool wrapText);

private:
	unsigned int boxID;
};