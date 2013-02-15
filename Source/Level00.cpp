///////////////////////
// Level 0 Source File
//////////////////////

#include "Level00.h"
#include "agk.h"

//////////////////////////
// Default Constructor
// Input: None
// Result: Tutorial Level Object created
//////////////////////////
Level00::Level00(void)
{
	unlockNum = 0;
	unlockedDefenders = false;
	currencyGained = 0;
}

////////////////////////////////////////////////////////
// Constructor
// Input: Attacker List
// Result: Tutorial Level Object Created
//         Level Object Created
// Note (1/3/13): Might want to not initialize anything in the object constructor
///////////////////////////////////////////////////////
Level00::Level00(std::vector<Creature> attackerList)
	: Level(0, attackerList)
{
	unlockNum = 0;
	unlockedDefenders = false;
	currencyGained = 0;
}

/////////////////////////////
// Destructor
// Input: None
// Result: Tutorial Level Destroyed
//////////////////////////
Level00::~Level00(void)
{
}

//////////////////////////
// Initializer
// Input: None
// Result: Tutorial Level initialized
//////////////////////////
void Level00::init(void)
{
	//Local Variables
	//Creature Type;
	Point Location;
	File LevelSource(true, "LevelData/Level 00.txt");

	//Initialize base object
	Level::init();

	//Find everything we need in the Level Source file
	while (!LevelSource.FileEOF())
	{
		//Input will be separated into a Category and a Value
		Text Input(LevelSource.getLine());
		Text Category;
		Text Value;
		short value;

		//Input gets split here
		Input.splitAtDelimeter(&Category, &Value, ':');
	
		//Tutorial has hidden defenders
		if (Category == Text("Hidden Defenders"))
		{
			Text SelectedDefender;
			Text RestOfDefenders;

			//Might be more than one hidden diffender, separated by commas
			while (Value.splitAtDelimeter(&SelectedDefender, &RestOfDefenders, ','))
			{
				//Make Selected defender invisible
				Defenders[agk::Val(SelectedDefender.getCString())]->Character::setVisible(false);
				//push the current defender onto the hidden defender stack
				hiddenDefenderStack.push_back(agk::Val(SelectedDefender.getCString()));
				//Change the Rest of the Defenders for a re-split
				Value = RestOfDefenders;
				//This prevents text overruns
				RestOfDefenders = Text("");
			}
		}
		//This whole else if is probably old code and does not need to be in, but I would wait until Tutorial is running to remove it
		else if (Category == Text("Unhide Defenders"))
		{
			Text TypeOfUnlock;
			Text DataForUnlock;
			
			Value.splitAtDelimeter(&TypeOfUnlock, &DataForUnlock, ':');

			if (TypeOfUnlock == Text("Death"))
			{
			}
		}
		//This section sets up how creatures get unlocked for the player
		else
		{
			//need to know what the value portion of the text file is
			value = agk::Val(Value.getCString());

			//Check the category and apply the value to the correct variable
			if (Category == Text("Data Required for Unlock"))
				currencyForUnlock.push_back(value);
			else if (Category == Text("Unlocked Attacker"))
				unlockedAttacker.push_back((Creature) value);
		}
	}

	AlarmSystem = Alarm(8); //length of alarm in seconds
	Song = Music(Text("Assets/Sounds/Level 00.wav"));
}

/////////////////////////////////
// Delete Level
// Input: None
// Result: Clear all vectors (might need more than this) and delete the base object
/////////////////////////////////
void Level00::deleteLevel(void)
{
	currencyForUnlock.clear();
	unlockedAttacker.clear();

	hiddenDefenderStack.clear();

	Level::deleteLevel();
}

////////////////////////////////////////////
// get Fog (virtual override)
// Input: GridLocation Point to check if there is fog there
// Output: Bool true for yet, false for no
// Note: No fog in Tutorial Level
////////////////////////////////////////////
bool Level00::getFog(Point GridLocation)
{
	return false;
}

///////////////////////////////////
// Update Level
// Input: None
// Result: Update things specific to the Tutorial Level
/////////////////////////////
void Level00::update(void)
{
	if (AlarmSystem.getActivated())
	{
		AlarmSystem.update();
	}
	//Attackers first
	for (unsigned int i = 0; i < Attackers.size(); i++)
	{
		if (Attackers[i]->isExample)
		{
			//Specific code for the 'Choose attacker' Menu
			for (unsigned int j = 0; j < unlockedAttacker.size(); j++)
			{
				if (Attackers[i]->getCreatureType() == unlockedAttacker[j])
				{
					//If the creature hasn't been unlocked, blacken him and alpha him
					if (currencyGained < currencyForUnlock[j])
						Attackers[i]->setColor(RGBA(0, 0, 0, 32));
				}
			}
		}

		//handle attacks for the Miner_Virus
		if (Attackers[i]->getCreatureType() == MINER_VIRUS)
		{
			if (Attackers[i]->didAttackThisTurn())
				currencyGained += Attackers[i]->getAttackAmount();
		}
	}

	//check on deaths for Thief Virus attack
	for (unsigned int i = 0; i < Defenders.size(); i++)
	{
		if (Defenders[i]->getState() == FADEOUT)
		{
			if (Defenders[i]->getCreatureType() == INFORMATION_NODE)
			{
				if (Defenders[i]->getKilledBy()->getCreatureType() == THIEF_VIRUS)
				{
					if (!unlockedDefenders)
					{
						//This text should work if an Alarm system is set up
						//sound alarm!
						AlarmSystem.activate();

						while (hiddenDefenderStack.size() != 0)
						{
							//Unhide all of the defenders, play their animations, and delete them from the vector
							Defenders[hiddenDefenderStack.back()]->Character::setVisible(true);
							Defenders[hiddenDefenderStack.back()]->setState(IDLE);
							hiddenDefenderStack.pop_back();
						}

						unlockedDefenders = true;
					}
				}
			}
		}
	}

	//Update the base level as well
	Level::update();
}