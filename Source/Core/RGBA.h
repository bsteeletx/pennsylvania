#pragma once

class RGBA
{
public:
	RGBA(void);
	RGBA(unsigned short redValue, unsigned short greenValue, unsigned short blueValue, unsigned short alphaValue = 255);
	~RGBA(void);

	unsigned short getAlpha(void);
	unsigned short getBlue(void);
	unsigned short getGreen(void);
	unsigned short getRed(void);
		
	void setAlpha(unsigned short value);
	void setBlue(unsigned short value);
	void setGreen(unsigned short value);
	void setRed(unsigned short value);

private:
	unsigned short alpha;
	unsigned short blue;
	unsigned short green;
	unsigned short red;

	bool _Color(unsigned short value);
};
