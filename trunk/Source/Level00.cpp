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
	isPaused = false;

	for (int i = 0; i < 8; i++)
		shownCreature[i] = false;

	bugDeath = false;
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

	Highlighter = Sprite(Text("Assets/Common/selector.png"), false);
	Highlighter.setOffset(Selector.getWidth()/2, Selector.getHeight()/2);
	addSprite(Highlighter.getSpriteNumber());
	Highlighter.setSize(12.5f);
	Highlighter.setOffset(1.5f, 1.9f);
	Highlighter.setVisible(false);
	Highlighter.setPosition(Point(0.0f, 0.0f).getNormalCoords());
	Highlighter.setY(Highlighter.getY() - 15.0f);
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
	if (isPaused)
	{
		if (!Highlighter.getVisible())
		{
			if ((agk::GetPointerReleased() == 1) && bugDeath)
			{
				Prompt.setVisible(false);
				PromptBackground.setVisible(false);
				togglePause();
			}
			else 
				Level::update();
		}
		else if ((agk::GetPointerReleased() == 1) && !shownCreature[THIEF_VIRUS])
		{
			Point MouseLoc = Point(agk::GetPointerX(), agk::GetPointerY());
			
			if (MouseLoc.getGridCoords() == Point(0.0f, -1.0f))
			{
				Highlighter.setVisible(false);
				Highlighter.setX(-20.0f);
				Prompt.setVisible(false);
				PromptBackground.setVisible(false);
				selectCreature(0);
				togglePause();
			}
		}
		else if ((agk::GetPointerPressed() == 1) && !shownCreature[SPAMMER])
		{
			//TODO: End Level to next level...how?
		}
		return;
	}

	doPrompts();

	if (AlarmSystem.getActivated())
	{
		AlarmSystem.update();
	}

	updateAttackers();
	
	//check on deaths for Thief Virus attack
	if (checkForKilling(INFORMATION_NODE))
	{
		if (!unlockedDefenders)
		{
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
	

	//Update the base level as well
	Level::update();
}

void Level00::doPrompts(unsigned int creatureID)
{
	if (!shownCreature[INFORMATION_NODE])
	{
		for (unsigned int i = 0; i < Defenders.size(); i++)
		{
			if (Defenders[i]->getCreatureType() == INFORMATION_NODE)
			{
				showCreature(Defenders[i]);
				shownCreature[INFORMATION_NODE] = true;
				return;
			}
		}
	}
	else if (!shownCreature[MINER_VIRUS])
	{
		for (unsigned int i = 0; i < Attackers.size(); i++)
		{
			if (Attackers[i]->getCreatureType() == MINER_VIRUS)
			{
				showCreature(Attackers[i]);
				shownCreature[MINER_VIRUS] = true;
				return;
			}
		}
	}
	else if (Highlighter.getX() > 0.0f)
	{
		if (!Highlighter.getVisible())
		{
			getPrompt();
			setPrompt();
			Highlighter.setVisible(true);
			Attackers[0]->setState(MENU_AVAILABLE);
			return;
		}
	}
	else if (creatureID != 0)
	{
		Attackers[creatureID]->setVisible(true);
		showCreature(Attackers[creatureID]);
		shownCreature[Attackers[creatureID]->getCreatureType()] = true;
		return;
	}
	else if (AlarmSystem.getActivated() && !shownCreature[NORT])
	{
		for (unsigned int i = 0; i < Defenders.size(); i++)
		{
			if (Defenders[i]->getCreatureType() == NORT)
			{
				showCreature(Defenders[i]);
				shownCreature[NORT] = true;
				return;
			}
		}
	}
	else if (AlarmSystem.getActivated() && !shownCreature[BUG_VIRUS])
	{
		for (unsigned int i = 0; i < Attackers.size(); i++)
		{
			if (Attackers[i]->getCreatureType() == BUG_VIRUS)
			{
				//Attackers[BUG_VIRUS]->setVisible(true);
				showCreature(Attackers[i]);
				shownCreature[BUG_VIRUS] = true;
				return;
			}
		}
	}
	else if (AlarmSystem.getActivated() && !shownCreature[DBLOCKER])
	{
		for (unsigned int i = 0; i < Attackers.size(); i++)
		{
			if (Attackers[i]->getCreatureType() == DBLOCKER)
			{
				//Attackers[BUG_VIRUS]->setVisible(true);
				showCreature(Attackers[i]);
				shownCreature[DBLOCKER] = true;
				return;
			}
		}
	}
	else if (!bugDeath && checkForKilling(BUG_VIRUS))
	{
		getPrompt();
		setPrompt();
		bugDeath = true;
	}
}

void Level00::updateAttackers(void)
{
	//Attackers first
	for (unsigned int i = 0; i < Attackers.size(); i++)
	{
		if (Attackers[i]->isExample)
		{
			//Specific code for the 'Choose attacker' Menu
			for (unsigned int j = 0; j < currencyForUnlock.size(); j++)
			{
				if (Attackers[i]->getCreatureType() == unlockedAttacker[j])
				{
					//If the creature hasn't been unlocked, do not show him
					//if (currencyGained < currencyForUnlock[j])
					//	Attackers[i]->setVisible(false);
					if (currencyGained > currencyForUnlock[j])
					{
						doPrompts(i);
						unlockedAttacker.erase(unlockedAttacker.begin() + j);
						currencyForUnlock.erase(currencyForUnlock.begin() + j);
					}
				}
			}

			if (!shownCreature[Attackers[i]->getCreatureType()])
				Attackers[i]->setState(MENU_HIDDEN);				
		}

		//handle attacks for the Miner_Virus
		if (Attackers[i]->getCreatureType() == MINER_VIRUS)
		{
			if (Attackers[i]->didAttackThisTurn())
				currencyGained += Attackers[i]->getAttackAmount();
		}
	}
}

bool Level00::checkForKilling(Creature Type)
{
	for (unsigned int i = 0; i < Defenders.size(); i++)
	{
		if (Defenders[i]->getState() == FADEOUT)
		{
			if (Defenders[i]->getCreatureType() == Type)
			{
				if (Defenders[i]->getColorAlpha() < 5)
					return true;
			}
		}
	}

	for (unsigned int j = 0; j < Attackers.size(); j++)
	{
		if (Attackers[j]->getState() == FADEOUT)
		{
			if (Attackers[j]->getCreatureType() == Type)
			{
				if (Attackers[j]->getColorAlpha() < 5)
					return true;
			}
		}
	}

	return false;
}