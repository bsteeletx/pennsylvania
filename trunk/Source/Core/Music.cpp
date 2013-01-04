#include "Music.h"
#include "agk.h"

Music::Music(void)
{
	musicNumber = 0;
}

Music::~Music(void)
{
	//if(getExists())
	//	agk::DeleteMusic(musicNumber);
}

Music::Music(unsigned short assignedID, Text Filename)
{
	if (_Filename(Filename))
	{
		if (assignedID <= 50)
		{
			agk::LoadMusic(assignedID, Filename.getString());
			musicNumber = assignedID;
		}
	}
}

Music::Music(Text Filename)
{
	if (_Filename(Filename))
		musicNumber = agk::LoadMusic(Filename.getString());
}

bool Music::getExists(void)
{
	if (agk::GetMusicExists(musicNumber) == 1)
		return true;

	return false;
}

bool Music::getPlaying(void)
{
	if (agk::GetMusicPlaying() == musicNumber)
		return true;

	return false;
}

void Music::pause(void)
{
	agk::PauseMusic();
}

void Music::play(void)
{
	agk::PlayMusic(musicNumber);
}

void Music::resume(void)
{
	agk::ResumeMusic();
}

void Music::setFileVolume(unsigned short volume)
{
	if (volume <= 100)
		agk::SetMusicFileVolume(musicNumber, volume);
}

void Music::setSystemVolume(unsigned short volume)
{
	if (volume <= 100)
		agk::SetMusicSystemVolume(volume);
}

void Music::stop(void)
{
	agk::StopMusic();
}

bool Music::_Filename(Text Filename)
{
	char tempFilename[4];
	short lengthOfString = Filename.getLength() - 1;

	for (int i = 3; i > 0; i--)
		tempFilename[i] = Filename.getChar(lengthOfString - 1);
		
	if (strcmp(tempFilename, ".wav") == 0) //equal
		return true;
	if (strcmp(tempFilename, ".mp3") == 0) //equal
		return true;

	return false;
}