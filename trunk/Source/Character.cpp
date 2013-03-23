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
	oldY = 0.0f;
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
	didDamage = false;
	//setCollisionGroup((int)EXAMPLES);
	hasRangedWeapon = false;
	CurrentTarget = NULL;
	isExample = false;
	oldY = 0.0f;
	costIncrease = 0;
	costFactor = 0;
	costPower = 0;
	healthDrainAmount = 0;
	healthDrainRate = 0;
	shield = shieldMax = 0;

	init();
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
void Character::attack(float currentTime, Character *Target)
{
	if (timeFromLastAttack == 0)
	{
		timeFromLastAttack = currentTime + attackSpeed;
		return;
	}

	if (currentTime - timeFromLastAttack > attackSpeed)
	{
		if (this->hasRangedWeapon)
		{
			fireWeapon();
			CurrentTarget = Target;
			timeFromLastAttack = currentTime;
			return;
		}

		Target->damage(attackAmount, this);

		timeFromLastAttack = currentTime;
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
void Character::minerAttack(float currentTime)
{
	if (currentTime - timeFromLastAttack > attackSpeed)
	{
		if (getCreatureType() == MINER_VIRUS)
		{
			timeFromLastAttack = currentTime;
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
void Character::damage(short amount, Character *Attacker)
{
	if (shield != 0)
	{
		if (amount <= shield)
			shield -= amount;
		else
		{
			hitPoints -= (amount - shield);
			shield = 0;
		}
	}
	else
		hitPoints -= amount;

	if (hitPoints <= 0)
		kill(Attacker);
}

void Character::destroy(void)
{
	setX(200.0f);
	setY(200.0f);
	setState(FADEOUT);
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

void Character::fireWeapon(void)
{
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

//////////////////////////////////////////////
// Get Menu Size
// Input: None
// Output: returns menu size
////////////////////////////////////////
unsigned short Character::getMenuSize(void)
{
	return menuSize;
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
		{
			int needleLocPlus = End.foundNeedle('+');
			int needleLocX = End.foundNeedle('x');
			int needleLocPower = End.foundNeedle('^');

			if (needleLocPlus != -1)
				costIncrease = agk::Val(End.mid(needleLocPlus + 2, 1).getCString(), 10);
			
			if (needleLocX != -1)
				costFactor = agk::Val(End.mid(needleLocX + 2, 1).getCString(), 10);
			
			if (needleLocPower != -1)
				costPower = agk::Val(End.mid(needleLocPower + 2, 1).getCString(), 10);

			if (needleLocPlus != -1)
				End.splitAtDelimeter(&End, &Text(), '+');
			else if (needleLocX != -1)
				End.splitAtDelimeter(&End, &Text(), 'x');
			else if (needleLocPower != -1)
				End.splitAtDelimeter(&End, &Text(), '^');
			
			costCurrent = cost = agk::Val(End.getCString());
		}
		else if (Start == Text("IdleSpeed"))
			idleFrameSpeed = agk::ValFloat(End.getCString());
		else if (Start == Text("MoveSpeed"))
			moveFrameSpeed = agk::ValFloat(End.getCString());
		else if (Start == Text("AttackFramesSpeed"))
			attackFrameSpeed = agk::ValFloat(End.getCString());
		else if (Start == Text("DeathSpeed"))
			deathFrameSpeed = agk::ValFloat(End.getCString());
		else if (Start == Text("HealthDrainAmount"))
			healthDrainAmount = agk::Val(End.getCString());
		else if (Start == Text("HealthDrainRate"))
			healthDrainRate = agk::ValFloat(End.getCString());
		else if (Start == Text("Shield"))
			shieldMax = shield = agk::Val(End.getCString());
		else if (Start == Text("MenuSize"))
			menuSize = agk::Val(End.getCString());
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

	if ((getState() != DEATH) && (getState() != FADEOUT))
		setState(DEATH);

	//MinerVirus kills itself, and Thief kills itself
	if (Killer != this) 
	{
		if (Killer->Type != THIEF_VIRUS)
			Killer->setState(MOVING);
	}

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
	else if (!value && (oldY == 0.0f))
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
void Character::update(float currentTime, std::vector<Character*> Defenders)
{
	if (isExample)
		return;

	if (getCreatureType() == MINER_VIRUS)
		attack(currentTime, NULL);

	if (CurrentState == FADEOUT)
	{
		short alpha = getColorAlpha() - 5;
				
		if (alpha >= 0)
			setColorAlpha(alpha);
		else
			setX(-15.0f);

		return;
	}
	else if (CurrentState == DEATH)
		return;

	for (unsigned int j = 0; j < Defenders.size(); j++)
	{
		//check to make sure we're looking at the same aisle
		if (Defenders[j]->getPosition().getGridCoords().getY() != getPosition().getGridCoords().getY())
			continue;

		//Check each of the Defenders, as long as they aren't already dead
		if (Defenders[j]->getState() != DEATH)
		{
			//This section is only for melee weapons
			if (!hasRangedWeapon)
			{
				if (collidedWith(Defenders[j]->getSpriteNumber()))
				{	//can't move, attacking	
					
					//check to see if they are in the same collision group
					bool actualCollision = (getCollisionGroup() == Defenders[j]->getCollisionGroup());

					if (getY() == Defenders[j]->getY())
					{

						//special Thief section as it can collide with multiple groups
						if (!actualCollision && getCreatureType() == THIEF_VIRUS)
							actualCollision = true;

						//If this character is dead, don't worry about collisions, he has bigger issues to deal with
						if (getState() == DEATH)
							actualCollision = false;
						//Same thing for if the Defender is dead
						else if (Defenders[j]->getState() == DEATH)
							actualCollision = false;
					}
					else
						actualCollision = false;

					if (actualCollision)
					{
						//Collision distance is 2.0f, probably can be tweaked to get the actual collision
						if (getX() - Defenders[j]->getX() <= 2.0f)
						{
							setState(ATTACKING);
							attack(currentTime, Defenders[j]);
						}
					}
				}
				else
				{//no longer colliding
					if (getState() == ATTACKING)
					{
						if (getCurrentFrame() == attackFrameMax)
							setState(MOVING);
					}
				}
			}
			//Following section is for ranged attacks
			else
			{
				//Make sure they are in the same group
				if (getCollisionGroup() == Defenders[j]->getCollisionGroup())
				{
					setState(ATTACKING);
					attack(currentTime, Defenders[j]);
				}
			}
		}
	}

	if (getState() != ATTACKING)
	{//not attacking, move
		//Dividing Move Speed by 1000 to make it easier for designers to tweak things
		if (getMoveSpeed() > 0.0f)
		{
			if (!this->getIsDefender())
				moveX(-getMoveSpeed()/100.0f);
			else
			{
				if (getPosition().getGridCoords().getX() < 5.0f)
					moveX(getMoveSpeed()/100.0f);
			}
		}
	}
}

////////////////////////////////////////////
// Update Cost
// Input Number of creatures
// Result Change cost value
////////////////////////////////////////
void Character::updateCost(unsigned short creatureCount)
{
	unsigned short factor = 0;
	float power = 0;

	if (creatureCount == 0)
		return;

	if (costFactor != 0)
		factor = (creatureCount*costFactor*cost);
	else
		factor = 1;
	
	if (costPower != 0)
		power = factor*(std::pow((float) costPower, (float) creatureCount));
	else if (factor != 1)
		power = factor;
	else
		power = 0;

	if (costIncrease != 0)
		costCurrent =  (unsigned short) (power + (creatureCount*costIncrease));
	else if (power != 0)
		costCurrent = (unsigned short) (power * cost);
	else
		costCurrent = cost;
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

	/*if (CurrentState == DEATH)
	{
		if (State < CurrentState)
			return;
	}*/


	CurrentState = State;

	switch (State)
	{
	case MENU_TOOMUCH:
		setFrame(1);
		setGroup((int) EXAMPLES);
		setColor(RGBA(255, 255, 255, 64));
		fps = 1;
		loop = false;
		min = 1;
		max = 1;
		break;
	case MENU_AVAILABLE:
		setFrame(1);
		setColor(RGBA(255, 255, 255, 192));
		setGroup((int) EXAMPLES);
		fps = 1;
		loop = false;
		min = 1;
		max = 1;
		break;
	case MENU_HIDDEN:
		setFrame(1);
		setColor(RGBA(0, 0, 0, 64));
		setGroup((int) EXAMPLES);
		fps = 1;
		loop = false;
		min = 1;
		max = 1;
		break;
	case SELECTED:
		setFrame(1);
		setColorAlpha(128);
		setGroup((int) GHOSTS);
		return;
		break;
	case IDLE:
		setColor(RGBA(255, 255, 255, 255));
		fps = idleFrameSpeed;
		loop = true;
		min = idleFrameMin;
		max = this->idleFrameMax;
		//As long as the attacker is not a MINER_VIRUS, set its group to MORTALS
		if ((Type != MINER_VIRUS) && (Type != INFORMATION_NODE))
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
		max = attackFrameMax;
		break;
	case DEATH:
		fps = deathFrameSpeed;
		loop = false;
		min = deathFrameMin;
		max = deathFrameMax;
		setCollisionGroup((int) GODS);
		break;
	case FADEOUT:
		setCollisionGroup((int) GODS);
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
	return costCurrent;
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
