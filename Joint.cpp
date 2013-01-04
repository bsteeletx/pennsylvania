#include "Joint.h"
#include "agk.h"

Joint::Joint(void)
{
	jointID = 0;
}

Joint::~Joint(void)
{
	//if (getExists())
	//	agk::DeleteJoint(jointID);
}

bool Joint::getExists(void)
{
	if (agk::GetJointExists(jointID) == 1)
		return true;

	return false;
}

unsigned int Joint::getJointID(void)
{
	return jointID;
}

float Joint::getReactionForceX(void)
{
	return agk::GetJointReactionForceX(jointID);
}

float Joint::getReactionForceY(void)
{
	return agk::GetJointReactionForceY(jointID);
}

float Joint::getReactionTorque(void)
{
	return agk::GetJointReactionTorque(jointID);
}

void Joint::setLimitOff(void)
{
	agk::SetJointLimitOff(jointID);
}

void Joint::setLimitOn(float lowerBounds, float upperBounds)
{
	agk::SetJointLimitOn(jointID, lowerBounds, upperBounds);
}

void Joint::setMotorOff(void)
{
	agk::SetJointMotorOff(jointID);
}

void Joint::setMotorOn(float speed, float maxForce)
{
	agk::SetJointMotorOn(jointID, speed, maxForce);
}

DistanceJoint::DistanceJoint(void)
{
	jointID = 0;
}

DistanceJoint::~DistanceJoint(void)
{
	if (getExists())
		agk::DeleteJoint(jointID);
}

DistanceJoint::DistanceJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, Point AnchorForSprite1, Point AnchorForSprite2, bool canCollide)
{
	if (canCollide)
		agk::CreateDistanceJoint(assignedIndex, Object1.getSpriteNumber(), Object2.getSpriteNumber(), AnchorForSprite1.getX(), AnchorForSprite1.getY(), AnchorForSprite2.getX(), AnchorForSprite2.getY(), 1);
	else
		agk::CreateDistanceJoint(assignedIndex, Object1.getSpriteNumber(), Object2.getSpriteNumber(), AnchorForSprite1.getX(), AnchorForSprite1.getY(), AnchorForSprite2.getX(), AnchorForSprite2.getY(), 0);

	jointID = assignedIndex;
}

DistanceJoint::DistanceJoint(Sprite Object1, Sprite Object2, Point AnchorForSprite1, Point AnchorForSprite2, bool canCollide)
{
	if (canCollide)
		jointID = agk::CreateDistanceJoint(Object1.getSpriteNumber(), Object2.getSpriteNumber(), AnchorForSprite1.getX(), AnchorForSprite1.getY(), AnchorForSprite2.getX(), AnchorForSprite2.getY(), 1);
	else
		jointID = agk::CreateDistanceJoint(Object1.getSpriteNumber(), Object2.getSpriteNumber(), AnchorForSprite1.getX(), AnchorForSprite1.getY(), AnchorForSprite2.getX(), AnchorForSprite2.getY(), 0);
}

GearJoint::GearJoint(void)
{
	jointID = 0;
}

GearJoint::~GearJoint(void)
{
	if (getExists())
		agk::DeleteJoint(jointID);
}

GearJoint::GearJoint(unsigned int assignedIndex, Joint Object1, Joint Object2, float ratio)
{
	agk::CreateGearJoint(assignedIndex, Object1.getJointID(), Object2.getJointID(), ratio);

	jointID = assignedIndex;
}

GearJoint::GearJoint(Joint Object1, Joint Object2, float ratio)
{
	jointID = agk::CreateGearJoint(Object1.getJointID(), Object2.getJointID(), ratio);
}

LineJoint::LineJoint(void)
{
	jointID = 0;
}

LineJoint::~LineJoint(void)
{
	if (getExists())
		agk::DeleteJoint(jointID);
}

LineJoint::LineJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, Point Anchor, Point Axis, bool canCollide)
{
	if (canCollide)
		agk::CreateLineJoint(assignedIndex, Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), Axis.getX(), Axis.getY(), 1);
	else
		agk::CreateLineJoint(assignedIndex, Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), Axis.getX(), Axis.getY(), 0);

	jointID = assignedIndex;
}

LineJoint::LineJoint(Sprite Object1, Sprite Object2, Point Anchor, Point Axis, bool canCollide)
{
	if (canCollide)
		agk::CreateLineJoint(Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), Axis.getX(), Axis.getY(), 1);
	else
		agk::CreateLineJoint(Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), Axis.getX(), Axis.getY(), 1);
}

MouseJoint::MouseJoint(void)
{
	jointID = 0;
}

MouseJoint::~MouseJoint(void)
{
	if (getExists())
		agk::DeleteJoint(jointID);
}

MouseJoint::MouseJoint(unsigned int assignedIndex, Sprite Object, Point Anchor, float maxForce)
{
	agk::CreateMouseJoint(assignedIndex, Object.getSpriteNumber(), Anchor.getX(), Anchor.getY(), maxForce);
	jointID = assignedIndex;
}

MouseJoint::MouseJoint(Sprite Object, Point Anchor, float maxForce)
{
	jointID = agk::CreateMouseJoint(Object.getSpriteNumber(), Anchor.getX(), Anchor.getY(), maxForce);
}

void MouseJoint::setTarget(Point Location)
{
	agk::SetJointMouseTarget(jointID, Location.getX(), Location.getY());
}

PrismaticJoint::PrismaticJoint(void)
{
	jointID = 0;
}

PrismaticJoint::~PrismaticJoint(void)
{
	if (getExists())
		agk::DeleteJoint(jointID);
}

PrismaticJoint::PrismaticJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, Point Anchor, Point Axis, bool canCollide)
{
	if (canCollide)
		agk::CreatePrismaticJoint(assignedIndex, Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), Axis.getX(), Axis.getY(), 1);
	else
		agk::CreatePrismaticJoint(assignedIndex, Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), Axis.getX(), Axis.getY(), 0);

	jointID = assignedIndex;
}

PrismaticJoint::PrismaticJoint(Sprite Object1, Sprite Object2, Point Anchor, Point Axis, bool canCollide)
{
	if (canCollide)
		jointID = agk::CreatePrismaticJoint(Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), Axis.getX(), Axis.getY(), 1);
	else
		jointID = agk::CreatePrismaticJoint(Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), Axis.getX(), Axis.getY(), 0);
}

PulleyJoint::PulleyJoint(void)
{
	jointID = 0;
}

PulleyJoint::~PulleyJoint(void)
{
	if (getExists())
		agk::DeleteJoint(jointID);
}

PulleyJoint::PulleyJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, Point Ground1, Point Ground2, Point Anchor1, Point Anchor2, float ratio, bool canCollide)
{
	if (canCollide)
		agk::CreatePulleyJoint(assignedIndex, Object1.getSpriteNumber(), Object2.getSpriteNumber(), Ground1.getX(), Ground1.getY(), Ground2.getX(), Ground2.getY(), Anchor1.getX(), Anchor1.getY(), Anchor2.getX(), Anchor2.getY(), ratio, 1);
	else
		agk::CreatePulleyJoint(assignedIndex, Object1.getSpriteNumber(), Object2.getSpriteNumber(), Ground1.getX(), Ground1.getY(), Ground2.getX(), Ground2.getY(), Anchor1.getX(), Anchor1.getY(), Anchor2.getX(), Anchor2.getY(), ratio, 0);

	jointID = assignedIndex;
}

PulleyJoint::PulleyJoint(Sprite Object1, Sprite Object2, Point Ground1, Point Ground2, Point Anchor1, Point Anchor2, float ratio, bool canCollide)
{
	if (canCollide)
		agk::CreatePulleyJoint2(Object1.getSpriteNumber(), Object2.getSpriteNumber(), ratio, 1);
	else
		agk::CreatePulleyJoint2(Object1.getSpriteNumber(), Object2.getSpriteNumber(), ratio, 0);

	jointID = finish (Ground1, Ground2, Anchor1, Anchor2);
}

unsigned int PulleyJoint::finish(Point Ground1, Point Ground2, Point Anchor1, Point Anchor2)
{
	return agk::FinishPulleyJoint(Ground1.getX(), Ground1.getY(), Ground2.getX(), Ground2.getY(), Anchor1.getX(), Anchor1.getY(), Anchor2.getX(), Anchor2.getY());
}

RevoluteJoint::RevoluteJoint(void)
{
	jointID = 0;
}

RevoluteJoint::~RevoluteJoint(void)
{
	if (getExists())
		agk::DeleteJoint(jointID);
}

RevoluteJoint::RevoluteJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, Point Anchor, bool canCollide)
{
	jointID = assignedIndex;
	if (canCollide)
		agk::CreateRevoluteJoint(assignedIndex, Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), 1);
	else
		agk::CreateRevoluteJoint(assignedIndex, Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), 0);
}

RevoluteJoint::RevoluteJoint(Sprite Object1, Sprite Object2, Point Anchor, bool canCollide)
{
	if (canCollide)
		agk::CreateRevoluteJoint(Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), 1);
	else
		agk::CreateRevoluteJoint(Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), 0);
}

WeldJoint::WeldJoint(void)
{
	jointID = 0;
}

WeldJoint::~WeldJoint(void)
{
	if (getExists())
		agk::DeleteJoint(jointID);
}

WeldJoint::WeldJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, Point Anchor, bool canCollide)
{
	jointID = assignedIndex;

	if (canCollide)
		agk::CreateWeldJoint(assignedIndex, Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), 1);
	else
		agk::CreateWeldJoint(assignedIndex, Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), 0);
}

WeldJoint::WeldJoint(Sprite Object1, Sprite Object2, Point Anchor, bool canCollide)
{
	if (canCollide)
		jointID = agk::CreateWeldJoint(Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), 1);
	else
		jointID = agk::CreateWeldJoint(Object1.getSpriteNumber(), Object2.getSpriteNumber(), Anchor.getX(), Anchor.getY(), 0);
}