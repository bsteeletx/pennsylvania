//////////////////////////////////////////////////////////////////////
/* Timer class because everything I've seen about the Timers in AGK suck
/  by Steele Game Studios
*///////////////////////////////////////////////////////////////////

#pragma once
#include <time.h>

class Timer
{
public:
	Timer(void);
	~Timer(void);

	void reset(void);
	void resetStopWatch(void);
	unsigned int getElapsed(void);
	bool getRinging(void);
	void stopWatch(unsigned int stopValue);
	void updateTime(void);

private:
	time_t startTime;
	unsigned int stopTime;
	unsigned int stopAmount;
	bool ringing;
};

