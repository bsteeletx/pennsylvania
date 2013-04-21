#pragma once
#include "Advert.h"
#include "Character.h"
#include "Image.h"
#include "Sprite.h"
#include "CreatureList.h"
#include <vector>
#include "Music.h"

class Level
{
public:
	Level(void);
	Level(short levelNumber, std::vector<Creature> AttackerList);
	~Level(void);

	Level& Level::operator= (const Level &NewLevel);

	void addBackground(Text PathFilename);
	void addCreatureType(Creature creatureNumber, Point Location);
	void addSprite(unsigned int image);
		
	virtual void deleteLevel(void);
	
	Creature getCreatureTypeFromString(Text CreatureString);
	virtual bool getFog(Point GridLocation) = 0;
	bool getPaused(void);
	void getPrompt(void);
	void giveReward(void);

	void handleUI(void);
	
	virtual void init(void);
	void initCreatureCosts(void);
	void initFromFile(Text Filename);
	
	void setFrameVisible(bool visible);
	void setPrompt(void);
	void showCreature(Character *Example);
	void sizeDownCreature(void);

	void togglePause(void);

	virtual void update(void);
	void updateCharacters(float currentTime);

	unsigned short currencyAmount;

protected:
#if (PLATFORM == OS)
	Sprite Selector;
#endif
	Sprite Background;
	Sprite BottomFrame;
	
	Sprite CreatureFrame;

	Sprite DataStream[16];

	Sprite MenuHex[9];
	
	Image LevelPieces;
	Text Prompt;
	Sprite PromptBackground;
	
	Music Song;
	
	std::vector<Character*> Attackers;
	std::vector<Character*> Defenders;

	bool isPaused;
	
	unsigned short reward;

	void selectCreature(unsigned short grid);

	enum DataStreamParts
	{
		ELBOW,
		MAIN1,
		MAIN2,
		MAIN3,
		MAIN4,
		MAIN5,
		TERMINAL00,
		TERMINAL01,
		TERMINAL10,
		TERMINAL11,
		TERMINAL20,
		TERMINAL21,
		TERMINAL30,
		TERMINAL31,
		TERMINAL40,
		TERMINAL41
	};

private:
	std::vector<unsigned int> imageStack;
	std::vector<unsigned int> spriteStack;
	
	unsigned short creatureCost[9];

	bool fogEnabled;

	unsigned short levelID;

	unsigned short messageCounter;
	float menuSize;

	unsigned short originalDepth;
	float originalSize;
	Point OriginalGridLoc;

	Advert *Ad;

	Character *ExampleChar;

	Point CreatureLoc;
	Text CreatureCosts[9];

	Text CurrencyTitle;
	Text CurrencyValue;

	Creature Selected;
	std::vector<Creature> AttackerInitList;

	void creatureRemoval(void);

	void displayCurrency(void);

	Text getLevelFilename(void);
	bool getOKLocation(Point Location);

	void setAttackerMenu(void);
	void setCreatureFadeout(void);

	void updateAttackers(float currentTime);
	void updateDefenders(float currentTime);
};

