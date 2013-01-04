
// placement editor loading code
#include "placement_editor.agc"

// globals for the placement editor
global dim g_Entities [ 1000 ] as tEntity
global dim g_MediaList [ 1000 ] as tEntity
global     g_iEntityCount = 0
global     g_iMediaCount  = 1
global	   g_fJoystickSpeed#

// load a level using a virtual resolution
LoadFromPlacementEditor ( "export.txt", "virtual" )

// load a level using the percentage system
// LoadFromPlacementEditor ( "export.txt", "percentage" )

// to delete data call
// DeletePlacementEditorData ( )

// our main loop
do
	// scroll the screen
	joystickX# = GetVirtualJoystickX ( 1 ) * g_fJoystickSpeed#
    joystickY# = GetVirtualJoystickY ( 1 ) * g_fJoystickSpeed#

	SetViewOffset ( GetViewOffsetX ( ) + joystickX#, GetViewOffsetY ( ) + joystickY# )

	// update the screen
	sync ( )
loop
