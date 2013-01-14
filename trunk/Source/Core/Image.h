#pragma once

#include "Point.h"
#include "Text.h"
#include "File.h"
#include <vector>

class Text;
class File;

class Image
{
public:
	//constructors/deconstructors
	~Image(void);
	Image(void);
	Image (unsigned int assignedImageNumber, Text Filename);
	Image (unsigned int copyImageNumber);
	Image (Point Begin, Point End);
	Image (Text EncodedText);
	Image (Text Filename, bool blackIsAlpha = false); 
	Image (unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha = false);
	Image (Text SubImageFilename, unsigned int parentImage);
	Image (unsigned int assignedImageumber, unsigned int parentImage, Text SubImageFilename);
	Image (File FileToInit, Text PathToParent);
	
	//operators
	Image& operator= (const Image& newImage);
	//Image& operator<< (const Text& Filename);

	//methods
	//unsigned int copySection(Point Begin, Point End); 

	Text decodeQRCode(void);

	bool getExists(void);
	Text getFilename(void);
	float getHeight(void);
	unsigned int getImageNumber(void);
	float getWidth(void);

	void printImage(float percentSize); //yes, no negative

	void saveImage(Text savedFilename); //yes, make sure it's a jpg or png
	void setImageMagFilter(bool linear);
	void setAsImageMask(unsigned int imageToMask, short colorDest, short colorSrc, int offsetXDest, int offsetYDest); 
	//yes 
	void setImageMinFilter(bool linear);
	void setImageWrapU(bool repeat);
	void setImageWrapV(bool repeat);
	void setAsQRCode(void);

private:
	void loadImage(Text Filename, bool blackIsAlpha = false);
	void loadImage(unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha = false);
	void loadSubImage(unsigned int parentImage, Text SubImageFilename);
	void loadSubImage(unsigned int assignedImageNumber, unsigned int parentImage, Text subImageFilename);

	bool _Filename(Text filename);
	bool _ImageNumber(unsigned int number);
	//bool _ParentNumber(unsigned int number);
	static std::vector<Text> ParentImages;
	static std::vector<Text> NonParentFileNames;
	static std::vector<unsigned int> parentImageNumbers;
	static std::vector<unsigned int> nonParentImageNumbers;

protected:
	bool _ColorChannel(short value);
	unsigned int imageNumber;
};