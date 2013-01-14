#include "Sprite.h"
#include "agk.h"

Sprite::~Sprite(void)
{
	//if (getExists())
		//agk::DeleteSprite(spriteNumber);
}

Sprite::Sprite(void)
{
	spriteNumber = agk::CreateSprite(0);
}

Sprite::Sprite(Text Filename, unsigned int assignedImageNumber, unsigned int assignedSpriteNumber)
	: Image(Filename, assignedImageNumber)
{
	create(assignedSpriteNumber);
}

Sprite::Sprite(Point Begin, Point End, unsigned int assignedSpriteNumber)
	: Image(Begin, End)
{
	create(assignedSpriteNumber);
}

Sprite::Sprite(Text Filename, bool blackIsAlpha, unsigned int assignedSpriteNumber)
	: Image(Filename, blackIsAlpha)
{
	create(assignedSpriteNumber);
}

Sprite::Sprite(unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha, unsigned int assignedSpriteNumber)
	: Image(assignedImageNumber, Filename, blackIsAlpha)
{
	create(assignedSpriteNumber);
}

Sprite::Sprite(unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber)
	: Image(SubImageFilename, parentImage)
{
	create(assignedSpriteNumber);
}

Sprite::Sprite(unsigned int assignedImageNumber, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber)
	: Image(assignedImageNumber, parentImage, SubImageFilename)
{
	create(assignedSpriteNumber);
}

Sprite::Sprite(File FileToInit, Text PathToParent)
	: Image(FileToInit, PathToParent)
{
	create();

	FileToInit.reOpen();

	while(!FileToInit.FileEOF())
	{
		Text Line = FileToInit.getLine();
		Text Start;
		Text End;

		Line.splitAtDelimeter(&Start, &End, ':');

		if (Start == Text("Size"))
		{
			setSize(atof(End.getString()));
			break;
		}
	}

	FileToInit.close();
}

Sprite& Sprite::operator= (const Sprite &NewSprite)
{	
	if (this != &NewSprite)
	{
		if (getExists())
			agk::DeleteSprite(spriteNumber);
		spriteNumber = NewSprite.spriteNumber;
		imageNumber = NewSprite.imageNumber;
		//Image NewImage(newSprite.imageNumber);
		//imageNumber = NewImage.getImageNumber();
	}

	return *this;
}

Sprite& Sprite::operator<< (const Image& Object)
{
	Image TempImage(Object);

	if (getExists())
		agk::DeleteSprite(spriteNumber);

	spriteNumber = agk::CreateSprite(TempImage.getImageNumber());
	
	return *this;
}

void Sprite::fixToScreen(bool screen)
{
	if (screen)
		agk::FixSpriteToScreen(spriteNumber, 1);
	else
		agk::FixSpriteToScreen(spriteNumber, 0);
}

bool Sprite::getActive(void)
{
	if (agk::GetSpriteActive(spriteNumber) == 1)
		return true;
	else
		return false;
}

short Sprite::getAlpha(void)
{
	return (short) agk::GetSpriteColorAlpha(spriteNumber);
}

float Sprite::getAngle(void)
{
	return agk::GetSpriteAngle(spriteNumber);
}

float Sprite::getAngleInRad(void)
{
	return agk::GetSpriteAngleRad(spriteNumber);
}

short Sprite::getBlue(void)
{
	return (short) agk::GetSpriteColorBlue(spriteNumber);
}

Point Sprite::getPosition(void)
{
	return Point(getX(), getY());
}

bool Sprite::collidedWith(Sprite TestSprite)
{
	if (agk::GetSpriteCollision(spriteNumber, TestSprite.getSpriteNumber()) == 1)
		return true;
	else
		return false;
}

bool Sprite::collidedWith(unsigned int testSpriteNumber)
{
	if (agk::GetSpriteCollision(spriteNumber, testSpriteNumber) == 1)
		return true;
	else
		return false;
}

int Sprite::getCollisionGroup(void)
{
	return agk::GetSpriteGroup(spriteNumber);
}

void Sprite::setCollisionGroup(int group)
{
	agk::SetSpriteGroup(spriteNumber, group);
}

short Sprite::getDepth(void)
{
	return (short) agk::GetSpriteDepth(spriteNumber);
}

float Sprite::getDistanceFrom(Sprite TestSprite)
{
	return agk::GetSpriteDistance(spriteNumber, TestSprite.getSpriteNumber());
}

float Sprite::getDistancePoint1X(void)
{
	return agk::GetSpriteDistancePoint1X();
}

float Sprite::getDistancePoint1Y(void)
{
	return agk::GetSpriteDistancePoint1Y();
}

float Sprite::getDistancePoint2X(void)
{
	return agk::GetSpriteDistancePoint2X();
}

float Sprite::getDistancePoint2Y(void)
{
	return agk::GetSpriteDistancePoint2Y();
}

bool Sprite::getExists(void)
{
	if (agk::GetSpriteExists(spriteNumber) == 1)
		return true;
	else
		return false;
}

short Sprite::getGreen(void)
{
	return (short) agk::GetSpriteColorGreen(spriteNumber);
}

float Sprite::getHeight(void)
{
	return agk::GetSpriteHeight(spriteNumber);
}

bool Sprite::getHitTest(Point Location)
{
	if (agk::GetSpriteHitTest(spriteNumber, Location.getX(), Location.getY()) == 1)
		return true;
	else
		return false;
}

bool Sprite::getIsInBox(Point TopLeft, Point BottomRight)
{
	if (agk::GetSpriteInBox(spriteNumber, TopLeft.getX(), TopLeft.getY(), BottomRight.getX(), BottomRight.getY()) == 1)
		return true;
	else
		return false;
}

bool Sprite::getIsInCircle(Point CenterOfCircle, float radius)
{
	if (agk::GetSpriteInCircle(spriteNumber, CenterOfCircle.getX(), CenterOfCircle.getY(), radius) == 1)
		return true;
	else
		return false;
}

int Sprite::getPixelFromX(float x)
{
	return agk::GetSpritePixelFromX(spriteNumber, x);
}

int Sprite::getPixelFromY(float y)
{
	return agk::GetSpritePixelFromY(spriteNumber, y);
}

short Sprite::getRed(void)
{
	return (short) agk::GetSpriteColorRed(spriteNumber);
}

unsigned int Sprite::getSpriteNumber(void)
{
	return spriteNumber;
}

bool Sprite::getVisible(void)
{
	if (agk::GetSpriteVisible(spriteNumber) == 1)
		return true;
	else
		return false;
}

float Sprite::getWidth(void)
{
	return agk::GetSpriteWidth(spriteNumber);
}

float Sprite::getX(void)
{
	return agk::GetSpriteX(spriteNumber);
}

float Sprite::getXByOffset(void)
{
	return agk::GetSpriteXByOffset(spriteNumber);
}

float Sprite::getXFromPixel(int x)
{
	return agk::GetSpriteXFromPixel(spriteNumber, x);
}

float Sprite::getY(void)
{
	return agk::GetSpriteY(spriteNumber);
}

float Sprite::getYByOffset(void)
{
	return agk::GetSpriteYByOffset(spriteNumber);
}

float Sprite::getYFromPixel(int y)
{
	return agk::GetSpriteYFromPixel(spriteNumber, y);
}

void Sprite::resetUV(void)
{
	agk::ResetSpriteUV(spriteNumber);
}

void Sprite::setActive(bool isActive)
{
	agk::SetSpriteActive(spriteNumber, isActive);
}

void Sprite::setAlpha(short alpha)
{
	ColorValues.setAlpha(alpha);
	agk::SetSpriteColorAlpha(spriteNumber, ColorValues.getAlpha());
}

void Sprite::setAngle(float angle)
{
	agk::SetSpriteAngle(spriteNumber, angle);
}

void Sprite::setAngleInRad(float rad)
{
	agk::SetSpriteAngleRad(spriteNumber, rad);
}

void Sprite::setBlue(short blue)
{
	ColorValues.setBlue(blue);
	agk::SetSpriteColorBlue(spriteNumber, ColorValues.getBlue());
}

void Sprite::setColor(RGBA Values)
{

	agk::SetSpriteColor(spriteNumber, Values.getRed(), Values.getGreen(), Values.getBlue(), Values.getAlpha());
}

void Sprite::setDepth(short depth)
{
	if (_Depth(depth))
		agk::SetSpriteDepth(spriteNumber, depth);
}

void Sprite::setFlip(bool horizontal, bool vertical)
{
	agk::SetSpriteFlip(spriteNumber, horizontal, vertical);
}

void Sprite::setGreen(short green)
{
	if (_ColorChannel(green))
		agk::SetSpriteColorGreen(spriteNumber, green);
}

void Sprite::setImage(Image newImage, bool reshape)
{
	if (reshape)
		agk::SetSpriteImage(spriteNumber, newImage.getImageNumber(), 1);
	else
		agk::SetSpriteImage(spriteNumber, newImage.getImageNumber());
}

void Sprite::setOffset(float x, float y)
{
	agk::SetSpriteOffset(spriteNumber, x, y);
}

void Sprite::setPosition(float x, float y)
{
	setPosition(Point(x, y));
}

void Sprite::setPosition(Point Location)
{
	agk::SetSpritePosition(spriteNumber, Location.getX(), Location.getY());
}

void Sprite::setPositionByOffset(float x, float y)
{
	setPositionByOffset(Point(x, y));
}

void Sprite::setPositionByOffset(Point Location)
{
	agk::SetSpritePositionByOffset(spriteNumber, Location.getX(), Location.getY());
}

void Sprite::setRed(short red)
{
	if (_ColorChannel(red))
		agk::SetSpriteColorRed(spriteNumber, red);
}

void Sprite::setScale(float x, float y)
{
	agk::SetSpriteScale(spriteNumber, x, y);
}

void Sprite::setScaleByOffset(float x, float y)
{
	agk::SetSpriteScaleByOffset(spriteNumber, x, y);
}

void Sprite::setScissor(Point TopLeft, Point BottomRight)
{
	agk::SetSpriteScissor(spriteNumber, TopLeft.getX(), TopLeft.getY(), BottomRight.getX(), BottomRight.getY());
}

void Sprite::setSize(float width, float height)
{
	agk::SetSpriteSize(spriteNumber, width, height);
}

void Sprite::setSnap(bool snap)
{
	agk::SetSpriteSnap(spriteNumber, snap);
}

void Sprite::setTransparencySetting(short setting)
{
	if (_TransparencySetting(setting))
		agk::SetSpriteTransparency(spriteNumber, setting);
}

void Sprite::setUV(Point UV1, Point UV2, Point UV3, Point UV4)
{
	agk::SetSpriteUV(spriteNumber, UV1.getX(), UV1.getY(), UV2.getX(), UV2.getY(), UV3.getX(), UV3.getY(), UV4.getX(), UV4.getY());
}

void Sprite::setUVBorder(float border)
{
	if (_UVBorder(border))
		agk::SetSpriteUVBorder(spriteNumber, border);
}

void Sprite::setUVOffset(float u, float v)
{
	agk::SetSpriteUVOffset(spriteNumber, u, v);
}

void Sprite::setUVScale(float u, float v)
{
	agk::SetSpriteUVScale(spriteNumber, u, v);
}

void Sprite::setVisible(bool visible)
{
	agk::SetSpriteVisible(spriteNumber, visible);
}

void Sprite::setX(float x)
{
	agk::SetSpriteX(spriteNumber, x);
}

void Sprite::setY(float y)
{
	agk::SetSpriteY(spriteNumber, y);
}

void Sprite::toggleVisiblity(void)
{
	if (this->getVisible() == 0)
		this->setVisible(true);
	else
		this->setVisible(false);
}

unsigned int Sprite::clone(void)
{
	return agk::CloneSprite(spriteNumber);
}

unsigned int Sprite::clone(unsigned int spriteToClone)
{
	return agk::CloneSprite(spriteToClone);
}

void Sprite::create(unsigned int assignedSpriteNumber)
{
	if (!assignedSpriteNumber)
		spriteNumber = agk::CreateSprite(getImageNumber());
	else
	{
		spriteNumber = assignedSpriteNumber;
		agk::CreateSprite(spriteNumber, getImageNumber());
	}
}

bool Sprite::_Depth(short value)
{
	if (value >= 0)
	{
		if (value <= 10000)
			return true;
	}

	return false;
}

bool Sprite::_SpriteNumber(unsigned int number)
{
	if (number != 0)
		return true;

	return false;
}

bool Sprite::_TransparencySetting(short setting)
{
	if (setting >= 0)
	{
		if (setting <= 2)
			return true;
	}

	return false;
}

bool Sprite::_UVBorder(float border)
{
	if (border >= 0.0f)
	{
		if (border <= 1.0f)
			return true;
	}

	return false;
}