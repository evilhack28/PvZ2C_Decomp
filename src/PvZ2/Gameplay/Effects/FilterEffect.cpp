//
//  FilterEffect.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "TodLib/FilterEffect.h"
#include "TodLib/TodCommon.h"
#include "SexyAppFramework/MemoryImage.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"

#include <map>
#include <algorithm>

typedef std::map<Sexy::Image*, Sexy::Image*> FilterMap;

FilterMap gFilterMap[NUM_FILTER_EFFECTS];

/////////////// FilterEffect ///////////////

void HSL_to_RGB(float h, float s, float l, float* r, float* g, float* b)
{
	float v;
	if (l > 0.5f)
		v = l + s - l * s;
	else
		v = l * (1.0f + s);

	if (v <= 0.0f)
	{
		*r = 0.0f;
		*g = 0.0f;
		*b = 0.0f;
		return;
	}

	float m = l * 2.0f - v;
	float aHue = h * 6.0f;
	int aSextant = ClampInt((int)aHue, 0, 5);
	float aFract = aHue - aSextant;
	float aVsf = ((v - m) / v) * v * aFract;
	float aMid1 = m + aVsf;
	float aMid2 = v - aVsf;
	switch (aSextant)
	{
	case 0:
		*r = v;
		*g = aMid1;
		*b = m;
		break;
	case 1:
		*r = aMid2;
		*g = v;
		*b = m;
		break;
	case 2:
		*r = m;
		*g = v;
		*b = aMid1;
		break;
	case 3:
		*r = m;
		*g = aMid2;
		*b = v;
		break;
	case 4:
		*r = aMid1;
		*g = m;
		*b = v;
		break;
	case 5:
		*r = v;
		*g = m;
		*b = aMid2;
		break;
	}
}

void RGB_to_HSL(float r, float g, float b, float* h, float* s, float* l)
{
	float aMax = std::max(r, g);
	aMax = std::max(aMax, b);
	float aMin = std::min(r, g);
	aMin = std::min(aMin, b);
	float aSum = aMax + aMin;
	*l = aSum * 0.5f;
	if (*l <= 0.0f)
		return;

	float aDelta = aMax - aMin;
	*s = aDelta;
	if (!(aDelta > 0.0f))
		return;

	float aDenom;
	if (*l <= 0.5f)
		aDenom = aSum;
	else
		aDenom = 2.0f - aSum;
	float aG = (aMax - g) / aDelta;
	float aB = (aMax - b) / aDelta;
	*s = aDelta / aDenom;
	float aH;
	if (aMax == r)
	{
		if (aMin == g)
			aH = aB + 5.0f;
		else
			aH = 1.0f - aG;
	}
	else
	{
		float aR = (aMax - r) / aDelta;
		if (aMax == g)
		{
			if (aMin == b)
				aH = aR + 1.0f;
			else
				aH = 3.0f - aB;
		}
		else if (aMin == r)
			aH = aG + 3.0f;
		else
			aH = 5.0f - aR;
	}
	*h = aH * (1.0f / 6.0f);
}

void FilterEffectDisposeForApp()
{
	for (int i = 0; i < NUM_FILTER_EFFECTS; i++)
	{
		FilterMap& aMap = gFilterMap[i];
		for (FilterMap::iterator it = aMap.begin(); it != aMap.end(); ++it)
		{
			if (it->second != NULL)
				delete it->second;
		}
		aMap.clear();
	}
}

void FilterEffectInitForApp()
{
}

void FilterEffectDoWhite(Sexy::MemoryImage* theImage)
{
	uint32* aBits = theImage->mBits;
	for (int y = 0; y < theImage->mHeight; y++)
	{
		for (int x = 0; x < theImage->mWidth; x++)
		{
			*aBits++ |= 0x00FFFFFF;
		}
	}
}

void FilterEffectDoLumSat(Sexy::MemoryImage* theImage, float theLum, float theSat)
{
	uint32* aBits = theImage->mBits;
	for (int y = 0; y < theImage->mHeight; y++)
	{
		for (int x = 0; x < theImage->mWidth; x++)
		{
			uint32* aCur = aBits++;
			uint32 aPixel = *aCur;
			float r = (aPixel & 0xFF) * (1.0f / 255.0f);
			float g = ((aPixel >> 8) & 0xFF) * (1.0f / 255.0f);
			float b = ((aPixel >> 16) & 0xFF) * (1.0f / 255.0f);
			float h, s, l;
			RGB_to_HSL(r, g, b, &h, &s, &l);
			s *= theSat;
			l *= theLum;
			HSL_to_RGB(h, s, l, &r, &g, &b);
			int aR = ClampInt((int)(r * 255.0f), 0, 255);
			int aG = ClampInt((int)(g * 255.0f), 0, 255);
			int aB = ClampInt((int)(b * 255.0f), 0, 255);
			*aCur = aR | (aPixel & 0xFF000000) | (aB << 16) | (aG << 8);
		}
	}
}

void FilterEffectDoWashedOut(Sexy::MemoryImage* theImage)
{
	FilterEffectDoLumSat(theImage, 1.8f, 0.2f);
}

void FilterEffectDoLessWashedOut(Sexy::MemoryImage* theImage)
{
	FilterEffectDoLumSat(theImage, 1.2f, 0.3f);
}

Sexy::Image* FilterEffectCreateImage(Sexy::Image* theImage, FilterEffect theFilterEffect)
{
	Sexy::MemoryImage* aImage = new Sexy::MemoryImage();
	aImage->mWidth = theImage->mWidth;
	aImage->mHeight = theImage->mHeight;
	uint32* aBits = new uint32[theImage->mWidth * theImage->mHeight + 1];
	aImage->mHasTrans = true;
	aImage->mHasAlpha = true;
	aImage->mBits = aBits;
	memset(aBits, 0, sizeof(uint32) * (theImage->mWidth * theImage->mHeight));
	aImage->mBits[theImage->mWidth * theImage->mHeight] = 0x4BEEFADE;

	Sexy::Graphics g(aImage);
	g.DrawImage(theImage, 0, 0);
	FixPixelsOnAlphaEdgeForBlending(aImage);

	switch (theFilterEffect)
	{
	case FILTER_EFFECT_WASHED_OUT:
		FilterEffectDoWashedOut(aImage);
		break;
	case FILTER_EFFECT_LESS_WASHED_OUT:
		FilterEffectDoLessWashedOut(aImage);
		break;
	case FILTER_EFFECT_WHITE:
		FilterEffectDoWhite(aImage);
		break;
	default:
		break;
	}

	aImage->mNumCols = theImage->mNumCols;
	aImage->mNumRows = theImage->mNumRows;
	aImage->mBitsChangedCount++;
	return aImage;
}

Sexy::Image* FilterEffectGetImage(Sexy::Image* theImage, FilterEffect theFilterEffect)
{
	FilterMap& aMap = gFilterMap[theFilterEffect];
	FilterMap::iterator it = aMap.find(theImage);
	if (it != aMap.end())
		return it->second;

	Sexy::Image* aFilterImage = FilterEffectCreateImage(theImage, theFilterEffect);
	aMap.insert(FilterMap::value_type(theImage, aFilterImage));
	return aFilterImage;
}
