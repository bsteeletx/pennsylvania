#pragma once
//#include "Character.h"
#include "CreatureList.h"
#include <vector>
//#include "Object.h"
#include "Wall.h"
#include "Camera.h"
#include "Ceiling.h"
#include "Floor.h"
#include "PointLight.h"
#include "Sun.h"
#include "MyJoystick.h"
#include "Selector.h"

class Level
{
public:
	Level(void);
	Level(short levelNumber, std::vector<Creature> AttackerList);
	~Level(void);

	Level& Level::operator= (const Level &NewLevel);

	//void addBackground(Text PathFilename);
	void addCeiling(Image Texture);
	void addCreatureType(Creature creatureNumber, Point Location);
	void addFloor(Image Texture);
	//void addSprite(unsigned int image);
	void addWalls(Image WallTexture[3]);
	
	virtual void deleteLevel(void);

	virtual bool getFog(Point GridLocation) = 0;
	
	void handleUI(void);

	virtual void init(void);

	virtual void update(void);
	void updateCharacters(void);

	unsigned short currencyAmount;

protected:
	Selector MouseBox;

	std::vector<Character*> Attackers;
	std::vector<Character*> Defenders;

	unsigned short reward;

private:
	//std::vector<unsigned int> imageStack;
	//std::vector<unsigned int> spriteStack;
	enum WallTypes
	{
		LEFT_WALL,
		BACK_WALL,
		RIGHT_WALL
	};

	enum CameraSettings
	{
		FRONT,
		TOP,
		LEFT,
		RIGHT
	};

	struct CameraFrontSettings
	{

	};

	Camera LevelCam;
	Wall Walls[3];
	Ceiling Sky;
	Floor Ground;
	MyJoystick CameraControl;
	Sun Sol;

	CameraSettings currentView;
	
	bool fogEnabled;

	unsigned short levelID;

	bool offsetSelector;

	Point GridLocs[9][6];

	Text CurrencyTitle;
	Text CurrencyValue;

	Creature Selected;
	std::vector<Creature> AttackerInitList;

	void switchCamera(CameraSettings newSetting);

	void updateCamera(void);
};

