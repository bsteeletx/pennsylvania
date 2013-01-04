#include "TestCard.h"

TestCard::~TestCard()
{
}

TestCard::TestCard()
{
}

TestCard::TestCard (unsigned int assignedImageNumber, unsigned int assignedSpriteNumber, short mode)
	: PhysicsSprite(assignedImageNumber, assignedSpriteNumber, mode)
{
}

TestCard::TestCard (Point Begin, Point End, unsigned int assignedSpriteNumber, short mode)
	: PhysicsSprite(Begin, End, assignedSpriteNumber, mode)
{
}

TestCard::TestCard (Text Filename, bool blackIsAlpha, unsigned int assignedSpriteNumber, short mode)
	: PhysicsSprite(Filename, blackIsAlpha, assignedSpriteNumber, mode)
{
}

TestCard::TestCard (unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha, unsigned int assignedSpriteNumber, short mode)
	: PhysicsSprite(assignedImageNumber, Filename, blackIsAlpha, assignedSpriteNumber, mode)
{
}

TestCard::TestCard (unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber, short mode)
	: PhysicsSprite(parentImage, SubImageFilename, assignedSpriteNumber, mode)
{
}

TestCard::TestCard (unsigned int assignedImageNumber, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber, short mode)
	: PhysicsSprite(assignedImageNumber, parentImage, SubImageFilename, assignedSpriteNumber, mode)
{
}