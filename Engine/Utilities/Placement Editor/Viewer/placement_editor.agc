
type tEntity
	file as string
	id   as integer
	image as integer

	originalMediaIndex as integer

	properties as string
endtype

function LoadFromPlacementEditor ( file$, mode$ )
	// now load the file
	file = OpenToRead ( file$ )

	// find out whether virtual or percentage system is being used
	vMode$         = ReadLine ( file )
	displayWidth$  = ReadLine ( file )
	displayHeight$ = ReadLine ( file )
	screenWidth$   = ReadLine ( file )
	screenHeight$  = ReadLine ( file )
	screenX$       = ReadLine ( file )
	screenY$       = ReadLine ( file )
	width#         = val ( displayWidth$ )
	height#        = val ( displayHeight$ )

	g_fJoystickSpeed# = 4.0

	if ( mode$ = "virtual" )
		SetVirtualResolution ( width#, height# )
		AddVirtualJoystick ( 1, width# - 60, height# - 60, 100 )
	else
		g_fJoystickSpeed# = 1.0
		SetDisplayAspect ( width# / height# )
		AddVirtualJoystick   ( 1, 85, 90, 15 )
	endif

	// next block of data is related to the editor - we don't need to care about this
	temp$ = ReadLine ( file )
	temp$ = ReadLine ( file )
	temp$ = ReadLine ( file )
	x$ = ReadLine ( file )
	y$ = ReadLine ( file )

	SetViewOffset ( val ( x$ ), val ( y$ ) )

	mediaCount$ = ReadLine ( file )

	g_iMediaCount = val ( mediaCount$ ) - 1

	for i = 0 to val ( mediaCount$ ) - 1
		g_MediaList [ i ].file = ReadLine ( file )
		g_MediaList [ i ].image = LoadImage ( g_MediaList [ i ].file )
	next i

	// now get the entity count
	entityCount$ = ReadLine ( file )

	// load all the entities
	for i = 0 to val ( entityCount$ ) - 1

		image$  = ReadLine ( file )
		index$  = ReadLine ( file )
		x$      = ReadLine ( file )
		y$      = ReadLine ( file )
		percentageX$  = ReadLine ( file )
		percentageY$  = ReadLine ( file )
		percentageWidth$  = ReadLine ( file )
		percentageHeight$  = ReadLine ( file )
		locked$ = ReadLine ( file )
		depth$  = ReadLine ( file )

		properties$ = ReadLine ( file )
		scaleX$ = ReadLine ( file )
		scaleY$ = ReadLine ( file )
		angle$ = ReadLine ( file )
		mirror$ = ReadLine ( file )
		flip$ = ReadLine ( file )

		index = val ( index$ )

		// create a new entity using the image from the media list
		g_Entities [ g_iEntityCount ].id   = CreateSprite ( g_MediaList [ index ].image )
		g_Entities [ g_iEntityCount ].properties = properties$

		// store the entities ID number
		id = g_Entities [ g_iEntityCount ].id

		if ( mode$ = "virtual" )
			SetSpritePosition ( id, val ( x$ ), val ( y$ ) )
		else
			SetSpritePosition ( id, val ( percentageX$ ), val ( percentageY$ ) )

			SetSpriteSize ( id, val ( percentageWidth$ ), val ( percentageHeight$ ) )
		endif

		if ( i = 0 and mode$ = "percentage" )
			x# = ( GetSpriteX ( id ) )
			y# = ( GetSpriteY ( id ) )

			SetViewOffset ( x#, y# )
		endif

		SetSpriteDepth ( id, val ( depth$ ) )
		SetSpriteVisible ( id, 1 )

		if ( mode$ = "virtual" )
			SetSpriteScale ( id, val ( scaleX$ ), val ( scaleY$ ) )
		endif

		SetSpriteAngle ( id, val ( angle$ ) )
		SetSpriteFlip ( id, val ( mirror$ ), val ( flip$ ) )

		g_iEntityCount = g_iEntityCount + 1
	next i

	CloseFile ( file )
endfunction

function DeletePlacementEditorData ( )
	for i = 0 to g_iEntityCount
		DeleteSprite ( g_Entities [ i ].id )
	next i

	for i = 0 to g_iMediaCount
		DeleteImage ( g_MediaList [ i ].id )
	next i

	g_iEntityCount = 0
	g_iMediaCount = 1
endfunction







