#pragma once

#include "PhysicsSprite.h"

class TestCard : public PhysicsSprite
{
public:
	~TestCard();
	TestCard();
	TestCard (unsigned int assignedImageNumber, unsigned int assignedSpriteNumber = 0, short mode = 2);
	TestCard (Point Begin, Point End, unsigned int assignedSpriteNumber = 0, short mode = 2);
	TestCard (Text Filename, bool blackIsAlpha = false, unsigned int assignedSpriteNumber = 0, short mode = 2); 
	TestCard (unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha = false, unsigned int assignedSpriteNumber = 0, short mode = 2);
	TestCard (unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber = 0, short mode = 2);
	TestCard (unsigned int assignedImageNumber, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber = 0, short mode = 2);
}