#pragma once

#include "Point.h"
#include "Image.h"
#include "RGBA.h"
#include "Text.h"

class VirtualButton
{
public:
	VirtualButton();
	~VirtualButton(void);
	VirtualButton(unsigned short buttonNumber, Point Location, float size);

	bool getExists(void);
	bool getPressed(void);
	bool getReleased(void);
	bool getState(void);

	void setActive(bool active);
	void setAlpha(unsigned short alpha);
	void setColor(RGBA Values);
	void setImageDown(Image Object);
	void setImageUp(Image Object);
	void setPosition(Point Location);
	void setScreenPosition(Point Location, float size);
	void setSize(float size);
	void setText(Text InnerLabel);
	void setVisible(bool visible);

private:
	unsigned short buttonID;
};