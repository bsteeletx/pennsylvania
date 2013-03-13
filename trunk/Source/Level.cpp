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
	currencyAmount = 0;
	reward = 0;
	isPaused = false;
	messageCounter = 0;
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
	currencyAmount = 0;
	reward = 0;
	levelID = levelNumber;
	isPaused = false;
	messageCounter = 0;
	
	for (unsigned int i = 0; i < AttackerList.size(); i++)
		AttackerInitList.push_back(AttackerList[i]);
}

//////////////////////////////////////////////////////
// Overload Operator =
// /////////////////////////////////////////////////
Level& Level::operator= (const Level &NewLevel)
{
	this->currencyAmount = NewLevel.currencyAmount;
	this->reward = NewLevel.reward;
	this->levelID = NewLevel.levelID;
	this->Attackers = NewLevel.Attackers;
	this->Defenders = NewLevel.Defenders;
	//this->objectStack = NewLevel.objectStack;
	//this->imageStack = NewLevel.imageStack;
	//this->spriteStack = NewLevel.spriteStack;

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
	Creature Type = (Creature) 0;
	Point Location = Point();
	Image Texture[3] = {NULL, NULL, NULL};
	Prompt = Text("", true);

	//Take Default beginning...
	Text LevelName = getLevelFilename();

	//Open Script File for reading
	File LevelSource = File(true, LevelName);
	//End Local Vars

	//Keep reading until at end of file
	while (!LevelSource.FileEOF())
	{
		//Each line of the script file is separated into two items, categories and values
		Text Input = Text(LevelSource.getLine());
		Text Category = Text();
		Text Value = Text();
		short value = 0;

		//Splitting the line at the colon
		Input.splitAtDelimeter(&Category, &Value, ':');
		
		//Check for what category we're looking for and assigne the value to the appropriate variable
		if (Category == Text("Background Image", false))
			addBackground(Value);
		else if (Category == Text("Creature Location", false))
		{
			Location.setX((float) Value.getChar(0) - 48); //subtracting 48 to get to number values as 0 = 48 in ASCII
			Location.setY((float) Value.getChar(2) - 48);
			addCreatureType(Type, Location);
		}
		else if (Category == Text("Reward", false))
		{
			Text *NewCategory = new Text();
			Text *NewValue = new Text();

			Value.splitAtDelimeter(NewCategory, NewValue, ':');

			if (*NewCategory == Text("Creature"))
				reward = agk::Val(NewValue->getCString(), 10);
		}
		else
		{
			value = agk::Val(Value.getCString());

			//To save memory, need to load Creature Types--hold off on Attacker Types
			//until we have an Attacker Selector Menu, then load those Attackers
			//Load initial defenders offscreen, then clone and place them in the 
			//correct location
			//NOTE (1/1/13): We may just load all creatures ahead of time, making part of this unnecessary
			if (Category == Text("Creature Type", false))
				Type = (Creature) value;
			else if (Category == Text("Starting Data", false))
				currencyAmount = value;
			else if (Category == Text("Fog", false))
			{
				if (value == 1)
					fogEnabled = true;
				else
					fogEnabled = false;
			}
		}
	}

	LevelSource.close();

	setAttackerMenu();

	//Load in the Selector
#if (PLATFORM == PC)
	Selector = Sprite(Text("Assets/Common/selector.png"), false);
	Selector.setOffset(Selector.getWidth()/2, Selector.getHeight()/2);
	addSprite(Selector.getSpriteNumber());
	Selector.setSize(12.5f);
	Selector.setOffset(1.5f, 1.9f);
#endif

	displayCurrency();
	
	//Null out the Selected Creature
	Selected = (Creature) NULL;

	CreatureFrame = Sprite(); //Need an actual frame here
	CreatureFrame.setPosition(Point(33.3f, 33.3f));
	CreatureFrame.setSize(40.0f, 70.0f);
	CreatureFrame.setVisible(false);
	
	Song.setSystemVolume(100);
}

void Level::displayCurrency(void)
{
	//Place the text for player's currency, set the color and position
	CurrencyTitle = Text("Bytes: ", true);
	CurrencyValue = Text(agk::Str(currencyAmount), true);

	CurrencyTitle.setColor(RGBA(255, 255, 255));
	CurrencyValue.setColor(RGBA(255, 255, 255));

	CurrencyTitle.setPosition(Point(2.0f, 95.0f));
	CurrencyValue.setPosition(Point(15.0f, 95.0f));

}

//////////////////////////////
// Set Attacker Menu
// Input None
// Output Attackers placed
//////////////////////////////
void Level::setAttackerMenu(void)
{
	//set up attacker choice menu
	for (unsigned int i = 0; i < AttackerInitList.size(); i++)
	{
		//Assign Grid Location to Location Value
		Point AssignedLocation((float) i, 0.0f);
		//Create another Location for Normal Coords
		Point NormalCoords = AssignedLocation.getNormalCoords();

		//Add creature normally
		addCreatureType(AttackerInitList[i], AssignedLocation);
		//subtrack 15 from the y to place the creature in the selection area as opposed to the game board
		NormalCoords.setY(NormalCoords.getY() - 15.0f);
		Attackers.back()->setY(NormalCoords.getY());
		Attackers.back()->isExample = true;
		//Alpha out the creature a bit and set in the pose state
		//Attackers.back()->setColorAlpha(128);
		Attackers.back()->setState(MENU_HIDDEN); 
	}
}

///////////////////////////////
// Get Level Filename
// Input none
// Output Text Object that contains filename of level
//////////////////////////////
Text Level::getLevelFilename(void)
{
	Text ReturnText = Text("LevelData/Level ");
	Text NumberText = Text(agk::Str((float) levelID, 0));
	
	if (levelID < 10)
		ReturnText += "0";

	//...Add Number to end to have the script file
	ReturnText += NumberText;
	ReturnText += Text(".txt");

	return ReturnText;
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
	//imageStack.clear();
	//spriteStack.clear();

	//objectStack.clear();

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
		//addSprite(Defenders.back()->getSpriteNumber());
		Defenders.back()->setState(IDLE);
		//Give the game a sense of depth: The further to the bottom, depth should be less than top
		//Location is in grid coordinates 
		//Defenders.back()->setDepth(Defenders.back()->getDepth() - (short) Location.getY());
	}
	else
	{
		//addSprite(Attackers.back()->getSpriteNumber());
		
		if (!Attackers.back()->isExample)
			Attackers.back()->setState(SELECTED);
		else
			Attackers.back()->setState(MENU_TOOMUCH);
		//Give the game a sense of depth: The further to the bottom, depth should be less than top
		//Location is in grid coordinates 
		//Attackers.back()->setDepth(Attackers.back()->getDepth() - (short) Location.getY());
	}

}

////////////////////////////////////////////
// get Paused
// Input: none
// output: returns whether the level is paused or not
// ///////////////////////////////////////
bool Level::getPaused(void)
{
	return isPaused;
}

void Level::togglePause(void)
{
	isPaused = !isPaused;
}

/////////////////////////////
// Get OK Location
// Input: Mouse Location
// Output: If the location is a valid spot on the grid
//////////////////////////////
bool Level::getOKLocation(Point Location)
{
	bool valid = false;
	Location.setCoordsAsGridCoords();
	unsigned short gridX = (int) Location.getX();
	short gridY = (int) Location.getY();
	
	//Check for Fog
	//Limiting locations currently to the far right 3 columns, this isn't a game design mention, just following I, Zombie
	if (gridX >= 5)
	{
		if (!fogEnabled)
			valid = true;
		else if (!getFog(Location))
			valid = true;
	}
	else if (gridY < 0)
	{
		if (gridX >= 0)
		{
			//Check to see if player is selecting a creature to spawn
			if (gridX <= AttackerInitList.size() - 1)
				valid = true;
		}
	}

	return valid;
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

	//set the Green Selector to the Mouse's Grid Position
	if (!isPaused)
	{
		Selector.setPositionByOffset(MouseLoc.getGridCoords().getNormalCoords());
		Selector.setVisible(true);
	}
	else
	{
		Selector.setVisible(false);
		return;
	}

	//Adding a creature
	if (agk::GetPointerReleased())
	{
		bool validLocation = getOKLocation(MouseLoc);
		unsigned short gridX = (int) MouseLoc.getGridCoords().getX();
		short gridY = (int) MouseLoc.getGridCoords().getY();
				
		if (validLocation)
		{
			if (gridY < 0)
				selectCreature(gridX);
				
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
				Attackers.back()->setState(IDLE);
				Attackers.back()->incrementCount();
			}
		}
		
	}

	//If the player has an attacker selected, set the attackers position to the Mouse Location
	if (Selected != (Creature) NULL)
		Attackers.back()->setPosition(MouseLoc.getGridCoords().getNormalCoords());
	
	//Display Currency
	CurrencyValue.setString(agk::Str(currencyAmount));
}

///////////////////////////////
// Prompt
// Input: Message to display
// Output: Message displayed with a background
//////////////////////////////////
void Level::getPrompt(void)
{
	Text Filename = Text("LevelData/Level_");
	Text PromptNumber = Text();
	Text NewLine = Text();

	if (levelID < 10)
		Filename += Text("0");

	Filename += Text(agk::Str(levelID));
	Filename += Text("_Messages.txt");

	File MessagePrompts = File(true, Filename);

	while (!MessagePrompts.FileEOF())
	{
		NewLine = MessagePrompts.getLine();
			
		NewLine.splitAtDelimeter(&PromptNumber, &Prompt, ':');

		if (agk::Val(PromptNumber.getCString(), 10) == messageCounter)
			break;
	}

	MessagePrompts.close();

	Prompt.setVisible(false);
	messageCounter++;
}

void Level::selectCreature(unsigned short grid)
{
	//make sure the character is available, could check any color, not just blue
	if (Attackers[grid]->getState() == MENU_AVAILABLE)
	{
		//make sure the player has the currency to purchase it
		if (Attackers[grid]->getCost() <= currencyAmount)
		{
			Selected = Attackers[grid]->getCreatureType();
			addCreatureType(Selected, Point(agk::GetPointerX(), agk::GetPointerY()));
			Attackers.back()->isExample = true;
			Attackers.back()->setState(SELECTED);
		}
	}
}

void Level::setFrameVisible(bool isVisible)
{
	CreatureFrame.setVisible(isVisible);
	CreatureFrame.setSize(40.0f, 65.0f);
	//Need more here...do we add the creature here? I don't think so,
	//it looks like right now this is a one line code, kind of a waste
}

void Level::setPrompt(void)
{
	if (!isPaused)
		togglePause();

	PromptBackground = Sprite();
	PromptBackground.setColor(RGBA(0, 0, 255));
	PromptBackground.setPosition(Point(25.0f, 80.0f));
	PromptBackground.setSize(50.0f, 15.0f);

	Prompt.setMaxWidth(50.0f);
	Prompt.setAlignment(Prompt.CENTER);
	Prompt.setPosition(Point(50.0f, 80.0f));
	Prompt.setVisible(true);
}

void Level::showCreature(Character *Example)
{
	ExampleChar = Example;
	CreatureLoc = Point(ExampleChar->getPosition());
	
	ExampleChar->setState(IDLE);
	ExampleChar->setPositionByOffset(50.0f, 50.0f);
	originalSize = ExampleChar->getWidth();
	ExampleChar->setSize(33.0f);
	originalDepth = ExampleChar->getDepth();
	ExampleChar->setDepth(1);

	CreatureLoc.setX((ExampleChar->getX() - CreatureLoc.getX())/23.0f);
	CreatureLoc.setY((ExampleChar->getY() - CreatureLoc.getY())/23.0f);

	setFrameVisible(true);
	getPrompt();
	setPrompt();
}

void Level::sizeDownCreature(void)
{
	setFrameVisible(false);
	PromptBackground.setVisible(false);
	Prompt.setVisible(false);

	float sizeChange = (33.0f - originalSize)/23.0f;

	for (int i = 0; i < 24; i++)
	{
		ExampleChar->setSize(33.0f - (sizeChange*i));
		ExampleChar->setX(ExampleChar->getX() - CreatureLoc.getX());
		ExampleChar->setY(ExampleChar->getY() - CreatureLoc.getY());

		if (!ExampleChar->isExample)
		{
			if (ExampleChar->getY() < 17.5f)
				ExampleChar->setY(17.5f);
		}

		agk::Sync();
	}

	Point Position = ExampleChar->getPosition();
	Position.setX((float) agk::Ceil(Position.getX()));
	Position.setY((float) agk::Ceil(Position.getY()));
	ExampleChar->setPosition(Position);

	ExampleChar->setPosition(ExampleChar->getPosition().getGridCoords().getNormalCoords());
	ExampleChar->setDepth(originalDepth);

	if (ExampleChar->isExample)
		ExampleChar->setState(MENU_AVAILABLE);

	togglePause();
}

////////////////////////////
// Update Level
// Input: None
// Output: None;
///////////////////////////////
void Level::update(void)
{
	bool gameOver = true;

	handleUI();

	if (!isPaused)
		updateCharacters();
	else if (agk::GetPointerReleased() == 1)
	{
		if (ExampleChar->getWidth() >= 30.0f)
			sizeDownCreature();
	}

	if (!Song.getPlaying())
		Song.play();

	for (unsigned int i = 0; i < Defenders.size(); i++)
	{
		if (Defenders[i]->getCreatureType() == INFORMATION_NODE)
		{
			gameOver = false;
			break;
		}
	}

	if (gameOver)
		giveReward();
}

////////////////////////////////////
// Give Reward
// Input None
// Output show player reward, end level
///////////////////////////////////
void Level::giveReward(void)
{
	//assuming it will always be a creature for now
	//might already be rewarded due to replay, so need some way of
	//checking that first
	addCreatureType((Creature) reward, Point(0.0f, 0.0f));
	showCreature(Attackers.back());
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
	updateAttackers();
	//Update Defenders
	updateDefenders();
	
	//Removing Creature if offscreen
	creatureRemoval();
	
	//fade out dead attackers
	setCreatureFadeout();
}

void Level::updateAttackers(void)
{
	for (unsigned int i = 0; i < Attackers.size(); i++)
	{
		//general update
		Attackers[i]->update(Defenders);
		
		//Ensure Example Attackers stay in pose
		if (Attackers[i]->isExample)
		{
			if (Attackers[i]->getColorBlue() != 0)
			{
				if (Attackers[i]->getCost() > currencyAmount)
					Attackers[i]->setState(MENU_TOOMUCH);
				else
					Attackers[i]->setState(MENU_AVAILABLE);
				continue;
			}
		}

		//Miner Virus doesn't really attack, just gets a default amount of currency every now and then
		if (Attackers[i]->getCreatureType() == MINER_VIRUS)
		{
			if (Attackers[i]->didAttackThisTurn())
				currencyAmount += Attackers[i]->getAttackAmount();
		}
	}
}

void Level::updateDefenders(void)
{
	for (unsigned int i = 0; i < Defenders.size(); i++)
		Defenders[i]->update(Attackers);
}

void Level::creatureRemoval(void)
{
	for (unsigned int i = 0; i < Attackers.size(); i++)
	{
		//check to see if offscreen--remember that sprite is measured at top left, so it has to be a bit off screen
		if (Attackers[i]->getX() < -10.0f)
			Attackers.erase(Attackers.begin() + i--);
	}

	//Removing Defender if offscreen (placed offscreen when dead, or potentially, walk
	//off screen to right)
	for (unsigned int i = 0; i < Defenders.size(); i++)
	{
		if (Defenders[i]->getX() < -10.0f)
			Defenders.erase(Defenders.begin() + i--);
		else if (Defenders[i]->getX() > 110.0f)
			Defenders.erase(Defenders.begin() + i--);
	}
}

void Level::setCreatureFadeout(void)
{
	for (unsigned int i = 0; i < Attackers.size(); i++)
	{
		if (Attackers[i]->getState() == DEATH)
		{
			if (Attackers[i]->getIsFinishedDying())
				Attackers[i]->setState(FADEOUT);
		}
	}

	//fade out dead defenders
	for (unsigned int i = 0; i < Defenders.size(); i++)
	{
		if (Defenders[i]->getState() == DEATH)
		{
			if (Defenders[i]->getIsFinishedDying())
				Defenders[i]->setState(FADEOUT);
		
		}
	}
}