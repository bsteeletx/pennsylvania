#pragma once
#include "Level.h"
//AlarmSystem needs to be defined
#include "Alarm.h"
#include "Sprite.h"

class Level00 :
	public Level
{
public:
	Level00(void);
	Level00(std::vector<Creature> attackerList);
	~Level00(void);

	void deleteLevel(void);

	bool getFog(Point GridLocation);
	
	void init(void);

	void update(void);

private:
	bool bugDeath;
	bool unlockedDefenders;
	std::vector<unsigned int> hiddenDefenderStack;

	unsigned short unlockNum;
	std::vector<unsigned short> currencyForUnlock;
	std::vector<Creature> unlockedAttacker;

	unsigned short currencyGained;

	bool shownCreature[8];

	Alarm AlarmSystem;
	Sprite Highlighter;

	bool checkForKilling(Creature Type);

	void doPrompts(unsigned int creatureID = 0);

	void updateAttackers(void);
	void updateDefenders(void);
};

