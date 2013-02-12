#pragma once
#include "AnimatedSprite.h"

class Fog
{
public:
	Fog(void);
	~Fog(void);

	bool getVisible(Point Location);

	unsigned short getLastVisibleColumn(void);

	void initFog(void);
	bool isFogGone(void);
	
	void removeFog(Point Location);
	
	void update(void);

private:
	AnimatedSprite FogBank[8][5];
	Sprite FogSprite;
	bool fogIsGone;
};

