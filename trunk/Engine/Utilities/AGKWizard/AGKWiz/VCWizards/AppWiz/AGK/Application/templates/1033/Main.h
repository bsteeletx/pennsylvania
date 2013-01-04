//  Project      : [!output PROJECT_NAME]
//	Name         : Main.h
//	Description  : Main header file for the application.
//

#pragma once

// Link to GDK libraries
#include "AGK.h"

// Global values for the app
class app
{
	public:

		// constructor
		app() { memset(this, 0, sizeof(app)); }

		// main app functions
		void Begin(void);
		void Loop(void);
		void End(void);
};

extern app App;

// Allow us to use the LoadImage function name
#ifdef LoadImage
 #undef LoadImage
#endif
