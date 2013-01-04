#include "agk.h"
#include "PhysicsSprite.h"

PhysicsSprite::~PhysicsSprite()
{
}

PhysicsSprite::PhysicsSprite()
{
}

/*PhysicsSprite::PhysicsSprite(unsigned int assignedImageNumber, unsigned int assignedSpriteNumber, short mode)
	: Sprite(assignedImageNumber, assignedSpriteNumber)
{
	setOn(mode);
}*/

PhysicsSprite::PhysicsSprite (Point Begin, Point End, unsigned int assignedSpriteNumber, short mode)
	: Sprite(Begin, End, assignedSpriteNumber)
{
	setOn(mode);
}

PhysicsSprite::PhysicsSprite (Text Filename, bool blackIsAlpha, unsigned int assignedSpriteNumber, short mode)
	: Sprite(Filename, blackIsAlpha, assignedSpriteNumber)
{
	setOn(mode);
}

PhysicsSprite::PhysicsSprite (unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha, unsigned int assignedSpriteNumber, short mode)
	: Sprite(assignedImageNumber, Filename, blackIsAlpha, assignedSpriteNumber)
{
	setOn(mode);
}

PhysicsSprite::PhysicsSprite (unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber, short mode)
	: Sprite(parentImage, SubImageFilename, assignedSpriteNumber)
{
	setOn(mode);
}

PhysicsSprite::PhysicsSprite (unsigned int assignedImageNumber, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber, short mode)
	: Sprite(assignedImageNumber, parentImage, SubImageFilename, assignedSpriteNumber)
{
	setOn(mode);
}

/*PhysicsSprite& PhysicsSprite::operator=(const PhysicsSprite& TempSprite)
{

}*/

void PhysicsSprite::addShapeBox(Point TopLeft, Point BottomRight, float angleInRads)
{
	agk::AddSpriteShapeBox(spriteNumber, TopLeft.getX(), TopLeft.getY(), BottomRight.getX(), BottomRight.getY(), angleInRads);
}

void PhysicsSprite::addShapeCircle(Point CenterOfCircle, float radius)
{
	agk::AddSpriteShapeCircle(spriteNumber, CenterOfCircle.getX(), CenterOfCircle.getY(), radius);
}

void PhysicsSprite::addShapePolygon(unsigned int numOfPoints, unsigned int pointIndex, Point Location)
{
	if (_ShapePolygon(numOfPoints, pointIndex))
		agk::AddSpriteShapePolygon(spriteNumber, numOfPoints, pointIndex, Location.getX(), Location.getY());
}

void PhysicsSprite::reCalculateCOM(void)
{
	agk::CalculateSpritePhysicsCOM(spriteNumber);
}

void PhysicsSprite::clearShapes(void)
{
	agk::ClearSpriteShapes(spriteNumber);
}

bool PhysicsSprite::collidedWith(Sprite TestSprite)
{
	if (agk::GetPhysicsCollision(spriteNumber, TestSprite.getSpriteNumber()) == 1)
		return true;
	else
		return false;
}

float PhysicsSprite::getAngularVelocity(void)
{
	return agk::GetSpritePhysicsAngularVelocity(spriteNumber);
}

float PhysicsSprite::getCollisionWorldX(void)
{
	return agk::GetPhysicsCollisionWorldX();
}

float PhysicsSprite::getCollisionWorldY(void)
{
	return agk::GetPhysicsCollisionWorldY();
}

float PhysicsSprite::getCollisionX(void)
{
	return agk::GetPhysicsCollisionX();
}

float PhysicsSprite::getCollisionY(void)
{
	return agk::GetPhysicsCollisionY();
}

int PhysicsSprite::getGroup(void)
{
	return agk::GetSpriteGroup(spriteNumber);
}

unsigned int PhysicsSprite::getHitCategory(unsigned short categoryTest, Point Location)
{
	return agk::GetSpriteHitCategory(categoryTest, Location.getX(), Location.getY());
}

unsigned int PhysicsSprite::getHitGroup(Point Location)
{
	return agk::GetSpriteHitGroup(getGroup(), Location.getX(), Location.getY());
}

bool PhysicsSprite::getIsInCategory(unsigned short categoryNum)
{
	return category[categoryNum];
}

bool PhysicsSprite::getIsInCollisionGroup(unsigned short collisionNum)
{
	return collision[collisionNum];
}

float PhysicsSprite::getMass(void)
{
	return agk::GetSpritePhysicsMass(spriteNumber);
}

bool PhysicsSprite::getUsingPhysics(void)
{
	return usingPhysics;
}

float PhysicsSprite::getVelocityX(void)
{
	return agk::GetSpritePhysicsVelocityX(spriteNumber);
}

float PhysicsSprite::getVelocityY(void)
{
	return agk::GetSpritePhysicsVelocityY(spriteNumber);
}

void PhysicsSprite::setAngularDamping(float damp)
{
	if (_ZeroToOneFloat(damp))
		agk::SetSpritePhysicsAngularDamping(spriteNumber, damp);
}

void PhysicsSprite::setAngularImpulse(float impulse)
{
	agk::SetSpritePhysicsAngularImpulse(spriteNumber, impulse);
}

void PhysicsSprite::setAngularVelocity(float aVelocity)
{
	agk::SetSpritePhysicsAngularVelocity(spriteNumber, aVelocity);
}

void PhysicsSprite::setBounciness(float bounciness)
{
	if (_ZeroToOneFloat(bounciness))
		agk::SetSpritePhysicsRestitution(spriteNumber, bounciness);
}

void PhysicsSprite::setCanRotate(bool canRotate)
{
	agk::SetSpritePhysicsCanRotate(spriteNumber, canRotate);
}

void PhysicsSprite::setCategoryBit(unsigned short categoryNum, bool inCategory)
{
	if (_ZeroToFifteen(categoryNum))
	{
		agk::SetSpriteCategoryBit(spriteNumber, categoryNum, inCategory);
		category[categoryNum] = inCategory;
	}
}

void PhysicsSprite::setCategoryByBit(unsigned int bits)
{
	if (_ZeroToMaxInt(bits, (2^16)-1))
	{
		int remainder = bits;

		for (int i = 15; i < 0; i--)
		{
			int j = 2^i;

			if (remainder / j > 0)
			{
				category[i] = true;
				remainder -= j;
			}
			else
				category[i] = false;
		}

		agk::SetSpriteCategoryBits(spriteNumber, bits);
	}
}

void PhysicsSprite::setCollideBit(unsigned short collisionNum, bool inCollision)
{
	if (_ZeroToFifteen(collisionNum))
	{
		agk::SetSpriteCollideBit(spriteNumber, collisionNum, inCollision);
		collision[collisionNum] = inCollision;
	}
}

void PhysicsSprite::setCollideByBit(unsigned int bits)
{
	if (_ZeroToMaxInt(bits, (2^16)-1))
	{

		int remainder = bits;

		for (int i = 15; i < 0; i--)
		{
			int j = 2^i;

			if (remainder / j > 0)
			{
				collision[i] = true;
				remainder -= j;
			}
			else
				collision[i] = false;
		}

		agk::SetSpriteCollideBits(spriteNumber, bits);
	}
}

void PhysicsSprite::setCOM(Point COM)
{
	agk::SetSpritePhysicsCOM(spriteNumber, COM.getX(), COM.getY());
}

void PhysicsSprite::setDamping(float damp)
{
	if (_ZeroToOneFloat(damp))
		agk::SetSpritePhysicsDamping(spriteNumber, damp);
}

void PhysicsSprite::setForce(Vector Force)
{
	agk::SetSpritePhysicsForce(spriteNumber, Force.getStartPointX(), Force.getStartPointY(), Force.getEndPointX(), Force.getEndPointY());
}

void PhysicsSprite::setFriction(float friction)
{
	if (_ZeroToOneFloat(friction))
		agk::SetSpritePhysicsFriction(spriteNumber, friction);
}

void PhysicsSprite::setGroup(int group)
{
	agk::SetSpriteGroup(spriteNumber, group);
}

void PhysicsSprite::setImpulse(Vector Impulse)
{
	agk::SetSpritePhysicsImpulse(spriteNumber, Impulse.getStartPointX(), Impulse.getStartPointY(), Impulse.getEndPointX(), Impulse.getEndPointY());
}

void PhysicsSprite::setIsBullet(bool isBullet)
{
	if (isBullet)
		agk::SetSpritePhysicsIsBullet(spriteNumber, 1);
	else
		agk::SetSpritePhysicsIsBullet(spriteNumber, 0);
}

void PhysicsSprite::setIsSensor(bool isSensor)
{
	if(isSensor)
		agk::SetSpritePhysicsIsSensor(spriteNumber, 1);
	else
		agk::SetSpritePhysicsIsSensor(spriteNumber, 0);
}

void PhysicsSprite::setMass(float massInKG)
{
	if (_UnsignedFloat(massInKG))
		agk::SetSpritePhysicsMass(spriteNumber, massInKG);
}

void PhysicsSprite::setTorque(float torque)
{
	agk::SetSpritePhysicsTorque(spriteNumber, torque);
}

void PhysicsSprite::setVelocity(float xVelocity, float yVelocity)
{
	agk::SetSpritePhysicsVelocity(spriteNumber, xVelocity, yVelocity);
}

void PhysicsSprite::setShape(short shapeType)
{
	if (_Shape(shapeType))
		agk::SetSpriteShape(spriteNumber, shapeType);
}

void PhysicsSprite::setShapeBox(Point TopLeft, Point BottomRight, float angleInRads)
{
	agk::SetSpriteShapeBox(spriteNumber, TopLeft.getX(), TopLeft.getY(), BottomRight.getX(), BottomRight.getY(), angleInRads);
}

void PhysicsSprite::setShapeCircle(Point CenterOfCircle, float radius)
{
	agk::SetSpriteShapeCircle(spriteNumber, CenterOfCircle.getX(), CenterOfCircle.getY(), radius);
}

void PhysicsSprite::setShapePolygon(short numOfPoints, short pointIndex, Point Location)
{
	if (_ShapePolygon(numOfPoints, pointIndex))
		agk::SetSpriteShapePolygon(spriteNumber, numOfPoints, pointIndex, Location.getX(), Location.getY());
}

void PhysicsSprite::setOff(void)
{
	agk::SetSpritePhysicsOff(spriteNumber);
}

void PhysicsSprite::setOn(short mode)
{
	if(_Mode(mode))
		agk::SetSpritePhysicsOn(spriteNumber, mode);
}

bool PhysicsSprite::_Mode(short value)
{
	if (value > 0)
	{
		if (value <= 3)
			return true;
	}

	return false;
}

bool PhysicsSprite::_Shape(short shapeType)
{
	if (shapeType >= 0)
	{
		if (shapeType <= 3)
			return true;
	}

	return false;
}

bool PhysicsSprite::_ShapePolygon(short numOfPoints, short pointIndex)
{
	if (numOfPoints > 0)
	{
		if (pointIndex > 0)
		{
			if (numOfPoints >= pointIndex)
				return true;
		}
	}

	return false;
}

bool PhysicsSprite::_UnsignedFloat(float value)
{
	if (value >= 0.0f)
		return true;
	else
		return false;
}

bool PhysicsSprite::_ZeroToFifteen(unsigned int value)
{
	if (value < 16)
		return true;

	return false;
}

bool PhysicsSprite::_ZeroToMaxInt(unsigned int value, unsigned int maxValue)
{
	if (value < maxValue)
		return true;

	return false;
}

bool PhysicsSprite::_ZeroToOneFloat(float value)
{
	if (value >= 0.0f)
	{
		if (value <= 1.0f)
			return true;
	}

	return false;
}