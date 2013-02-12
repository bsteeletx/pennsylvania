#pragma once
#include "AnimatedSprite.h"
#include "Defines.h"
#include "File.h"
#include "Object.h"

class Character :
	public BoxObject
{
public:
	Character(void);
	~Character(void);
	Character(Text FilenamePath);
	
	//virtual void activateSpecial(AnimatedSprite Fog[8][5] = NULL, unsigned short *currency = 0);
	virtual void attack(Character *Target);

	virtual void damage(short amount);
	bool didAttackThisTurn(void);

	unsigned short getAttackAmount(void);	
	unsigned short getCost(void);
	Creature getCreatureType(void);
	Character *getCurrentTarget(void);
	bool getIsFinishedDying(void);
	bool getIsDefender(void);	
	Character *getKilledBy(void);
	float getMoveSpeed(void);
	CharacterState getState(void);

	void init(void);
	
	virtual void kill(Character *Killer);	
	
	void repair(short amount);	

	void setAlphaOut(bool isAlphaOut, CollisionGroup Group = GHOSTS);
	void setBluedOut(bool isBluedOut);
	void setState(CharacterState State);
	void setVisible(bool visibility);

	virtual void update(std::vector<Character*> Defenders);

	bool isExample;

protected:
	unsigned short attackAmount;
	unsigned short attackFrameMin, attackFrameMax;
	float attackFrameSpeed;
	float attackSpeed;

	unsigned short cost;

	unsigned short deathFrameMin, deathFrameMax;
	float deathFrameSpeed;
	bool didDamage;

	bool hasRangedWeapon;
	short hitPoints;

	unsigned short idleFrameMin, idleFrameMax;
	float idleFrameSpeed;

	unsigned short maxHitPoints;
	unsigned short moveFrameMin, moveFrameMax;
	float moveFrameSpeed;
	float moveSpeed;
	
	float oldY;
	
	float timeFromLastAttack;
	
	AnimatedSprite *Texture;

	Character *CurrentTarget;
	Character *KilledBy;
	CharacterState CurrentState;
	Creature Type;
	
	File Data;
		
	void killCharacter(Character *Killer);
	
	void minerAttack(void);
	
	void normalAttack(Character *Target);
protected:

	Point OffsetAmount;
};

