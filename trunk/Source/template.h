#ifndef _H_APP
#define _H_APP

// Link to AGK libraries
#include "Globals.h"
#include "Levels.h"

// Global values for the app
class app
{
	public:

		// main vars
		float mouseX;
		float mouseY;

		short gameState;

		//objects
		Level *CurrentLevel;

		//methods
		void loadLevel(unsigned short level);
	
	public:

		// constructor
		app() { memset ( this, 0, sizeof(app)); }

		// main app functions
		void Begin( void );
		void Loop( void );
		void End( void );

		//custom functions
		//void physicsTest(void);
		//void pushObject(Vector2D vector);
};

extern app App;

#endif

// Allow us to use the LoadImage function name
#ifdef LoadImage
 #undef LoadImage
#endif


//Global Functions
void clearQueue(AnimatedSprite *Symbol, short queue);
void addToQueue(unsigned int imageNumber, short queue);