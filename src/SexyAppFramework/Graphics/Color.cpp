//
//  Color.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/Color.h"

#include <limits>

using namespace Sexy;

/////////////// Lifecycle ///////////////

Color::Color() : mRed(0), mGreen(0), mBlue(0), mAlpha(255)
{
}

Color::Color(const Color& theColor) : mRed(theColor.mRed), mGreen(theColor.mGreen), mBlue(theColor.mBlue), mAlpha(theColor.mAlpha)
{
}

Color::Color(int theColor) : mRed((theColor >> 16) & 0xFF), mGreen((theColor >> 8) & 0xFF), mBlue(theColor & 0xFF), mAlpha((theColor >> 24) & 0xFF)
{
	if (mAlpha == 0)
		mAlpha = 0xFF;
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

Color::Color(int theRed, int theGreen, int theBlue, int theAlpha) : mRed(theRed), mGreen(theGreen), mBlue(theBlue), mAlpha(theAlpha)
{
}

Color::Color(const PredefinedColor c)
{
	mAlpha = 255;
	switch (c)
	{
	case Invalid:
	{
		int aMax = std::numeric_limits<int>::max();
		mRed = aMax;
		mGreen = aMax;
		mBlue = aMax;
	}
		break;
	case Black:
		mRed = 0;
		mGreen = 0;
		mBlue = 0;
		break;
	case White:
		mRed = 255;
		mGreen = 255;
		mBlue = 255;
		break;
	case Red:
		mRed = 255;
		mGreen = 0;
		mBlue = 0;
		break;
	case Orange:
		mRed = 255;
		mGreen = 173;
		mBlue = 0;
		break;
	case Yellow:
		mRed = 255;
		mGreen = 255;
		mBlue = 0;
		break;
	case Green:
		mRed = 0;
		mGreen = 255;
		mBlue = 0;
		break;
	case Blue:
		mRed = 0;
		mGreen = 0;
		mBlue = 255;
		break;
	case Purple:
		mRed = 160;
		mGreen = 32;
		mBlue = 240;
		break;
	case Cyan:
		mRed = 0;
		mGreen = 255;
		mBlue = 255;
		break;
	}
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

Color Color::FAlpha(float theAlpha)
{
	return Color(255, 255, 255, (int)(theAlpha * 255));
}

int& Color::operator[](int theIdx)
{
	static int aJunk = 0;

	switch (theIdx)
	{
	case 0:
		return mRed;
	case 1:
		return mGreen;
	case 2:
		return mBlue;
	case 3:
		return mAlpha;
	default:
		return aJunk;
	}
}

int Color::operator[](int theIdx) const
{
	switch (theIdx)
	{
	case 0:
		return mRed;
	case 1:
		return mGreen;
	case 2:
		return mBlue;
	case 3:
		return mAlpha;
	default:
		return 0;
	}
}

/////////////// Operators ///////////////

Color Color::operator*(const Color& theColor) const
{
	return Color(mRed * theColor.mRed / 255, mGreen * theColor.mGreen / 255, mBlue * theColor.mBlue / 255, mAlpha * theColor.mAlpha / 255);
}
