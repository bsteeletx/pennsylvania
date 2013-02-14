#pragma once

#include "Sound.h"
#include "Sprite.h"
#include "Timer.h"

class Alarm
{
public:
	Alarm(void);
	~Alarm(void);
	Alarm(unsigned short alarmTime);

	void activate(void);

	bool getActivated(void);
	bool getFinished(void);

	//probably could use a reset

	void toggleVisual(void);

	void update(void);

private:
	Sound AudioAlert;
	Sprite VisualAlert;
	Timer StopWatch;
	
	bool isOn;
	bool isFinished;

	unsigned short count;

	unsigned short lengthOfTime;
};

