//
//  Color.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/Color.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

Color::Color() : mRed(0), mGreen(0), mBlue(0), mAlpha(255)
{
}

Color::Color(int theColor, int theAlpha)
{
	mRed = (theColor >> 16) & 0xFF;
	mGreen = (theColor >> 8) & 0xFF;
	mBlue = theColor & 0xFF;
	mAlpha = theAlpha;
}

Color::Color(int theRed, int theGreen, int theBlue) : mRed(theRed), mGreen(theGreen), mBlue(theBlue), mAlpha(255)
{
}

Color::Color(const SexyRGBA& theColor) : mRed(theColor.r), mGreen(theColor.g), mBlue(theColor.b), mAlpha(theColor.a)
{
}

Color::Color(const uchar* theElements) : mRed(theElements[0]), mGreen(theElements[1]), mBlue(theElements[2]), mAlpha(255)
{
}

Color::Color(const int* theElements) : mRed(theElements[0]), mGreen(theElements[1]), mBlue(theElements[2]), mAlpha(255)
{
}

/////////////// Accessors ///////////////

int Color::GetRed() const
{
	return mRed;
}

int Color::GetGreen() const
{
	return mGreen;
}

int Color::GetBlue() const
{
	return mBlue;
}

int Color::GetAlpha() const
{
	return mAlpha;
}

uint32 Color::ToInt() const
{
	return (mAlpha << 24) | (mRed << 16) | (mGreen << 8) | mBlue;
}

SexyRGBA Color::ToRGBA() const
{
	SexyRGBA aColor;
	aColor.r = mRed;
	aColor.g = mGreen;
	aColor.b = mBlue;
	aColor.a = mAlpha;
	return aColor;
}

bool Color::IsInvalid() const
{
	return *this == Color(Invalid);
}

Color Color::FromInt(ulong theColor)
{
	return Color((theColor >> 16) & 0xFF, (theColor >> 8) & 0xFF, theColor & 0xFF, (theColor >> 24) & 0xFF);
}
