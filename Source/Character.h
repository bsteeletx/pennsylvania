#pragma once
#include "AnimatedSprite.h"
#include "Defines.h"
#include "File.h"

class Character :
	public AnimatedSprite
{
public:
	Character(void);
	~Character(void);
	Character(Text FilenamePath);
	
	//virtual void activateSpecial(AnimatedSprite Fog[8][5] = NULL, unsigned short *currency = 0);
	virtual void attack(float currentTime, Character *Target);

	virtual void damage(short amount, Character *Attacker);
	bool didAttackThisTurn(void);

	virtual void fireWeapon(void);

	unsigned short getAttackAmount(void);	
	unsigned short getCost(void);
	Creature getCreatureType(void);
	Character *getCurrentTarget(void);
	bool getIsFinishedDying(void);
	bool getIsDefender(void);	
	Character *getKilledBy(void);
	float getMoveSpeed(void);
	CharacterState getState(void);

	virtual void incrementCount(void) {};
	void init(void);
	
	virtual void kill(Character *Killer);	
	
	void repair(short amount);	

	void setAlphaOut(bool isAlphaOut, CollisionGroup Group = GHOSTS);
	void setBluedOut(bool isBluedOut);
	void setState(CharacterState State);
	void setVisible(bool visibility);

	virtual void update(float currentTime, std::vector<Character*> Defenders);
	void updateCost(unsigned short creatureCount);

	bool isExample;

protected:
	unsigned short attackAmount;
	unsigned short attackFrameMin, attackFrameMax;
	float attackFrameSpeed;
	float attackSpeed;

	unsigned short cost;
	unsigned short costCurrent;
	unsigned short costIncrease;
	unsigned short costFactor;
	unsigned short costPower;

	unsigned short deathFrameMin, deathFrameMax;
	float deathFrameSpeed;
	bool didDamage;

	bool hasRangedWeapon;
	unsigned short healthDrainAmount;
	unsigned short healthDrainRate;
	short hitPoints;

	unsigned short idleFrameMin, idleFrameMax;
	float idleFrameSpeed;

	unsigned short maxHitPoints;
	unsigned short moveFrameMin, moveFrameMax;
	float moveFrameSpeed;
	float moveSpeed;
	
	float oldY;
	
	float timeFromLastAttack;
	
	Character *CurrentTarget;
	Character *KilledBy;
	CharacterState CurrentState;
	Creature Type;
	
	File Data;
		
	void killCharacter(Character *Killer);
	
	void minerAttack(float currentTime);
	
	void normalAttack(Character *Target);
protected:

	Point OffsetAmount;
};

