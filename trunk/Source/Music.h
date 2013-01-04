#pragma once

#include "Text.h"

class Music
{
public:
	Music();
	~Music();
	Music(unsigned short assignedID, Text Filename);
	Music(Text Filename);

	bool getExists(void);
	bool getPlaying(void);

	void pause(void);
	void play(void);
	
	void resume(void);

	void setFileVolume(unsigned short volume);
	void setSystemVolume(unsigned short volume);
	void stop(void);

private:
	unsigned short musicNumber;

	bool _Filename(Text Filename);
};