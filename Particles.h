#pragma once
#include "Point.h"
#include "Image.h"
#include "RGBA.h"
class Particles
{
public:
	Particles();
	~Particles();
	Particles(float x, float y);
	Particles(unsigned int assignedNumber, float x, float y);

	Particles& operator= (const Particles& newParticles);

	void addColorKeyFrame(float time, RGBA Values);
	void addForce(float startTime, float endTime, float xAcc, float yAcc);
	
	void clearColors(void);
	void clearForces(void);

	void fixToScreen(bool toScreen);

	bool getActive(void);
	float getAngle(void);
	float getAngleInRad(void);
	unsigned short getDepth(void);
	float getDirectionX(void);
	float getDirectionY(void);
	bool getExists(void);
	float getFrequency(void);
	float getLife(void);
	bool getMaxReached(void);
	float getSize(void);
	bool getVisible(void);
	float getX(void);
	float getY(void);

	void resetCount(void);

	void setActive(bool active);
	void setAngle(float angle);
	void setAngleInRad(float angleInRad);
	void setColorInterpolation(bool smooth);
	void setDepth(unsigned short depth);
	void setDirection(float xVelocity, float yVelocity);
	void setFrequency(float freq);
	void setImage(Image Object);
	void setLife(float lifespan);
	void setMax(unsigned int maxParticles);
	void setPosition(Point Location);
	void setSize(float size);
	void setStartZone(Point TopLeft, Point BottomRight);
	void setVelocityRange(float minVelocity, float maxVelocity);
	void setVisible(bool visible);

	void update(float updateSpeed);

private:
	unsigned int particleNumber;
};