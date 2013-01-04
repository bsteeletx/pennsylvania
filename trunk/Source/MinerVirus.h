#pragma once
#include "Character.h"

#define FOG_COLUMN_REMOVAL_TIME 6

class MinerVirus :
	public Character
{
public:
	MinerVirus(void);
	~MinerVirus(void);
	MinerVirus::MinerVirus(Point Location);

	//member methods
	virtual void attack(Character *Target) override;
	virtual void damage(short amount) override;
	virtual void kill(Character *KilledBy) override;
	virtual void update(std::vector<Character*> Defenders) override;

private:
};

