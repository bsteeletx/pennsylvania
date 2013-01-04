#pragma once
#include "Character.h"

#define DBLOCKER_HEIGHT 25
#define DBLOCKER_WIDTH 25
#define DBLOCKER_COUNT 24
#define DBLOCKER_PATHFILE "Creatures/DBlocker.png"

class DBlocker :
	public Character
{
public:
	DBlocker(void);
	~DBlocker(void);

	DBlocker::DBlocker(Point Location);

	virtual void attack(Character &Target);
	
	virtual void damage(short amount);
};

