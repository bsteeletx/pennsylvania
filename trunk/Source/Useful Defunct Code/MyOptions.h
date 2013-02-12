#pragma once

#include "MyMenu.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "ParentImage.h"

const short int MAX_THEMES = 6;

class MyOptions :
	public MyMenu
{
public:
	MyOptions(void);
	~MyOptions(void);

	bool arrowAnimation(short stage, short button);
	void show(short int curStyle);
	void mute(void);
	void unMute(void);
	void setPriority(short unsigned int value);
	void setup(AnimatedSprite *Symbol);
	void update(void);
	//void hide(void);

	Sprite Background;
	Sprite ThemeOption[MAX_THEMES];

private:
	bool isMuted;
    
    ParentImage Parent;
};

