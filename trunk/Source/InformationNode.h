#pragma once
#include "Character.h"
//#include "File.h"
#include <vector>

class InformationNode :
	public Character
{
public:
	//Constructor/Destructors
	InformationNode(void);
	~InformationNode(void);
	InformationNode::InformationNode(Point Location, bool submerged = false, unsigned short bonusType = 0, unsigned short bonusAmount = 0);	

	//member methods
	void attack(float currentTime, Character *Target) override;
	
	void damage(short amount, Character *Attacker) override;

	void fireWeapon(void) override;

	unsigned short getCurrentCost(void) override {return 0;};

	void incrementCount(void) override {};
	void incrementTime(float currentTime) override {};

	void kill(Character *Killer) override;
	
	void update(float currentTime, std::vector<Character*> Defenders) override;
};

