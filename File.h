#pragma once
#include "Text.h"
#include <string>

class Text;

class File
{
public:
	File();
	~File(void);
	File(bool read, Text Filename);

	File &operator= (const File &NewFile);

	void close(void);
	
	bool FileEOF(void);

	float getFloat(void);
	int getID(void);
	int getInt(void);
	Text getLine(void);
	unsigned int getSize(void);	
	Text getString(void);
	
	void putFloat(float value);
	void putInt(int value);
	void putLine(Text Value);
	void putString(Text Value);

	void reOpen(void);

private:
	unsigned int fileID;
	bool openToRead;
	std::string nameOfFile;

	bool getExists(Text Filename);
	bool isOpen(void);
	void open(bool read, Text Filename);
};
