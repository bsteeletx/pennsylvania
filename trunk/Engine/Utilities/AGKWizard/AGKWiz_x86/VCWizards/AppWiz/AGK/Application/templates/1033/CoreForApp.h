//  Project      : [!output PROJECT_NAME]
//	Name         : CoreForApp.h
//	Description  : Header file for the core routines.
//

#pragma once

// app header
#include "Main.h"

// app specific defines
#define DEVICE_WIDTH  [!output AGK_SCREEN_WIDTH]
#define DEVICE_HEIGHT [!output AGK_SCREEN_HEIGHT]
#define DEVICE_POS_X  [!output AGK_SCREEN_POS_X]
#define DEVICE_POS_Y  [!output AGK_SCREEN_POS_Y]

// Application initialisation code
int AppInitCode(char* pNameOfApp)
{
	// If app already running, quit
	HANDLE g_hWindowMutex = CreateMutex(NULL, TRUE, pNameOfApp);
	if (g_hWindowMutex!=NULL)
	{
		if (GetLastError()== ERROR_ALREADY_EXISTS)
		{
			CloseHandle((HANDLE)g_hWindowMutex);
			return 0;
		}
	}
	return 1;
}

// Application can gather data about the window app
void AppGatherData(HWND hWnd, char* lpCmdLine)
{
}

// Application can keep windows loop active
int AppKeepActive(void)
{
	return 1;
}
