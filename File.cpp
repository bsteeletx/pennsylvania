#include "File.h"
#include "agk.h"

File::File()
{
	fileID = 0;
	openToRead = true;
}

File::~File()
{
}

File::File(bool read, Text Filename)
{
	if (getExists(Filename) == 1)
	{
		open(read, Filename);
		nameOfFile = Filename.getString();
	}
}

File& File::operator= (const File &NewFile)
{
	File ReturnFile(NewFile);
	
	if (this != &NewFile)
	{
		if (fileID)
			close();
		
		this->fileID = NewFile.fileID;
		this->openToRead = NewFile.openToRead;
		this->nameOfFile = NewFile.nameOfFile;
	}

	return *this;
}

bool File::FileEOF(void)
{
	if (openToRead)
	{
		if (agk::FileEOF(fileID))
			return true;
		
		return false;
	}
	
	return false; //will always return false as you can always add to the file
}

float File::getFloat(void)
{
	if (openToRead)
		return agk::ReadFloat(fileID);

	return 0.0f;
}

int File::getID(void)
{
	return fileID;
}

int File::getInt(void)
{
	if (openToRead)
		return agk::ReadInteger(fileID);

	return 0;
}

Text File::getLine(void)
{
	if (openToRead)
	{
		Text Line(agk::ReadLine(fileID));
		return Line;
	}

	return Text();
}

unsigned int File::getSize(void)
{
	if (openToRead)
		return agk::GetFileSize(fileID);

	return 0;
}

Text File::getString(void)
{
	if (openToRead)
		return Text(agk::ReadString(fileID));

	return Text();
}

void File::putFloat(float value)
{
	if (!openToRead)
		agk::WriteFloat(fileID, value);
}

void File::putInt(int value)
{
	if (!openToRead)
		agk::WriteInteger(fileID, value);
}

void File::putLine(Text Value)
{
	if (!openToRead)
		agk::WriteLine(fileID, Value.getString());
}

void File::putString(Text Value)
{
	if (!openToRead)
		agk::WriteString(fileID, Value.getString());
}

void File::reOpen(void)
{
	open(openToRead, Text(nameOfFile));
}

void File::close(void)
{
	agk::CloseFile(fileID);
}

bool File::getExists(Text Filename)
{
	if (agk::GetFileExists(Filename.getString()) == 1 )
		return true;

	return false;
}

bool File::isOpen(void)
{
	if (agk::FileIsOpen(fileID) == 1)
		return true;

	return false;
}

void File::open(bool read, Text Filename)
{
	if (read)
		fileID = agk::OpenToRead(Filename.getString());
	else
		fileID = agk::OpenToWrite(Filename.getString());

	openToRead = read;
}