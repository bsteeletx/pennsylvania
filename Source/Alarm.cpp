#include "Alarm.h"
#include "Text.h"
#include "RGBA.h"

Alarm::Alarm(void)
{
	isOn = false;
	isFinished = false;
}


Alarm::~Alarm(void)
{
}

Alarm::Alarm(unsigned short alarmTime)
{
	VisualAlert = Sprite(RGBA(255, 0, 0, 128));
	AudioAlert = Sound(Text("Assets/Sounds/gqold.wav"));
	VisualAlert.setSize(100.0f);
	VisualAlert.setVisible(false);
	VisualAlert.setDepth(1);
	lengthOfTime = alarmTime;
	isOn = false;
	isFinished = false;
}

void Alarm::activate(void)
{
	StopWatch = Timer();
	StopWatch.stopWatch(lengthOfTime);
	AudioAlert.play(100, true);
	isOn = true;
	count = 0;
}

bool Alarm::getActivated(void)
{
	return isOn;
}

bool Alarm::getFinished(void)
{
	return isFinished;
}

void Alarm::toggleVisual(void)
{
	if (VisualAlert.getVisible())
		VisualAlert.setVisible(false);
	else
		VisualAlert.setVisible(true);
}

void Alarm::update(void)
{
	if (count++ % 25 == 0)
		toggleVisual();

	if (StopWatch.getRinging())
	{
		VisualAlert.setVisible(false);
		AudioAlert.stop();
		isOn = false;
		isFinished = true;
	}
}