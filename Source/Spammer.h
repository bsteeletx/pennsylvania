#pragma once
#include "Character.h"

class Spammer :
	public Character
{
public:
	Spammer(void);
	~Spammer(void);

	Spammer::Spammer(Point Location);

	void attack(Character &Target);
	
	void damage(short amount);

	void update(void);
};

