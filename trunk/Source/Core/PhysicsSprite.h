#pragma once
//#include "Text.h"
#include "Sprite.h"
//#include "Image.h"
#include "Vector.h"

class PhysicsSprite :
	public Sprite
{
public:
	~PhysicsSprite(void);
	PhysicsSprite(void);
	//PhysicsSprite (unsigned int assignedImageNumber, unsigned int assignedSpriteNumber = 0, short mode = 2);
	PhysicsSprite (Point Begin, Point End, unsigned int assignedSpriteNumber = 0, short mode = 2);
	PhysicsSprite (Text Filename, bool blackIsAlpha = false, unsigned int assignedSpriteNumber = 0, short mode = 2); 
	PhysicsSprite (unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha = false, unsigned int assignedSpriteNumber = 0, short mode = 2);
	PhysicsSprite (unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber = 0, short mode = 2);
	PhysicsSprite (unsigned int assignedImageNumber, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber = 0, short mode = 2);

	//PhysicsSprite& operator=(const PhysicsSprite& TempSprite);

	void addShapeBox(Point TopLeft, Point BottomRight, float angeInRads);
	void addShapeCircle(Point CenterOfCircle, float radius);
	void addShapePolygon(unsigned int numOfPoints, unsigned int pointIndex, Point Location);

	void reCalculateCOM(void);
	void clearShapes(void);
	bool collidedWith(Sprite TestSprite);
	
	float getAngularVelocity(void);
	float getCollisionWorldX(void);
	float getCollisionWorldY(void);
	float getCollisionX(void);
	float getCollisionY(void);
	int getGroup(void);
	unsigned int getHitCategory(unsigned short categoryTest, Point Location);
	unsigned int getHitGroup(Point Location);
	bool getIsInCategory(unsigned short categoryNum);
	bool getIsInCollisionGroup(unsigned short collisionNum);
	float getMass(void);
	bool getUsingPhysics(void);
	float getVelocityX(void);
	float getVelocityY(void);

	void setAngularDamping(float damp);
	void setAngularImpulse(float impulse);
	void setAngularVelocity(float aVelocity);
	void setBounciness(float bounciness);
	void setCanRotate(bool canRotate);
	void setCategoryBit(unsigned short categoryNum, bool inCategory);
	void setCategoryByBit(unsigned int bits);
	void setCollideBit(unsigned short collisionNum, bool inCollision);
	void setCollideByBit(unsigned int bits);
	void setCOM(Point COM);
	void setDamping(float damp);
	void setForce(Vector Force);
	void setFriction(float friction);
	void setGroup(int group);
	void setImpulse(Vector Impulse);
	void setIsBullet(bool isBullet);
	void setIsSensor(bool isSensor);
	void setMass(float massInKG);
	void setTorque(float torque);
	void setVelocity(float xVelocity, float yVelocity);
	void setShape(short shapeType);
	void setShapeBox(Point TopLeft, Point BottomRight, float angleInRads = 0.0f);
	void setShapeCircle(Point CenterOfCircle, float radius);
	void setShapePolygon(short numOfPoints, short pointIndex, Point Location);

	void togglePhysics(void);

private:
	bool usingPhysics;
	bool category[16];
	bool collision[16];
	
	void setOff(void);
	void setOn(short mode = 2);

	bool _Mode(short value = 2);	
	bool _Shape(short shapeType);
	bool _ShapePolygon(short numOfPoints, short pointIndex);
	bool _UnsignedFloat(float value);
	bool _ZeroToFifteen(unsigned int value);
	bool _ZeroToMaxInt(unsigned int value, unsigned int maxValue);
	bool _ZeroToOneFloat(float value);
};