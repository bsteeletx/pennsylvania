////////////////////////////
// Character class
////////////////////////////

#include "Character.h"
#include "agk.h"

//////////////////////////////////////
// Default Constructor
// Input: None
// Result: Character created
// Note: Does a character HAVE an Animated Sprite as part of its makeup?
//       Or IS a character a special type of Animated Sprite?
//       I think it's the first one, but when I first created it, I was obviously thinking the second
////////////////////////////////////////////
Character::Character(void)
	: AnimatedSprite()
{
	maxHitPoints = hitPoints = 1;
}

////////////////////////////////////////////////
// Constructor
// Input: Text Filename and path for the animated sprite
// Result: Character Object Created
// Note: See Above
//       Also, should only set up variables, save everything else for initialization
//////////////////////////////////////////
Character::Character(Text FilenamePath)
	: AnimatedSprite(File (true, FilenamePath), Text ("Assets/Creatures/Creatures.png"))
{
	Data = File(true, FilenamePath);
	init();
	didDamage = false;
	//setCollisionGroup((int)EXAMPLES);
	hasRangedWeapon = false;
	CurrentTarget = NULL;
}

////////////////////////////////
// Destructor
// Input: None
// Result: Character is destroyed
/////////////////////////////
Character::~Character(void)
{
}

////////////////////////////////////////////
// Attack
// Input: Pointer to Target Character that this character is attacking
// Result: If it is time to attack, attack, otherwise do nothing
// Note: I think this function is doing too much.
//       It shouldn't determine whether it's time to attack
//       Another function should determine the time
//       This function should just attack
//////////////////////////////////////////
void Character::attack(Character *Target)
{
	if (timeFromLastAttack == 0)
	{
		timeFromLastAttack = agk::Timer();
		return;
	}

	if (agk::Timer() - timeFromLastAttack > attackSpeed)
	{
		Target->damage(attackAmount);
		
		if (Target->hitPoints <= 0)
		{
			Target->kill(this);
			setState(IDLE);
			CurrentTarget = NULL;
		}

		timeFromLastAttack = agk::Timer();
		didDamage = true;
	}
	else
		didDamage = false;

	CurrentTarget = Target;
}

/////////////////////////////////////
// Miner Attack
// Input: None
// Result: Miner does its 'attack', but it's just a gathering data
// Note: I don't like that the minerAttack is here.
//       In fact, the gathering data should not be considered an attack as well
//       It should be part of the update of the Miner class
////////////////////////////////////
void Character::minerAttack(void)
{
	if (agk::Timer() - timeFromLastAttack > attackSpeed)
	{
		if (getCreatureType() == MINER_VIRUS)
		{
			timeFromLastAttack = agk::Timer();
			didDamage = true;
		}
	}
	else
		didDamage = false;
}

/////////////////////////////////////////
// Damage
// Input: amount to be damaged
// Result: Character's hit points are reduced by the amount
///////////////////////////////////////
void Character::damage(short amount)
{
	hitPoints -= amount;
}

/////////////////////////////////////////
// Did the character attack this turn?
// Input: None
// Output: Boolean true for yes, false for no
/////////////////////////////////////////
bool Character::didAttackThisTurn(void)
{
	return didDamage;
}

//////////////////////////////////////////////////////
// Get Attack Amount
// Input: None
// Output: Return the amount of damage the Character did
//////////////////////////////////////////////////
unsigned short Character::getAttackAmount(void)
{
	return attackAmount;
}

//////////////////////////////////////////////
// Get Creature Type
// Input: None
// Output: Returns Creature Type of the Character
////////////////////////////////////////////
Creature Character::getCreatureType(void)
{
	return Type;
}

//////////////////////////////////////////
// Get Character's Move Speed
// Input: None
// Output: Returns the speed of the Character
//////////////////////////////////////
float Character::getMoveSpeed(void)
{
	return moveSpeed;
}

///////////////////////////////////
// Initialize Character
// Input: None
// Result: Set character up with the correct values
////////////////////////////////
void Character::init(void)
{
	while(!Data.FileEOF())
	{
		Text Line = Data.getLine();
		Text Start;
		Text End;

		//Data Files are setup like: Category:Value
		Line.splitAtDelimeter(&Start, &End, ':');

		if (End == Text(""))
			continue;

		if (Start == Text("HP"))
			maxHitPoints = hitPoints = atoi(End.getCString());
		else if (Start == Text("Speed"))
			moveSpeed = agk::ValFloat(End.getCString());
		else if (Start == Text("Attack"))
			attackAmount = atoi(End.getCString());
		else if (Start == Text("AttackSpeed"))
			attackSpeed = agk::ValFloat(End.getCString())/1.0f;
		else if (Start == Text("Cost"))
			cost = agk::Val(End.getCString());
		else if (Start == Text("IdleSpeed"))
			idleFrameSpeed = agk::ValFloat(End.getCString());
		else if (Start == Text("MoveSpeed"))
			moveFrameSpeed = agk::ValFloat(End.getCString());
		else if (Start == Text("AttackFrameSpeed"))
			attackFrameSpeed = agk::ValFloat(End.getCString());
		else if (Start == Text("DeathSpeed"))
			deathFrameSpeed = agk::ValFloat(End.getCString());
		else
		{
			//Setting up Animation Frame Values
			Text MinValue;
			Text MaxValue;
			unsigned int min, max;

			End.splitAtDelimeter(&MinValue, &MaxValue, ',');
			min = agk::Val(MinValue.getCString());
			max = agk::Val(MaxValue.getCString());

			
			if (Start == Text("Idle"))
			{
				idleFrameMin = min;
				idleFrameMax = max;
			}
			else if (Start == Text("Move"))
			{
				moveFrameMin = min;
				moveFrameMax = max;
			}
			else if (Start == Text("AttackFrames"))
			{
				attackFrameMin = min;
				attackFrameMax = max;
			}
			else if (Start == Text("Death"))
			{
				deathFrameMin = min;
				deathFrameMax = max;
			}
		}

	}

	Data.close();

	//Set the depth of attackers to be in front of defenders
	/*if (isDefender())
	{
		this->set(5000);
		OffsetAmount.setX(getWidth()/2.0f);
		OffsetAmount.setY(getHeight()/2.0f);
		//setOffset(OffsetAmount.getX(), OffsetAmount.getY());
	}
	else
	{
		setDepth(3000);
		OffsetAmount.setX(getWidth()/2.0f);
		OffsetAmount.setY(getHeight()/2.0f);
		//setOffset(OffsetAmount.getX(), OffsetAmount.getY());
	}*/

	timeFromLastAttack = 0.0f;
	//Set Character in Pose to start, wait for commands for update
	setState(MENU_TOOMUCH);
}

/////////////////////////////////////
// Is Character a Defender?
// Input: None
// Output: Returns true if Character is a Defender, false otherwise
///////////////////////////////////
bool Character::getIsDefender(void)
{
	switch(Type)
	{
	case INFORMATION_NODE:
		return true;
		break;
	case MINER_VIRUS:
		return false;
		break;
	case THIEF_VIRUS:
		return false;
		break;
	case DBLOCKER:
		return false;
		break;
	case BUG_VIRUS:
		return false;
		break;
	case SPAMMER:
		return false;
		break;
	case NORT:
		return true;
		break;
	}

	return false;
}

/////////////////////////////////////////
// Kill Character
// Input: Point to Character Who killed this Character
// Result: Set KilledBy to the Input, Set hitPoints to 0, and set the state to Death Animation
////////////////////////////////////////////
void Character::kill(Character *Killer)
{
	KilledBy = Killer;
	hitPoints = 0;
	setState(DEATH);
}

////////////////////////////////////////////
// Get Killedby
// Input: None
// Output: Pointer to the Character that killed this Character
//////////////////////////////////////////
Character *Character::getKilledBy(void)
{
	return KilledBy;
}

////////////////////////////////////////
// Repair Character
// Input: amount to heal
// Result: Character is healed by the amount
// Note: No Character does this yet, but I figured one may at some point
////////////////////////////////////////
void Character::repair(short amount)
{
	hitPoints += amount;
}

////////////////////////////////////////
// Override of SetVisible
// Input: whether Character should be visible or not
// Result: Character is moved off screen to be invisible and not collidable
/////////////////////////////////////////
void Character::setVisible(bool value)
{
	//If we're making the character visible, return the character to its position
	if (value)
		setY(oldY);
	//Otherwise, store where the character is supposed to be, and move him to offscreen in the y direction (x direction will get him removed)
	else
	{
		oldY = getY();
		setY(115.0f);
	}
	
	//Set the sprite to be visible/invisible
	Sprite::setVisible(value);
}

//////////////////////////////////////////////
// Get Character's Current Target
// Input: None
// Output: Pointer to the Character's Current Target when attacking
//////////////////////////////////////////////////
Character *Character::getCurrentTarget(void)
{
	return CurrentTarget;
}

////////////////////////////////////////////////////////////
// update Character
// Input: List of Defenders--Note if the Character IS a defender, this will be a list of attackers
// Result: Function checks for collision, moves the character, and determines whether the character should be attacking
///////////////////////////////////////////////////////////
void Character::update(std::vector<Character*> Defenders)
{
	if (isExample)
		return;

	if (getState() == FADEOUT)
	{
		short alpha = getColorAlpha() - 5;
				
		if (alpha >= 0)
			setColorAlpha(alpha);
		else
			setX(-15.0f);

		return;
	}

	for (unsigned int j = 0; j < Defenders.size(); j++)
	{
		//Check each of the Defenders, as long as they aren't already dead
		if (Defenders[j]->getState() != DEATH)
		{
			//This section is only for melee weapons
			if (!hasRangedWeapon)
			{
				if (collidedWith(Defenders[j]->getSpriteNumber()))
				{	//can't move, attacking	
					bool actualCollision = (getCollisionGroup() == Defenders[j]->getCollisionGroup());

					//special Thief section as it can collide with multiple groups
					if (!actualCollision && getCreatureType() == THIEF_VIRUS)
						actualCollision = true;

					//If this character is dead, don't worry about collisions, he has bigger issues to deal with
					if (getState() == DEATH)
						actualCollision = false;
					//Same thing for if the Defender is dead
					else if (Defenders[j]->getState() == DEATH)
						actualCollision = false;

					if (actualCollision)
					{
						//Collision distance is 2.0f, probably can be tweaked to get the actual collision
						if (getX() - Defenders[j]->getX() <= 2.0f)
						{
							setState(ATTACKING);
							attack(Defenders[j]);
						}
					}
				}
			}
			//Following section is for ranged attacks
			else
			{
				//Make sure they are in the same group
				if (getCollisionGroup() == Defenders[j]->getCollisionGroup())
				{
					//Make sure they are on the same row
					if (getY() == Defenders[j]->getY())
					{
						setState(ATTACKING);
						attack(Defenders[j]);
					}
				}
			}
			
			if (getState() != ATTACKING)
			{	//not attacking, move
				if (!getIsDefender())
				{
					if (getMoveSpeed() > 0.0f)
						//Dividing Move Speed by 1000 to make it easier for designers to tweak things
						setX(getX() - (getMoveSpeed()/1000.0f));
				}
				else
				{
					if (getMoveSpeed() > 0.0f)
						setX(getX() + getMoveSpeed()/1000.0f);
				}
			}
		}
	}
}

////////////////////////////////////////////
// Get Character State
// Input: None
// Output: The State the Character is in
////////////////////////////////////////////
CharacterState Character::getState(void)
{
	return CurrentState;
}

///////////////////////////////////////////
// Is Character Finished Dying?
// Input: None
// Output: Boolean true if current frame is equal to the deathFrameMax
/////////////////////////////////////////
bool Character::getIsFinishedDying(void)
{
	if (deathFrameMax == getCurrentFrame())
		return true;

	return false;
}

//////////////////////////////////////////////////
// Set Character State
// Input: Character State character should be in
// Result: Character's State variable is updated to this state
//         Animation is also changed to reflect the new state
///////////////////////////////////////////////////
void Character::setState(CharacterState State)
{
	float fps = 0.0f;
	bool loop = false;
	unsigned short min = 1;
	unsigned short max = 10000;

	if (CurrentState == State)
		return;

	CurrentState = State;

	switch (State)
	{
	case MENU_TOOMUCH:
		setFrame(1);
		setGroup((int) EXAMPLES);
		setColor(RGBA(255, 255, 255, 64));
		return;
		break;
	case MENU_AVAILABLE:
		setFrame(1);
		setColor(RGBA(255, 255, 255, 192));
		setGroup((int) EXAMPLES);
		return;
		break;
	case SELECTED:
		setFrame(1);
		setColorAlpha(128);
		setGroup((int) GHOSTS);
		return;
		break;
	case IDLE:
		setColorAlpha(255);
		fps = idleFrameSpeed;
		loop = true;
		min = idleFrameMin;
		max = this->idleFrameMax;
		//As long as the attacker is not a MINER_VIRUS, set its group to MORTALS
		if (getCreatureType() != MINER_VIRUS)
			setCollisionGroup((int)(MORTALS));
		else
			setCollisionGroup((int) GODS);
		break;
	case MOVING:
		fps = moveFrameSpeed;
		loop = true;
		min = moveFrameMin;
		max = moveFrameMax;
		break;
	case ATTACKING:
		fps = attackFrameSpeed;
		loop = true;
		min = attackFrameMin;
		max = moveFrameMax;
		break;
	case DEATH:
		fps = deathFrameSpeed;
		loop = false;
		min = deathFrameMin;
		max = deathFrameMax;
		break;
	case FADEOUT:
		break;
		return;
	}

	play(fps, loop, min, max);
}

////////////////////////////////////////////
// Get Character Cost
// Input: None
// Output: Returns Cost to build character
///////////////////////////////////////////////
unsigned short Character::getCost(void)
{
	return cost;
}

/////////////////////////////////////////////
// Alpha Out
// Input None
// Output: Makes character semi-transparent
void Character::setAlphaOut(bool alphaOut, CollisionGroup Group)
{
	if (alphaOut)
	{
		setColorAlpha(128);
		setCollisionGroup((int) Group);
	}
	else
	{
		setColorAlpha(255);
		setCollisionGroup((int) Group);
	}
}