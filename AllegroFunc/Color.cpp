#include "Color.h"

Color::Color(unsigned r, unsigned g, unsigned b, unsigned a)
{
	mRed = r;
	mGreen = g;
	mBlue = b;
	mAlpha = a;

	mColor = al_premul_rgba(mRed, mGreen, mBlue, mAlpha);
}

Color::Color(unsigned r, unsigned g, unsigned b)
{
	mRed = r;
	mGreen = g;
	mBlue = b;
	mAlpha = 255;

	mColor = al_premul_rgba(mRed, mGreen, mBlue, mAlpha);
}


Color::~Color()
{
	//Destroys object
}