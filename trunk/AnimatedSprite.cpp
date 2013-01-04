#include "agk.h"
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
	: Sprite()
{
}

AnimatedSprite::~AnimatedSprite()
{
}

AnimatedSprite::AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, Text Filename, unsigned int assignedImageNumber, unsigned int assignedSpriteNumber)
	: Sprite(Filename, assignedImageNumber, assignedSpriteNumber)
{
	set(spriteNumber, width, height, count);
}

AnimatedSprite::AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, Point Begin, Point End, unsigned int assignedSpriteNumber)
	: Sprite(Begin, End, assignedSpriteNumber)
{
	set(spriteNumber, width, height, count);
}

AnimatedSprite::AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, Text Filename, bool blackIsAlpha, unsigned int assignedSpriteNumber)
	: Sprite(Filename, blackIsAlpha, assignedSpriteNumber)
{
	set(spriteNumber, width, height, count);
}

AnimatedSprite::AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha, unsigned int assignedSpriteNumber)
	: Sprite(assignedImageNumber, Filename, blackIsAlpha, assignedSpriteNumber)
{
	set(spriteNumber, width, height, count);
}

AnimatedSprite::AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber)
	: Sprite(parentImage, SubImageFilename, assignedSpriteNumber)
{
	set(spriteNumber, width, height, count);
}

AnimatedSprite::AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, unsigned int assignedImageNumber, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber)
	: Sprite(assignedImageNumber, parentImage, SubImageFilename, assignedSpriteNumber)
{
	set(spriteNumber, width, height, count);
}

AnimatedSprite::AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, unsigned int spriteNumberToClone)
	: Sprite()
{
	this->spriteNumber = clone(spriteNumberToClone);
	set(spriteNumber, width, height, count);
}

AnimatedSprite::AnimatedSprite(File FileToInit)
	: Sprite(FileToInit)
{
	
	FileToInit.reOpen();

	while(!FileToInit.FileEOF())
	{
		Text Line = FileToInit.getLine();
		Text Start;
		Text End;

		Line.splitAtDelimeter(&Start, &End, ':');

		if (Start == Text("Height"))
			height = agk::Val(End.getString());
		else if (Start == Text("Width"))
			width = agk::Val(End.getString());
		else if (Start == Text("Count"))
			count = agk::Val(End.getString());
		else if (Start == Text("PlaySpeed"))
		{
			if (End == Text(""))
				continue;
			else
				playSpeed = agk::Val(End.getString());
		}
	}

	set(spriteNumber, width, height, count);

	FileToInit.close();
}

void AnimatedSprite::addFrame(Image NewFrame)
{
	agk::AddSpriteAnimationFrame(spriteNumber, NewFrame.getImageNumber());
}

unsigned int AnimatedSprite::getCurrentFrame(void)
{
	return agk::GetSpriteCurrentFrame(spriteNumber);
}

unsigned int AnimatedSprite::getFrameCount(void)
{
	return agk::GetSpriteFrameCount(spriteNumber);
}

/*bool AnimatedSprite::getVisible(void)
{
	if (getY() <= 100.0f)
		return true;

	return false;
}*/

unsigned short AnimatedSprite::getPlaySpeed(void)
{
	return playSpeed;
}

void AnimatedSprite::play(float fps, bool loop, unsigned int start, unsigned int end)
{
	if (_Frame(start))
	{
		if (_Frame(end))
		{
			if (_FPS(fps))
				agk::PlaySprite(spriteNumber, fps, loop, start, end);
		}
	}
}

void AnimatedSprite::resume(void)
{
	agk::ResumeSprite(spriteNumber);
}

void AnimatedSprite::setFrame(unsigned int frame)
{
	if (_Frame(frame))
		agk::SetSpriteFrame(spriteNumber, frame);
}

void AnimatedSprite::setPosition(Point Location)
{
	originalY = Location.getY();
	Sprite::setPosition(Location);
}

void AnimatedSprite::setSpeed(float fps)
{
	if (_FPS(fps))
		agk::SetSpriteSpeed(spriteNumber, fps);
}

/*void AnimatedSprite::setVisibile(bool value)
{
	if (value)
		setY(200.0f);
	else
		setY(originalY);
}*/

void AnimatedSprite::stopSprite(void)
{
	agk::StopSprite(spriteNumber);
}

void AnimatedSprite::set(unsigned int spriteID, unsigned int width, unsigned int height, unsigned int count)
{
	if (width > 0)
	{
		if (height > 0)
		{
			if (count > 0)
			{
				agk::SetSpriteAnimation(spriteNumber, width, height, count);
				this->height = height;
				this->width = width;
				this->count = count;
			}
		}
	}
}

bool AnimatedSprite::_Frame(unsigned int frame)
{
	if (frame != 0)
	{
		if (frame <= getFrameCount())
			return true;
	}

	return false;
}

bool AnimatedSprite::_FPS(float fps)
{
	if (fps > 0.0f)
		return true;

	return false;
}