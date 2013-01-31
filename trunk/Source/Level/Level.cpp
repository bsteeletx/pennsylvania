/////////////////////////
// Level.cpp is our base level class
// It might be better served to change this class to a virtual class
// It contains methods for things that appear in ALL levels
/////////////////////////

#include "Level.h"
#include "agk.h"
#include "File.h"

////////////////////////////
// Default Level Constructor
// Input: None
// Output: None
//
////////////////////////////
Level::Level(void)
{
	offsetSelector = false;
	currencyAmount = 0;
	reward = 0;
}

//////////////////////////
// Level Destructor
// Input: None
// Output: None
//
///////////////////////////
Level::~Level(void)
{
}

//////////////////////////////////////////////////////////////////////////////////
// Level Constructor
// Input: level number for ID purposes, AttackerList for pre-loading purposes (I think)
// Output: None
//
// NOTE (1/1/2013): See template.cpp Note for the while loop inside the loadLevel function
//////////////////////////////////////////////////////////////////////////////////
Level::Level(short levelNumber, std::vector<Creature> AttackerList)
{
	offsetSelector = false;
	currencyAmount = 0;
	reward = 0;
	levelID = levelNumber;

	for (unsigned int i = 0; i < AttackerList.size(); i++)
		AttackerInitList.push_back(AttackerList[i]);
}

//////////////////////////////////////////////////////
// Overload Operator =
// /////////////////////////////////////////////////
Level& Level::operator= (const Level &NewLevel)
{
	this->offsetSelector = NewLevel.offsetSelector;
	this->currencyAmount = NewLevel.currencyAmount;
	this->reward = NewLevel.reward;
	this->levelID = NewLevel.levelID;
	this->Attackers = NewLevel.Attackers;
	this->Defenders = NewLevel.Defenders;
	this->imageStack = NewLevel.imageStack;
	this->spriteStack = NewLevel.spriteStack;

	return *this;
}

/////////////////////////
// Init Level
// Input: None
// Output: None
//
// Initializes level by loading in the Level's script file
////////////////////////////
void Level::init(void)
{
	//Local Vars
	Creature Type;
	Point Location;
	
	//Take Default beginning...
	Text LevelName("LevelData/Level ");

	Text NumberText(agk::Str((float) levelID, 0));
	
	if (levelID < 10)
		LevelName += "0";

	//...Add Number to end to have the script file
	LevelName += NumberText;
	LevelName += Text(".txt");

	//Open Script File for reading
	File LevelSource(true, LevelName);
	//End Local Vars

	//Keep reading until at end of file
	while (!LevelSource.FileEOF())
	{
		//Each line of the script file is separated into two items, categories and values
		Text Input(LevelSource.getLine());
		Text Category;
		Text Value;
		short value;

		//Splitting the line at the colon
		Input.splitAtDelimeter(&Category, &Value, ':');
		
		//Check for what category we're looking for and assigne the value to the appropriate variable
		if (Category == Text("Background Image"))
			addBackground(Value);			
		else if (Category == Text("Creature Location"))
		{
			Location.setX((float) Value.getChar(0) - 48); //subtracting 48 to get to number values as 0 = 48 in ASCII
			Location.setY((float) Value.getChar(2) - 48);
			addCreatureType(Type, Location);
		}
		else
		{
			value = agk::Val(Value.getString());

			//To save memory, need to load Creature Types--hold off on Attacker Types
			//until we have an Attacker Selector Menu, then load those Attackers
			//Load initial defenders offscreen, then clone and place them in the 
			//correct location
			//NOTE (1/1/13): We may just load all creatures ahead of time, making part of this unnecessary
			if (Category == Text("Creature Type"))
				Type = (Creature) value;
			else if (Category == Text("Starting Data"))
				currencyAmount = value;
			else if (Category == Text("Reward"))
				reward = value;
			else if (Category == Text("Fog"))
			{
				if (value = 1)
					fogEnabled = true;
				else
					fogEnabled = false;
			}
		}
	}

	LevelSource.close();

	//set up attacker choice menu
	for (unsigned int i = 0; i < AttackerInitList.size(); i++)
	{
		//Assign Grid Location to Location Value
		Point Location(i, 0);
		//Create another Location for Normal Coords
		Point NormalCoords = Location.getNormalCoords();

		//Add creature normally
		addCreatureType(AttackerInitList[i], Location);
		//subtrack 15 from the y to place the creature in the selection area as opposed to the game board
		NormalCoords.setY(NormalCoords.getY() - 15.0f);
		Attackers.back()->setY(NormalCoords.getY());
		Attackers.back()->isExample = true;
		//Alpha out the creature a bit and set in the pose state
		Attackers.back()->setAlpha(128);
		Attackers.back()->setState(POSE); 
	}

	//Load in the Selector
	//NOTE (1/1/13): Needs to have a #if PC as you won't see the selector for other platforms
	/////////////////Need to do a #if on the header file as well
	Selector = Sprite("Assets/Common/selector.png");
	Selector.setDepth(1);
	Selector.setSize(10.75f);
	//Selector.setOffset(Selector.getWidth()/2, Selector.getHeight()/2);
	addSprite(Selector.getSpriteNumber());

	//Place the text for player's currency, set the color and position
	CurrencyTitle = Text("Bytes: ");
	CurrencyValue = Text(agk::Chr(currencyAmount));

	CurrencyTitle.setColor(RGBA(0, 0, 0));
	CurrencyValue.setColor(RGBA(0, 0, 0));

	CurrencyTitle.setPosition(Point(2.0f, 95.0f));
	CurrencyValue.setPosition(Point(15.0f, 95.0f));

	//Null out the Selected Creature
	Selected = (Creature) NULL;
}

////////////////////////////////
// Delete Level
// Input: None
// Output: None
//
// Memory Management, clear out all vectors
////////////////////////////////
void Level::deleteLevel(void)
{
	imageStack.clear();
	spriteStack.clear();

	Attackers.clear();
	Defenders.clear();
}

//////////////////////////////////////////////
// Add Sprite
// Input: Sprite Number
// Output: None
//
// Add Sprites and images to memory management vectors
////////////////////////////////////////////
void Level::addSprite(unsigned int sprite)
{
	spriteStack.push_back(sprite);
	imageStack.push_back(agk::GetSpriteImageID(sprite));
}

//////////////////////////////////////////////
// Add Background
// Input: Filepath and name of background image
// Output: None
//////////////////////////////////////////////
void Level::addBackground(Text PathFilename)
{
	Background = Sprite(PathFilename, false);
	addSprite(Background.getSpriteNumber());
	Background.setSize(100.0f);
	Background.setDepth(10000);
	Background.setVisible(true);
}

//////////////////////////////////////////////////////////////////////
// Add Creature of Type
// Input: Creature number, Location
// Output: None
//
// Adds creature to the appropriate attacker or defender vector and add adds the creatures sprite to the sprite vector
////////////////////////////////////////////////////////////////////////
void Level::addCreatureType(Creature creatureNumber, Point Location)
{
	bool defender = false;
	
	switch (creatureNumber)
	{
	case INFORMATION_NODE:
		defender = true;
		Defenders.push_back(new InformationNode(Location));
		break;
	case MINER_VIRUS:
		Attackers.push_back(new MinerVirus(Location));
		break;
	case THIEF_VIRUS:
		Attackers.push_back(new ThiefVirus(Location));
		break;
	case DBLOCKER:
		Attackers.push_back(new DBlocker(Location));
		break;
	case BUG_VIRUS:
		Attackers.push_back(new BugVirus(Location));
		break;
	case SPAMMER:
		Attackers.push_back(new Spammer(Location));
		break;
	case NORT:
		defender = true;
		Defenders.push_back(new Nort(Location));
		break;
	}

	if (defender)
	{
		addSprite(Defenders.back()->getSpriteNumber());
		Defenders.back()->setState(IDLE);
		//Give the game a sense of depth: The further to the bottom, depth should be less than top
		//Location is in grid coordinates 
		Defenders.back()->setDepth(Defenders.back()->getDepth() - Location.getY());
	}
	else
	{
		addSprite(Attackers.back()->getSpriteNumber());
		
		if (!Attackers.back()->isExample)
			Attackers.back()->setState(IDLE);
		else
			Attackers.back()->setState(POSE);
		//Give the game a sense of depth: The further to the bottom, depth should be less than top
		//Location is in grid coordinates 
		Attackers.back()->setDepth(Attackers.back()->getDepth() - Location.getY());
	}

}

//////////////////////////////
// Handle UI
// Input: None
// Output: None
//
// Everything UI related should be here (including HUD)
///////////////////////////////
void Level::handleUI(void)
{
	//Get actual pointer location
	Point MouseLoc(agk::GetPointerX(), agk::GetPointerY());
	agk::PrintC("Mouse Location: ");
	agk::PrintC(MouseLoc.getX());
	agk::PrintC(", ");
	agk::Print(MouseLoc.getY());
	//set MouseLoc as gridCoords
	MouseLoc.setCoordsAsGridCoords();
	agk::PrintC("Grid Location: ");
	agk::PrintC(MouseLoc.getX());
	agk::PrintC(", ");
	agk::Print(MouseLoc.getY());

	//set the Green Selector to the Mouse's Grid Position
	Selector.setPosition(MouseLoc.getNormalCoords());

	//Selector needs a slight offset, if it hasn't been done, do it
	if (!offsetSelector)
	{
		Selector.setOffset(0.4f, 0.4f);
		offsetSelector = true;
	}

	//Get Coords back to normal Coords
	MouseLoc.setCoords(Selector.getX(), Selector.getY());

	//Apply the offset to the normal Coords
	Selector.setPositionByOffset(MouseLoc);

	//Need to have something turn the selector different colors for whether you can place something or not


	//Adding a creature
	if (agk::GetPointerReleased())
	{
		MouseLoc.setCoordsAsGridCoords();
		int gridX = (int) MouseLoc.getX();
		int gridY = (int) MouseLoc.getY();
		bool validLocation = false;

		//Check for Fog
		//Limiting locations currently to the far right 3 columns, this isn't a game design mention, just following I, Zombie
		if (gridX >= 5)
		{
			if (!fogEnabled)
				validLocation = true;
			else if (!getFog(MouseLoc))
				validLocation = true;
		}
		else if (gridY < 0)
		{
			if (gridX >= 0)
			{
				//Check to see if player is selecting a creature to spawn
				if (gridX <= AttackerInitList.size() - 1)
					validLocation = true;
			}
		}
		
		if (validLocation)
		{
			if (gridY < 0)
			{
				//make sure the character is available, could check any color, not just blue
				if (Attackers[gridX]->getBlue() > 100)
				{
					//make sure the player has the currency to purchase it
					if (Attackers[gridX]->getCost() <= currencyAmount)
					{
						Selected = Attackers[gridX]->getCreatureType();
						addCreatureType(Selected, MouseLoc);
						Attackers.back()->isExample = true;
						//Set alpha to show that the creature isn't on the board yet, also set its group to GHOSTS to keep defenders from hitting it
						Attackers.back()->setAlpha(128);
						Attackers.back()->setCollisionGroup((int) GHOSTS);
					}
				}
			}
			//if a creature is already selected
			else if (Selected != NULL)
			{
				//subtract the cost of the attacker
				currencyAmount -= Attackers.back()->getCost();
				//reset selected to Null
				Selected = (Creature) NULL;
				//remove isExample flag
				Attackers.back()->isExample = false;
				//Remove all Alpha and set creature as idle
				Attackers.back()->setAlpha(255);
				Attackers.back()->setState(IDLE);
				
				//As long as the attacker is not a MINER_VIRUS, set its group to MORTALS
				if (Attackers.back()->getCreatureType() != MINER_VIRUS)
					Attackers.back()->setCollisionGroup((int)(MORTALS));
			}
		}
		
	}

	//If the player has an attacker selected, set the attackers position to the Mouse Location
	if (Selected != (Creature) NULL)
		Attackers.back()->setPosition(MouseLoc);
	
	//Colorize characters player cannot afford
	for (int i = 0; i < Attackers.size(); i++)
	{
		if (Attackers[i]->isExample)
		{
			//Don't need to check if the attacker is the last attacker if the player doesn't have anything selected
			//Otherwise, need to make sure that we're not checking the creature the player is holding
			if ((Selected == (Creature) NULL) || (Attackers[i] != Attackers.back()))
			{
				if (Attackers[i]->getCost() < currencyAmount)
				{
					if (Attackers[i]->getBlue() != 0)
						Attackers[i]->setColor(RGBA(255, 255, 255, 192));
				}
				else
					Attackers[i]->setColor(RGBA(255, 255, 255, 64));
			}
		}
	}

	//Display Currency
	CurrencyValue.setString(agk::Str(currencyAmount));

	if (!CurrencyTitle.getVisible())
	{
		CurrencyTitle.setVisible(true);
		CurrencyValue.setVisible(true);
	}
}

////////////////////////////
// Update Level
// Input: None
// Output: None;
///////////////////////////////
void Level::update(void)
{
	handleUI();
	updateCharacters();
}

///////////////////////////////////
// Update Characters
// Input: None
// Output: None
//
// Giving each character a frame to update logic, movement, etc.
/////////////////////////////////////
void Level::updateCharacters(void)
{
	//Start with attackers
	for (int i = 0; i < Attackers.size(); i++)
	{
		//Ensure Example Attackers stay in pose
		if (Attackers[i]->isExample)
		{
			Attackers[i]->setState(POSE);
			continue;
		}

		//Non Examples need to update based on what defenders are doing
		Attackers[i]->update(Defenders);

		//Miner Virus doesn't really attack, just gets a default amount of currency every now and then
		if (Attackers[i]->getCreatureType() == MINER_VIRUS)
		{
			if (Attackers[i]->didAttackThisTurn())
				currencyAmount += Attackers[i]->getAttackAmount();
		}
	}

	//Update Defenders
	for (int i = 0; i < Defenders.size(); i++)
		Defenders[i]->update(Attackers);

	//Removing Creature if offscreen
	for (int i = 0; i < Attackers.size(); i++)
	{
		//check to see if offscreen--remember that sprite is measured at top left, so it has to be a bit off screen
		if (Attackers[i]->getX() < -10.0f)
			Attackers.erase(Attackers.begin() + i--);
	}

	//Removing Defender if offscreen (placed offscreen when dead, or potentially, walk
	//off screen to right)
	for (int i = 0; i < Defenders.size(); i++)
	{
		if (Defenders[i]->getX() < -10.0f)
			Defenders.erase(Defenders.begin() + i--);
		else if (Defenders[i]->getX() > 110.0f)
			Defenders.erase(Defenders.begin() + i--);
	}

	//fade out dead attackers
	for (int i = 0; i < Attackers.size(); i++)
	{
		if (Attackers[i]->getState() == DEATH)
		{
			if (Attackers[i]->isFinishedDying())
			{
				short alpha = Attackers[i]->getAlpha() - 5;
				
				if (alpha >= 0)
					Attackers[i]->setAlpha(alpha);
				else
					Attackers[i]->setX(-15.0f);
			}
		}
	}

	//fade out dead defenders
	for (int i = 0; i < Defenders.size(); i++)
	{
		if (Defenders[i]->getState() == DEATH)
		{
			if (Defenders[i]->isFinishedDying())
			{
				short alpha = Defenders[i]->getAlpha() - 5;

				if (alpha >= 0)
					Defenders[i]->setAlpha(alpha);
				else
					Defenders[i]->setX(-15.0f);
			}
		}
	}


}