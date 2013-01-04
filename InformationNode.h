#pragma once
#include "Character.h"
//#include "File.h"

class InformationNode :
	public Character
{
public:
	//Constructor/Destructors
	InformationNode(void);
	~InformationNode(void);
	InformationNode::InformationNode(Point Location, bool submerged = false, unsigned short bonusType = 0, unsigned short bonusAmount = 0);	

	//member methods
	virtual void attack(Character *Target) override;
	virtual void damage(short amount) override;
	virtual void kill(Character *KilledBy) override;
	virtual void update(std::vector<Character*> Defenders) override;
};

