////////////////////////////////
// Inofrmation Node Implementation/AI
////////////////////////////////
#include "InformationNode.h"

////////////////////////////////////////////
// Default Constructor
// Input: None
// Result: Information Node Object Created
////////////////////////////////////////////
InformationNode::InformationNode(void)
	: Character(Text("Assets/Creatures/InformationNode"))
{



}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Information Node Constructor
// Input: A Grid Location, whether the information node is submerged to start or not (bool), type of bonus when killed, and the bonus given
// Result: Information Node Object Created
// Note: Probably shouldn't do any intialization here, have an init function
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InformationNode::InformationNode(Point GridLocation, bool submerged, unsigned short bonusType, unsigned short bonusAmount)	
	: Character(Text("CreatureData/InformationNode"))
{
	setPosition(GridLocation.getNormalCoords());
	//setZ(5.0f);
	oldY = getY();
	Type = INFORMATION_NODE;
	Character::setVisible(!submerged);
	setCollisionGroup((int) GODS);
	setState(IDLE);

	setSize(10.0f);
}

//////////////////////////////////////////
// Destructor
// Input: None
// Result: Information Node is destroyed
/////////////////////////////////////////
InformationNode::~InformationNode(void)
{
}

///////////////////////////////////////////////////
// Overridden functions, nothing special for Information Node
//////////////////////////////////////////////////////
void InformationNode::attack(Character *Target)
{
	//no attacks from informaiton node
}

void InformationNode::damage(short amount, Character *Attacker)
{
	//nothing special
	//hitPoints -= amount;

	//if (hitPoints <= 0)
	//	kill();
	Character::damage(amount, Attacker);
}

void InformationNode::fireWeapon(void)
{
}


void InformationNode::kill(Character *KilledBy)
{
	Character::kill(KilledBy);
}

void InformationNode::update(std::vector<Character*> Defenders)
{
	//nothing as of yet
	/*if (getState() == FADEOUT)
	{
		short alpha = getColorAlpha() - 5;
				
		if (alpha >= 0)
			setColorAlpha(alpha);
		else
			setX(-15.0f);
	}*/
	Character::update(Defenders);
}