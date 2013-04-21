//////////////////////////
// Miner Virus Implementation/AI
////////////////////////////

#include "MinerVirus.h"
#include "agk.h"

unsigned short MinerVirus::count;
float MinerVirus::time;

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
	{
		isExample = true;
		ID = 0;
		count++;
	}
	
	lastDrainTime = 0.0f;
	blinkTime = 0.0f;
	difference = 0.0f;

	OffsetAmounts[MENU_BAR] = Point(-0.01f, -0.01f);
	OffsetAmounts[IN_GAME] = Point(getWidth()/4.0f - 0.5f, getHeight()/4.0f + 2.5f);
	OffsetAmounts[INTRO] = Point(10.0f, 7.5f);	
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
void MinerVirus::update(float currentTime, std::vector<Character*> Defenders)
{
	if (ID)
	{
		Character::update(currentTime, Defenders);
		
		if (getState() != SELECTED)
		{
			if (hitPoints != 0)
				drainHealth();
		}
	}
	else
	{
		updateCost(count);
		time = currentTime;
	}
}

///////////////////////////////////////////////////
// Attack (override of base function)
// Input: Pointer to Character who is the target
// Result: Nothing, Miner Virii don't attack
void MinerVirus::attack(float currentTime, Character *Target)
{
	if (timeFromLastAttack == 0.0f)
	{
		timeFromLastAttack = time;
		didDamage = false;
	}
	else if (time - timeFromLastAttack > attackSpeed)
	{
		timeFromLastAttack = time;
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

void MinerVirus::drainHealth(void)
{
	float healthPercent = (float)hitPoints/(float)maxHitPoints;
	
	if (getState() == SELECTED)
		return;

	if (difference != 0.0f)
	{
		lastDrainTime += difference;
		difference = 0.0f;
	}

	if (lastDrainTime == 0.0f)
		lastDrainTime = time;
	else if (time - lastDrainTime > healthDrainRate)
	{
		damage(healthDrainAmount, this);
		lastDrainTime = time;
	}

	if (healthPercent <= 0.25f)
	{
		if (time - blinkTime > 0.25f)
		{
			toggleAlpha();
			blinkTime = time;
		}
	}
	else if (healthPercent <= 0.5f)
	{
		if (blinkTime == 0.0f)
		{
			toggleAlpha();
			blinkTime = time;
		}
		else if (time - blinkTime > 0.5f)
		{
			toggleAlpha();
			blinkTime = time;
		}
	}
}

void MinerVirus::fireWeapon(void)
{
}

void MinerVirus::incrementCount(void)
{
	count++;
	ID = count;
}

//////////////////
// Increment Time
// Input None
// Output/Result Time is added to the self-damaging value. Used when game is paused
//				Or when virus is selected

void MinerVirus::incrementTime(float currentTime)
{
	difference = currentTime - time;
}

////////////////////////////////////////////
// Kill (override base function)
// Input: Pointer to Character who killed Miner Virus
// Result: Nothing, Miner Virii are immortal
void MinerVirus::kill(Character *Killer)
{
	Character::kill(Killer);
	count--;
}

void MinerVirus::toggleAlpha(void)
{
	if (getColorAlpha() > 200)
		setColorAlpha(128);
	else
		setColorAlpha(255);
}