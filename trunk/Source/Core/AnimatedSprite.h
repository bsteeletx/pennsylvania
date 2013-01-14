#pragma once
#include "Sprite.h"
//#include "File.h"

class AnimatedSprite :
	public Sprite
{
public:
	~AnimatedSprite(void);
	AnimatedSprite(void);
	AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, Text Filename, unsigned int assignedImageNumber, unsigned int assignedSpriteNumber = 0);
	AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, Point Begin, Point End, unsigned int assignedSpriteNumber = 0);
	AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, Text Filename, bool blackIsAlpha = false, unsigned int assignedSpriteNumber = 0);	
	AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha = false, unsigned int assignedSpriteNumber = 0);
	AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber = 0);
	AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, unsigned int assignedImageNumber, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber = 0);
	AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, unsigned int spriteNumberToClone);
	AnimatedSprite(File FileToInit, Text PathToParent);
	
	void addFrame(Image NewFrame);
	
	unsigned int getCurrentFrame(void);
	unsigned int getFrameCount(void);
	unsigned short getPlaySpeed(void);
	//bool getVisible(void);

	void play(float fps = 10.0f, bool loop = true, unsigned int start = 1, unsigned int end = 0);
	
	void resume(void);

	void setFrame(unsigned int frame);
	void setPosition(Point Location);
	void setSpeed(float fps);
	//void setVisibile(bool value);
	void stopSprite(void);

private:
	
	void set(unsigned int spriteID, unsigned int width, unsigned int height, unsigned int count);
	bool _Frame(unsigned int frame);
	bool _FPS(float fps);

	unsigned short height;
	unsigned short width;
	unsigned short count;

	float originalY;
	float playSpeed;
};

