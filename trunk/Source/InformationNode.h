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
	void attack(Character *Target) override;
	
	void damage(short amount, Character *Attacker) override;

	void fireWeapon(void) override;

	void incrementCount(void) override {};

	void kill(Character *Killer) override;
	
	void update(std::vector<Character*> Defenders) override;
};

