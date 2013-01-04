#pragma once
#include "Character.h"

class BugVirus :
	public Character
{
public:
	BugVirus(void);
	~BugVirus(void);

	BugVirus::BugVirus(Point Location);

	void attack(Character &Target);
	
	void damage(short amount);

	void update(void);

private:

};

