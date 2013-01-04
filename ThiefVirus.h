#pragma once
#include "Character.h"
#include "Text.h"

class ThiefVirus :
	public Character
{
public:
	ThiefVirus(void);
	~ThiefVirus(void);
	ThiefVirus::ThiefVirus(Point Location);

	//member methods
	virtual void attack(Character *Target) override;
	virtual void damage(short amount) override;
	virtual void kill(Character *KilledBy) override;
	virtual void update(std::vector<Character*> Defenders) override;

protected:
};

