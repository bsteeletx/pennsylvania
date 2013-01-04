#pragma once

#include "Text.h"

class Sound
{
public:
	Sound();
	~Sound(void);
	Sound(unsigned int assignedNumber, Text Filename);
	Sound(Text Filename);

	bool getExists(void);
	unsigned int getInstances(void);

	void play(unsigned short volume = 100, bool loop = false);
	
	void setSystemVolume(unsigned short volume);
	void stop(void);
	
	
private:
	unsigned int soundID;

	bool _Filename(Text Filename);
};
