//////////////////////////
// template.cpp is kind of like our main.cpp.
// it contains our main loop, begin function, and end function
//////////////////////////

// Includes, namespace and prototypes
#include "template.h"
//#include "Globals.h"

using namespace AGK;
app App;

//Old memory management code that I think we have a better way of doing now, but keeping this just in case I'm wrong
/*unsigned short themeQueue[128];
unsigned short themeQueuePointer;
unsigned short menuQueue[128];
unsigned short menuQueuePointer;*/

////////////////////////////
//Begin app
//Inputs: None
//Outputs: None
//
//Gets called at the beginning of the app for set up purposes only
/////////////////////////////
void app::Begin( void )
{
	//set gameState to LOADING
	gameState = LOADING;
    
	//set the aspect ratio to the approriate amound (defined in defines.h)
	agk::SetDisplayAspect(ASPECT);
	
	//set the Orientation allowed
    agk::SetOrientationAllowed(0, 0, 1, 1);

	//set the border color, if displayed
	agk::SetBorderColor(0, 128, 0);

	//set the sync rate to 60 for loading purposes
	agk::SetSyncRate(60, 0);
    
	//Set transition mode to view rotation, if any
    agk::SetTransitionMode(1);

	//set the default font
	agk::SetTextDefaultFontImage(agk::LoadImage("Arial.png"));

	//Forgot what this means
    agk::SetResolutionMode(1);
   
	//Setting Error Mode
	agk::SetErrorMode(0);

	//setting debug on
	agk::SetPhysicsDebugOn();
}

/////////////////////////////
// Main loop
// Inputs: None
// Outputs: None
//
// Gets called every frame
///////////////////////////
void app::Loop ( void )
{
	//Switch to the appropriate game state
	switch (gameState)
	{
	case LOADING:
		//Load up main menu items
		//Since we're not concerned about the menu for the moment, just skip it and increment the state variable
		gameState++;
		break;
	case MENU:
		//Menu functionality
		//Again, not concerned with Menu yet, probably first implenetation will be a basic menu that allows devs to choose level to load

		//make gameState = to Playing, as we are assuming player is playing first level
		gameState = LEVEL_LOAD;
		break;
	case OPTIONS:
		//Specialized Menu Functionality
		//Not concerned with this
		break;
	case LEVEL_LOAD:
		//Loading Level-Specific options
		//Loading Tutorial Level for now, will have better logic later
		loadLevel(0);
		gameState++;
		break;
	case LEVEL_INIT:
		//Initializing the level
		CurrentLevel->init();
		gameState++;
		break;
	case PLAYING:
		//Call the level update to determine game level logic
		CurrentLevel->update();
		break;
	}
	
	//Sync to screen
	agk::Sync();
}

//////////////////////////
// End App
// Inputs: None
// Outputs: None
//
// Called when App Ends, can be used to save data if needed
//////////////////////////
void app::End ( void )
{
}

//////////////////////////////////////////////
// Load Level
// Inputs: Level Number to load
// Outputs: None
//
// Load the New Level into the global CurrentLevel
//////////////////////////////////////////
void app::loadLevel(unsigned short level)
{
	//Local Variables needed for the function
	Text LevelName("LevelData/Level ");
	
	//using 01, 02, 03...etc terminology
	if (level < 10)
		LevelName += Text("0");

	Text NumberText(agk::Str((float) level, 0));

	//Added .txt to the end too
	NumberText += Text(".txt");

	//Not sure why I need this yet, but I'm sure it's for relevant reasons
	std::vector<Creature> attackerCount;
	
	//Appending the Number Text to the Level Name
	LevelName += NumberText;

	//Another Local Variable that represents the level filepath and filename
	File LevelSource(true, LevelName);

	//Go through the level source file until it reaches the end
	//Look for Unlocked Attackers only
	//NOTE (12/31/12)--Bobby: I think the idea of this is to pre-load all of the characters before the level starts, which is good
	////////////////////////: So this means I think we need to load in the defenders as well, if this doesn't seem right, remove this note
	////////////////////////: Additionally, we should just add all attackers, not just the Unlocked ones
	while (!LevelSource.FileEOF())
	{
		//Local Variables for the Input File
		Text Input(LevelSource.getLine());
		//One line in the Source File is separated into two sections, the Category, and the Value(s)
		Text Category;
		Text Value;
		//Used when we convert the Text Object into an actual numerical value
		short value;

		//Splitting the Input into the Category and the Value at the colon
		Input.splitAtDelimeter(&Category, &Value, ':');

		//Turning the Value from a string to a number
		value = agk::Val(Value.getCString());

		//For this section we are only worried about attakers (for some reason that I can no longer remember)
		//Push the attackers onto the attackerCount vector
		if (Category == Text("Unlocked Attacker"))
			attackerCount.push_back((Creature) value);
	}

	//Copy level to the global, CurrentLevel
	switch (level)
	{
	case 0: //tutorial level
		//The only other attacker that needs to be put in is the MINER_VIRUS
		attackerCount.insert(attackerCount.begin(), MINER_VIRUS);
		//Construct the new Level and assign it CurrentLevel
		CurrentLevel = new Level00(attackerCount);
		break;
	}
}

//////////Memory Functions that I'm not sure we're using
/*void addToQueue(unsigned int imageNumber, short queue)
{
    if (queue == 0)
        themeQueue[themeQueuePointer++] = imageNumber;
    else
        menuQueue[menuQueuePointer++] = imageNumber;
}

void clearQueue(AnimatedSprite *Symbol, short queue)
{
    if (queue == 0)
    {
        for (int i = themeQueuePointer - 1; i > 0; i--)
        {
            agk::DeleteImage(themeQueue[i]);
        
            if (i % 5 == 0)
            {
                Symbol->incrementSpriteFrame();
                agk::Sync();
            }
        }
        
        themeQueuePointer = 0;
    }
    /*else
    {
        for (int i = menuQueuePointer - 1; i > 0; i--)
        {
            agk::DeleteImage(menuQueue[i]);
            
            if (i % 5 == 0)
            {
                Symbol->incrementSpriteFrame();
                agk::Sync();
            }
        }
        
        menuQueuePointer = 0;
    }
}

void initQueue(void)
{
    themeQueuePointer = 0;
    menuQueuePointer = 0;
}*/
////////////////////////////