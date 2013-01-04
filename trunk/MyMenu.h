#pragma once

#include "AnimatedSprite.h"
#include "ParentImage.h"

class MyMenu
{
public:
	MyMenu(void);
	~MyMenu(void);

	bool ButtonAnimation(short int stage, short int button);
	void hide(void);
	void update(void);
	void setPriority(short unsigned int value);
	void setup(AnimatedSprite *Symbol);
	void muteSound(void);
	void unMuteSound(void);
	
	ParentImage MenuParent;

private:

	//Sprite Background;
};

