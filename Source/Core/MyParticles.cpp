#include "MyParticles.h"
#include "agk.h"

Particles::Particles(void)
{
	particleNumber = 0;
}

Particles::~Particles(void)
{
	//if (getExists())
		//agk::DeleteParticles(particleNumber);
}

Particles::Particles(float x, float y)
{
	particleNumber = agk::CreateParticles(x, y);
}

Particles& Particles::operator= (const Particles& newParticle)
{	
	if (this != &newParticle)
	{
		particleNumber = newParticle.particleNumber;
	}

	return *this;
}

Particles::Particles(unsigned int assignedNumber, float x, float y)
{
	if (assignedNumber != 0)
	{
		agk::CreateParticles(assignedNumber, x, y);
		particleNumber = assignedNumber;
	}
}

void Particles::addColorKeyFrame(float time, RGBA Values)
{
	if (time > 0.0f)
		agk::AddParticlesColorKeyFrame(particleNumber, time, Values.getRed(), Values.getGreen(), Values.getBlue(), Values.getAlpha());
}

void Particles::addForce(float startTime, float endTime, float xAcc, float yAcc)
{
	if (startTime < endTime)
	{
		if (startTime >= 0.0f)
			agk::AddParticlesForce(particleNumber, startTime, endTime, xAcc, yAcc);
	}
}

void Particles::clearColors(void)
{
	agk::ClearParticlesColors(particleNumber);
}

void Particles::clearForces(void)
{
	agk::ClearParticlesForces(particleNumber);
}

void Particles::fixToScreen(bool toScreen)
{
	if (toScreen)
		agk::FixParticlesToScreen(particleNumber, 1);
	else
		agk::FixParticlesToScreen(particleNumber, 0);
}

bool Particles::getActive(void)
{
	if (agk::GetParticlesActive(particleNumber) == 1)
		return true;
	
	return false;
}

float Particles::getAngle(void)
{
	return agk::GetParticlesAngle(particleNumber);
}

float Particles::getAngleInRad(void)
{
	return agk::GetParticlesAngleRad(particleNumber);
}

unsigned short Particles::getDepth(void)
{
	return (unsigned short) agk::GetParticlesDepth(particleNumber);
}

float Particles::getDirectionX(void)
{
	return agk::GetParticlesDirectionX(particleNumber);
}

float Particles::getDirectionY(void)
{
	return agk::GetParticlesDirectionY(particleNumber);
}

bool Particles::getExists(void)
{
	if (agk::GetParticlesExists(particleNumber) == 1)
		return true;

	return false;
}

float Particles::getFrequency(void)
{
	return agk::GetParticlesFrequency(particleNumber);
}

float Particles::getLife(void)
{
	return agk::GetParticlesLife(particleNumber);
}

bool Particles::getMaxReached(void)
{
	if (agk::GetParticlesMaxReached(particleNumber) == 1)
		return true;
	
	return false;
}

float Particles::getSize(void)
{
	return agk::GetParticlesSize(particleNumber);
}

bool Particles::getVisible(void)
{
	if (agk::GetParticlesVisible(particleNumber) == 1)
		return true;

	return false;
}

float Particles::getX(void)
{
	return agk::GetParticlesX(particleNumber);
}

float Particles::getY(void)
{
	return agk::GetParticlesY(particleNumber);
}

void Particles::resetCount(void)
{
	agk::ResetParticleCount(particleNumber);
}

void Particles::setActive(bool active)
{
	if (active)
		agk::SetParticlesActive(particleNumber, 1);
	else
		agk::SetParticlesActive(particleNumber, 0);
}

void Particles::setAngle(float angle)
{
	agk::SetParticlesAngle(particleNumber, angle);
}

void Particles::setAngleInRad(float angleInRad)
{
	agk::SetParticlesAngleRad(particleNumber, angleInRad);
}

void Particles::setColorInterpolation(bool smooth)
{
	if (smooth)
		agk::SetParticlesColorInterpolation(particleNumber, 1);
	else
		agk::SetParticlesColorInterpolation(particleNumber, 0);
}

void Particles::setDepth(unsigned short depth)
{
	agk::SetParticlesDepth(particleNumber, depth);
}

void Particles::setDirection(float xVelocity, float yVelocity)
{
	agk::SetParticlesDirection(particleNumber, xVelocity, yVelocity);
}

void Particles::setFrequency(float freq)
{
	if (freq > 0.0f)
		agk::SetParticlesFrequency(particleNumber, freq);
}

void Particles::setImage(Image Object)
{
	agk::SetParticlesImage(particleNumber, Object.getImageNumber());
}

void Particles::setLife(float lifespan)
{
	if (lifespan > 0.0f)
		agk::SetParticlesLife(particleNumber, lifespan);
}

void Particles::setMax(unsigned int maxParticles)
{
	agk::SetParticlesMax(particleNumber, maxParticles);
}

void Particles::setPosition(Point Location)
{
	agk::SetParticlesPosition(particleNumber, Location.getX(), Location.getY());
}

void Particles::setSize(float size)
{
	if(size > 0.0f)
		agk::SetParticlesSize(particleNumber, size);
}

void Particles::setStartZone(Point TopLeft, Point BottomRight)
{
	agk::SetParticlesStartZone(particleNumber, TopLeft.getX(), TopLeft.getY(), BottomRight.getX(), BottomRight.getY());
}

void Particles::setVelocityRange(float minVelocity, float maxVelocity)
{
	agk::SetParticlesVelocityRange(particleNumber, minVelocity, maxVelocity);
}

void Particles::setVisible(bool visible)
{
	if (visible)
		agk::SetParticlesVisible(particleNumber, 1);
	else
		agk::SetParticlesVisible(particleNumber, 0);
}

void Particles::update(float updateSpeed)
{
	if (updateSpeed > 0.0f)
		agk::UpdateParticles(particleNumber, updateSpeed);
}