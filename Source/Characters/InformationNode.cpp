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
	oldY = getY();
	Type = INFORMATION_NODE;
	Character::setVisible(!submerged);
	setCollisionGroup((int) GODS);
	setState(IDLE);
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
	//no Attacks for Informaiton Nodes
}

void InformationNode::damage(short amount)
{
	//nothing special
	//hitPoints -= amount;

	//if (hitPoints <= 0)
	//	kill();
}

void InformationNode::kill(Character *KilledBy)
{
	Character::kill(KilledBy);
}

void InformationNode::update(std::vector<Character*> Defenders)
{
	//nothing as of yet
}