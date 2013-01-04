//////////////////////////
// Timer is our default Timer class as the other timers seem not to work
///////////////////////////

#include "Timer.h"
#include "agk.h"

//////////////////////////////
//Timer Constructor
//Inputs: None
//Returns: Nothing
//
//Sets startTime to current time,
//Sets stopTime to a valid, zero value
//Sets ringing to false
////////////////////////////////
Timer::Timer(void)
{
	//Adding this comment to test out git
	startTime = time(NULL);
	stopTime = 0;
	ringing = false;
}

/////////////////////////////
//Timer Destructor
//Inputs: None
//Returns: Nothing
//
//Does nothing as it has been recommended to do nothing
///////////////////////////////
Timer::~Timer(void)
{
}

/////////////////////////////////////
//Get Elapsed Timer 
//Inputs: None
//Returns: Elapsed Time from when Timer was start
//
//////////////////////////////////////
unsigned int Timer::getElapsed(void)
{
	//get the current time and assign it to time_t variable currentTime
	time_t currentTime = time(NULL);

	//return the currentTime variable
	return currentTime - startTime;
}

////////////////////////////////////
//Get Ringing
//Inputs: None
//Returns: Bool Value on whether the stopWatch has started ringing
//
//////////////////////////////////////
bool Timer::getRinging(void)
{
	//check to see if it is ringing, if so, return true
	if (ringing)
		return ringing;
	
	//else get the current time and assign it to time_t currentTime
	time_t currentTime = time(NULL);

	//DEBUG TAKE OUT!!!!
	AGK::agk::Print((int)currentTime);
	AGK::agk::Print((int)stopTime);
	
	//check one more time to see if it should be ringing, if so, return true
	if (currentTime >= stopTime)
		return true;

	//still not ready, return false
	return false;
}

/////////////////////////////////
//Reset
//Inputs: None
//Outputs: None
//
//Resets Start Time to Current Time
////////////////////////////////
void Timer::reset(void)
{
	//set start time to current time
	startTime = time(NULL);
}

///////////////////////////////////
//Reset Stop Watch
//Inputs: None
//Outputs: None
//
//Reset the stop watch to use again, using the same time interval
///////////////////////////////////
void Timer::resetStopWatch(void)
{
	//set time_t currentTime to the current time
	time_t currentTime = time(NULL);
	
	//set the stop time to be the current time + the time interval
	stopTime = stopAmount + currentTime;
}

///////////////////////////////////
//Stop Watch
//Inputs: unsigned int interval
//Outputs: None
//
//Initializes the stop watch (or alarm clock) to start ringing after interval milliseconds
////////////////////////////////////////////////
void Timer::stopWatch(unsigned int stopValue)
{
	//set the interval value to the passed in stopValue
	stopAmount = stopValue;

	//set the ring time to the current time + the interval time
	stopTime = stopAmount + startTime;
}

//////////////////////////////
//Update Time
//Inputs: None
//Outputs: None
//
//Checks to see if the stopWatch (alarm clock) should be ringing, sets ringing to true if needed
//////////////////////////////
void Timer::updateTime(void)
{
	//get the current time, set it to time_t currentTime
	time_t currentTime = time(NULL);

	//if stopTime is equal to zero, then ignore this as we are not using the stop watch (alarm clock)
	//if stopTime does not equal zero, then we are checking the stop time vs. the ring time
	if (stopTime != 0)
	{
		//if the currentTime has surpassed the stopTime, set ringing to true
		if (currentTime >= stopTime)
			ringing = true;
	}
}