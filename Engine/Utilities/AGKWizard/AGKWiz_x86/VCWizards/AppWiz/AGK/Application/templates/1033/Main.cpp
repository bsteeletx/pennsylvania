//  Project      : [!output PROJECT_NAME]
//	Name         : Main.cpp
//	Description  : The application main routines
//

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// include our main header file
#include "Main.h"

// let the compiler know we're using the AGK namespace
using namespace AGK;

// declare our app
app App;

// globals
int   width       = 0;
int   height      = 0;
int   orientation = 0;
char* platform    = NULL;

void app::Begin ( void )
{
	// TODO: Add your applications initialisation code here
		
	// get device width and height
	width = agk::GetDeviceWidth();
	height = agk::GetDeviceHeight();

	// find the current orientation
	orientation = agk::GetOrientation();

	// obtain the platform
	platform = agk::GetDeviceName();
}

void app::Loop(void)
{
	// print some information on screen
	agk::Print(width);
  agk::Print(height);
  agk::Print(orientation);
  agk::Print(platform);

	agk::Sync();
}

void app::End(void)
{

}
