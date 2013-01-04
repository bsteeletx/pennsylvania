#pragma once

#include "Sprite.h"
//#include "Point.h"

class Joint
{
public:
	Joint();
	~Joint(void);

	bool getExists(void);
	unsigned int getJointID(void);
	float getReactionForceX(void);
	float getReactionForceY(void);
	float getReactionTorque(void);

	void setLimitOff(void);
	void setLimitOn(float lowerBounds, float upperBounds);
	void setMotorOff(void);
	void setMotorOn(float speed, float maxForce);

protected:
	unsigned int jointID;
};

class DistanceJoint : public Joint
{
public:
	DistanceJoint();
	~DistanceJoint();
	DistanceJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, Point AnchorForSprite1, Point AnchorForSprite2, bool canCollide);
	DistanceJoint(Sprite Object1, Sprite Object2, Point AnchorForSprite1, Point AnchorForSprite2, bool canCollide);
};

class GearJoint : public Joint
{
public:
	GearJoint();
	~GearJoint(void);
	GearJoint(unsigned int assignedIndex, Joint Object1, Joint Object2, float ratio);
	GearJoint(Joint Object1, Joint Object2, float ratio);
};

class LineJoint : public Joint
{
public:
	LineJoint();
	~LineJoint();
	LineJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, Point Anchor, Point Axis, bool canCollide);
	LineJoint(Sprite Object1, Sprite Object2, Point Anchor, Point Axis, bool canCollide);
};

class MouseJoint : public Joint
{
public:
	MouseJoint();
	~MouseJoint();
	MouseJoint(unsigned int assignedIndex, Sprite Object, Point Anchor, float maxForce);
	MouseJoint(Sprite Object, Point Anchor, float maxForce);

	void setTarget(Point Location);
};

class PrismaticJoint : public Joint
{
public:
	PrismaticJoint();
	~PrismaticJoint();
	PrismaticJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, Point Anchor, Point Axis, bool canCollide);
	PrismaticJoint(Sprite Object1, Sprite Object2, Point Anchor, Point Axis, bool canCollide);
};

class PulleyJoint : public Joint
{
public:
	PulleyJoint();
	~PulleyJoint();
	PulleyJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, Point Ground1, Point Ground2, Point Anchor1, Point Anchor2, float ratio, bool canCollide);
	PulleyJoint(Sprite Object1, Sprite Object2, Point Ground1, Point Ground2, Point Anchor1, Point Anchor2, float ratio, bool canCollide);

private:
	unsigned int finish(Point Ground1, Point Ground2, Point Anchor1, Point Anchor2);
};

class RevoluteJoint : public Joint
{
	RevoluteJoint();
	~RevoluteJoint();
	RevoluteJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, Point Anchor, bool canCollide);
	RevoluteJoint(Sprite Object1, Sprite Object2, Point Anchor, bool canCollide);
};

class WeldJoint : public Joint
{
	WeldJoint();
	~WeldJoint();
	WeldJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, Point Anchor, bool canCollide);
	WeldJoint(Sprite Object1, Sprite Object2, Point Anchor, bool canCollide);
};