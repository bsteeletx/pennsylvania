#pragma once
#include "AnimatedSprite.h"
#include "../Defines.h"
#include "File.h"

class Character :
	public AnimatedSprite
{
public:
	Character(void);
	~Character(void);
	Character(Text FilenamePath);
	
	//virtual void activateSpecial(AnimatedSprite Fog[8][5] = NULL, unsigned short *currency = 0);
	virtual void attack(Character *Target);
	virtual void damage(short amount);
	virtual void kill(Character *Killer);
	virtual void update(std::vector<Character*> Defenders);

	bool didAttackThisTurn(void);

	unsigned short getAttackAmount(void);
	unsigned short getCost(void);
	Creature getCreatureType(void);
	Character *getCurrentTarget(void);
	Character *getKilledBy(void);
	float getMoveSpeed(void);
	CharacterState getState(void);

	void init(void);
	bool isFinishedDying(void);
	bool isDefender(void);

	void repair(short amount);

	void setState(CharacterState State);
	void setVisible(bool visibility);

	bool isExample;

protected:
	short hitPoints;
	unsigned short maxHitPoints;
	float moveSpeed;
	unsigned short attackAmount;
	float attackSpeed;
	float timeFromLastAttack;
	Creature Type;
	File Data;
	bool hasRangedWeapon;
	bool didDamage;
	unsigned short cost;
	unsigned short idleFrameMin, idleFrameMax;
	float idleFrameSpeed;
	unsigned short moveFrameMin, moveFrameMax;
	float moveFrameSpeed;
	unsigned short attackFrameMin, attackFrameMax;
	float attackFrameSpeed;
	unsigned short deathFrameMin, deathFrameMax;
	float oldY;
	float deathFrameSpeed;
	CharacterState CurrentState;
	Character *CurrentTarget;
	
	Character *KilledBy;

	//void damageCharacter(unsigned short amount);
	void killCharacter(Character *Killer);
	void minerAttack(void);
	void normalAttack(Character *Target);
private:
};

