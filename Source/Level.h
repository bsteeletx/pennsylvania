#pragma once
#include "Character.h"
#include "Vietnam/Image.h"
#include "Vietnam/Sprite.h"
#include "CreatureList.h"
#include <vector>

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

	virtual bool getFog(Point GridLocation) = 0;
	
	void handleUI(void);

	virtual void init(void);

	virtual void update(void);
	void updateCharacters(void);

	unsigned short currencyAmount;

protected:
	Sprite Selector;
	Sprite Background;

	std::vector<Character*> Attackers;
	std::vector<Character*> Defenders;

	unsigned short reward;

private:
	std::vector<unsigned int> imageStack;
	std::vector<unsigned int> spriteStack;
	
	bool fogEnabled;

	unsigned short levelID;

	bool offsetSelector;

	Point GridLocs[9][6];

	Text CurrencyTitle;
	Text CurrencyValue;

	Creature Selected;
	std::vector<Creature> AttackerInitList;
};

