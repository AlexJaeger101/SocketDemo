#pragma once
#include <allegro5/color.h>

class Color
{
public:
	
	//Constructors
	Color(unsigned r, unsigned g, unsigned b, unsigned a);
	Color(unsigned r, unsigned g, unsigned b);

	//Destructor
	~Color();

	//Accessors
	unsigned getRedChannel() { return mRed; };
	unsigned getBlueChannel() { return mBlue; };
	unsigned getGreenChannel() { return mGreen; };
	unsigned getAlphaChannel() { return mAlpha; };
	ALLEGRO_COLOR getAllegroColor() { return mColor; };

private:

	//Color Channels
	unsigned mRed;
	unsigned mBlue;
	unsigned mGreen;
	unsigned mAlpha;

	//Allegro Color
	ALLEGRO_COLOR mColor;
};