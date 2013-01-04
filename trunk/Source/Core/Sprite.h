#pragma once
#include "Image.h"
#include "RGBA.h"
//#include "Point.h"
//#include "Defines.h"
#include "File.h"
#include "Text.h"

class Sprite: public Image
{
public:
	~Sprite(void);
	Sprite(void);
	Sprite (Text Filename, unsigned int assignedImageNumber, unsigned int assignedSpriteNumber);
	Sprite (Point Begin, Point End, unsigned int assignedSpriteNumber = 0);
	Sprite (Text Filename, bool blackIsAlpha = false, unsigned int assignedSpriteNumber = 0); 
	Sprite (unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha = false, unsigned int assignedSpriteNumber = 0);
	Sprite (unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber = 0);
	Sprite (unsigned int assignedImageumber, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber = 0);
	Sprite (File FileToInit);
		
	Sprite& operator= (const Sprite& newSprite);
	Sprite& operator<< (const Image& Object);

	unsigned int clone(void);
	unsigned int clone(unsigned int);
	bool collidedWith(Sprite TestSprite);
	bool collidedWith(unsigned int testSpriteNumber);
	
	void fixToScreen(bool screen = 1);

	bool getActive(void);
	short getAlpha(void);
	float getAngle(void);
	float getAngleInRad(void);
	short getBlue(void);
	int getCollisionGroup(void);
	short getDepth(void);
	float getDistanceFrom(Sprite TestSprite);
	float getDistancePoint1X(void);
	float getDistancePoint1Y(void);
	float getDistancePoint2X(void);
	float getDistancePoint2Y(void);
	bool getExists(void);
	short getGreen(void);
	float getHeight(void);
	bool getHitTest(Point Location);
	bool getIsInBox(Point TopLeft, Point BottomRight);
	bool getIsInCircle(Point CenterOfCircle, float radius);
	int getPixelFromX(float x); 
	int getPixelFromY(float y); 
	Point getPosition(void);
	short getRed(void);
	unsigned int getSpriteNumber(void);
	bool getVisible(void);
	float getWidth(void);
	float getX(void);
	float getXByOffset(void);
	float getXFromPixel(int x);
	float getY(void);
	float getYByOffset(void);
	float getYFromPixel(int y);

	void resetUV(void);

	void setActive(bool isActive);
	void setAlpha(short alpha); 
	void setAngle(float angle); 
	void setAngleInRad(float rad);
	void setBlue(short blue); 
	void setColor(RGBA Values);
	void setCollisionGroup(int groupID);
	void setDepth(short depth); 
	void setFlip(bool horizontal, bool vertical);
	void setGreen(short green); 
	void setImage(Image newImage, bool reshape = false);
	void setOffset(float x, float y);
	void setPosition(float x, float y);
	void setPosition(Point Locaiton);
	void setPositionByOffset(float x, float y);
	void setPositionByOffset(Point Location);
	void setRed(short red);
	void setScale(float x, float y);
	void setScaleByOffset(float x, float y);
	void setScissor(Point TopLeft, Point BottomRight);
	void setSize(float width = -1.0f, float height = -1.0f);
	void setSnap(bool snap = true);
	void setTransparencySetting(short setting);
	void setUV(Point UV1, Point UV2, Point UV3, Point UV4);
	void setUVBorder(float border = 0.5f);
	void setUVOffset(float u, float v);
	void setUVScale(float u, float v);
	void setVisible(bool visible);
	void setX(float x);
	void setY(float y);

	void toggleVisiblity(void);

protected:
	unsigned int spriteNumber;
	RGBA ColorValues;
	
private:
	void create(unsigned int assignedSpriteNumber = 0);

	bool _Depth(short value);
	bool _SpriteNumber(unsigned int number);
	bool _TransparencySetting(short setting);
	bool _UVBorder(float border);
};