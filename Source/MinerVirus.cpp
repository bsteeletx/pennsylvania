//////////////////////////
// Miner Virus Implementation/AI
////////////////////////////

#include "MinerVirus.h"
#include "agk.h"

unsigned short MinerVirus::count;

//////////////////////////////
// Default Constructor
// Inputs: None
// Result: MinerVirus Object Created
//////////////////////////////
MinerVirus::MinerVirus(void)
{

}

///////////////////////////////////////////////
// Constructor
// Inputs: Grid Location for where Miner Virus should be placed
// Result: MinerVirus created and placed in the proper location
// Note: We probably shouldn't do any initialization here, create a separete init function
///////////////////////////////////////////////
MinerVirus::MinerVirus(Point GridLocation)
	: Character(Text("CreatureData/MinerVirus"))
{
	setPosition(GridLocation.getNormalCoords());
	Type = MINER_VIRUS;

	if (count == 0)
		isExample = true;
}

/////////////////////////////////
// Destructor
// Inputs: None
// Result: MinerVirus is destoyed
////////////////////////////////
MinerVirus::~MinerVirus(void)
{
}

///////////////////////////////////////////////////////////////
// Update (override of base function)
// Input: List of Defenders
// Result: Do MinerAttack in base
// Notes: Should the base Miner Attack be in the base?
////////////////////////////////////////////////////////////
void MinerVirus::update(std::vector<Character*> Defenders)
{
	if (!isExample)
		Character::update(Defenders);
	else
		updateCost(count);
}

///////////////////////////////////////////////////
// Attack (override of base function)
// Input: Pointer to Character who is the target
// Result: Nothing, Miner Virii don't attack
void MinerVirus::attack(Character *Target)
{
	if (timeFromLastAttack == 0)
	{
		timeFromLastAttack = agk::Timer();
		didDamage = false;
	}
	else if (agk::Timer() - timeFromLastAttack > attackSpeed)
	{
		timeFromLastAttack = agk::Timer();
		didDamage = true;
	}
	else
		didDamage = false;
}

//Currently commented out because we aren't doing fog,
//This might be useful here or in the Fog Class, not sure
/*Point MinerVirus::getFogRemoval(Fog FogBank)
{
	if (FogBank.isFogGone())
		return Point(-1, -1);
	
	if (FogRemovalTimer.getRinging())
	{
		unsigned short column = FogBank.getLastVisibleColumn();
		std::vector<unsigned short> availableLocations;
	
		if (column == 9)
			return Point(-1, -1);

		FogRemovalTimer.resetStopWatch();

		for (int i = 0; i < 5; i++)
		{
			if (FogBank.getVisible(Point(column, i)))
				availableLocations.push_back(i);
		}

		unsigned short min = availableLocations.front();
		unsigned short max = availableLocations.back();
		unsigned short remove = agk::Random(min, max);			

		return Point(column, remove);
	}

	return Point(-1, -1);
}*/

//////////////////////////////////////////
// Damage (override base function)
// Input: Damage amount
// Result: Nothing, Miner Virii are immortal
void MinerVirus::damage(short amount, Character *Attacker)
{
	Character::damage(amount, Attacker);
}

void MinerVirus::fireWeapon(void)
{
}

void MinerVirus::incrementCount(void)
{
	count++;
}

////////////////////////////////////////////
// Kill (override base function)
// Input: Pointer to Character who killed Miner Virus
// Result: Nothing, Miner Virii are immortal
void MinerVirus::kill(Character *Killer)
{
	Character::kill(Killer);
}