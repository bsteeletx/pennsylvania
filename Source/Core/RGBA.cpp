#include "RGBA.h"

RGBA::RGBA(void)
{
	alpha = 0;
	blue = 0;
	green = 0;
	red = 0;
}

RGBA::RGBA(unsigned short redValue, unsigned short greenValue, unsigned short blueValue, unsigned short alphaValue)
{
	if (_Color(redValue))
	{
		if (_Color(greenValue))
		{
			if (_Color(blueValue))
			{
				if (_Color(alphaValue))
				{
					alpha = alphaValue;
					blue = blueValue;
					green = greenValue;
					red = redValue;
				}
			}
		}
	}
}

RGBA::~RGBA(void)
{
}

unsigned short RGBA::getAlpha(void)
{
	return alpha;
}

unsigned short RGBA::getBlue(void)
{
	return blue;
}

unsigned short RGBA::getGreen(void)
{
	return green;
}

unsigned short RGBA::getRed(void)
{
	return red;
}

void RGBA::setAlpha(unsigned short value)
{
	if (_Color(value))
		alpha = value;
}

void RGBA::setBlue(unsigned short value)
{
	if (_Color(value))
		blue = value;
}

void RGBA::setGreen(unsigned short value)
{
	if (_Color(value))
		green = value;
}

void RGBA::setRed(unsigned short value)
{
	if (_Color(value))
		red = value;
}

bool RGBA::_Color(unsigned short value)
{
	if (value > 255)
		return false;

	return true;
}
