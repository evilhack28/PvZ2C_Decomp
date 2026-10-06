//
//  TodCommon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-05.
//

#include "SexyAppFramework/Common.h"

#include "TodLib/TodCommon.h"
#include "TodLib/TodList.h"
#include "TodLib/TodStringFile.h"
#include "core.h"
#include "TodLib/TodDebug.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/PrimeText/PrimeTypeface.h"
#include "SexyAppFramework/MTRand.h"
#include "SexyAppFramework/Color.h"
#include "SexyAppFramework/SexyMatrix.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/MemoryImage.h"
#include "SexyAppFramework/EncodingParser.h"
#include "SexyAppFramework/Buffer.h"
#include "SexyAppFramework/PerfTimer.h"
#include <algorithm>

/////////////// TodCommon ///////////////

float RandRangeFloat(float theMin, float theMax)
{
	return Sexy::Rand(theMax - theMin) + theMin;
}

int RandRangeInt(int theMin, int theMax)
{
	return Sexy::Rand(theMax - theMin + 1) + theMin;
}

int RandRangeInt(int theMin, int theMax, Sexy::MTRand* theRand)
{
	return theRand->Next((unsigned long)(theMax - theMin + 1));
}

int ColorComponentMultiply(int theColor1, int theColor2)
{
	return ClampInt((theColor1 * theColor2) / 255, 0, 255);
}

Sexy::Color ColorsMultiply(const Sexy::Color& theColor1, const Sexy::Color& theColor2)
{
	Sexy::Color aColor;
	aColor.mRed = ColorComponentMultiply(theColor1.mRed, theColor2.mRed);
	aColor.mGreen = ColorComponentMultiply(theColor1.mGreen, theColor2.mGreen);
	aColor.mBlue = ColorComponentMultiply(theColor1.mBlue, theColor2.mBlue);
	aColor.mAlpha = ColorComponentMultiply(theColor1.mAlpha, theColor2.mAlpha);
	return aColor;
}

Sexy::Color ColorAdd(const Sexy::Color& theColor1, const Sexy::Color& theColor2)
{
	Sexy::Color aColor;
	int aRed = theColor1.mRed + theColor2.mRed;
	int aGreen = theColor1.mGreen + theColor2.mGreen;
	int aBlue = theColor1.mBlue + theColor2.mBlue;
	int aAlpha = theColor1.mAlpha + theColor2.mAlpha;
	aColor.mRed = ClampInt(aRed, 0, 255);
	aColor.mGreen = ClampInt(aGreen, 0, 255);
	aColor.mBlue = ClampInt(aBlue, 0, 255);
	aColor.mAlpha = ClampInt(aAlpha, 0, 255);
	return aColor;
}

Sexy::Color GetFlashingColor(int theCounter, int theFlashTime)
{
	int aPhase = theCounter % theFlashTime;
	int aHalf = theFlashTime / 2;
	int aDist = abs(aHalf - aPhase);
	int aGrey = ClampInt(aDist * 200 / aHalf + 55, 0, 255);
	return Sexy::Color(aGrey, aGrey, aGrey, 255);
}

const int MAX_GLOBAL_ALLOCATORS = 128;
TodAllocator gGobalAllocators[MAX_GLOBAL_ALLOCATORS];
int gNumGobalAllocators = 0;
bool gTodTriangleDrawAdditive = false;
float gCurrentZBufferValue;

TodAllocator* FindGlobalAllocator(int theSize)
{
	for (int i = 0; i < gNumGobalAllocators; i++)
	{
		TodAllocator* anAllocator = &gGobalAllocators[i];
		if (anAllocator->m_itemSize == theSize)
			return anAllocator;
	}

	TodAllocator* anAllocator = &gGobalAllocators[gNumGobalAllocators];
	gNumGobalAllocators++;
	anAllocator->Initialize(16, theSize);
	return anAllocator;
}

void FreeGlobalAllocators()
{
	for (int i = 0; i < gNumGobalAllocators; i++)
		gGobalAllocators[i].Dispose();
	gNumGobalAllocators = 0;
}

namespace Sexy
{
Color ColorLerp(Color theColor1, Color theColor2, float thePercent)
{
	Color aColor = theColor1;
	aColor.mRed += (int)(thePercent * (theColor2.mRed - theColor1.mRed));
	aColor.mGreen += (int)((theColor2.mGreen - theColor1.mGreen) * thePercent);
	aColor.mBlue += (int)((theColor2.mBlue - theColor1.mBlue) * thePercent);
	aColor.mAlpha += (int)((theColor2.mAlpha - theColor1.mAlpha) * thePercent);
	return aColor;
}
}

void SexyMatrix3Translation(Sexy::SexyMatrix3& theMatrix, float theX, float theY)
{
	theMatrix.m02 += theX;
	theMatrix.m12 += theY;
}

void SexyMatrix3Transpose(const Sexy::SexyMatrix3& theMatrix, Sexy::SexyMatrix3& theResult)
{
	float m00 = theMatrix.m00;
	float m10 = theMatrix.m10;
	float m20 = theMatrix.m20;
	float m01 = theMatrix.m01;
	float m11 = theMatrix.m11;
	float m21 = theMatrix.m21;
	float m02 = theMatrix.m02;
	float m12 = theMatrix.m12;
	float m22 = theMatrix.m22;
	theResult.m00 = m00;
	theResult.m01 = m10;
	theResult.m02 = m20;
	theResult.m10 = m01;
	theResult.m11 = m11;
	theResult.m12 = m21;
	theResult.m20 = m02;
	theResult.m21 = m12;
	theResult.m22 = m22;
}

void TodScaleTransformMatrix(Sexy::SexyMatrix3& theMatrix, float theX, float theY, float theScaleX, float theScaleY)
{
	theMatrix.m02 = theX;
	theMatrix.m00 = theScaleX;
	theMatrix.m11 = theScaleY;
	theMatrix.m10 = 0.0f;
	theMatrix.m20 = 0.0f;
	theMatrix.m01 = 0.0f;
	theMatrix.m21 = 0.0f;
	theMatrix.m12 = theY;
	theMatrix.m22 = 1.0f;
}

void TodZBufferValueClear(Sexy::Graphics* g)
{
	gCurrentZBufferValue = 0.999f;
	g->Get3D()->ClearDepthBuffer();
}

void TodZBufferValueIncrement()
{
	gCurrentZBufferValue -= 0.001f;
}

void TodScaleRotateTransformMatrix(Sexy::SexyMatrix3& theMatrix, float theX, float theY, float theRad, float theScaleX, float theScaleY)
{
	float aSin = sinf(theRad);
	float aCos = cosf(theRad);
	theMatrix.m00 = aCos * theScaleX;
	theMatrix.m10 = -(aSin * theScaleX);
	theMatrix.m20 = 0.0f;
	theMatrix.m01 = aSin * theScaleY;
	theMatrix.m11 = aCos * theScaleY;
	theMatrix.m21 = 0.0f;
	theMatrix.m02 = theX;
	theMatrix.m12 = theY;
	theMatrix.m22 = 1.0f;
}

void SexyMatrix3Inverse(const Sexy::SexyMatrix3& m, Sexy::SexyMatrix3& r)
{
	float m22 = m.m22;
	float m10 = m.m10;
	float m12 = m.m12;
	float m21 = m.m21;
	float m20 = m.m20;
	float aCofactor10 = m20 * m12 - m10 * m22;
	float m11 = m.m11;
	float m01 = m.m01;
	float aCofactor00 = m22 * m11 - m21 * m12;
	float m00 = m.m00;
	float m02 = m.m02;
	float aCofactor20 = m10 * m21 - m20 * m11;
	float aInvDet = 1.0f / (aCofactor10 * m01 + m00 * aCofactor00 + m02 * aCofactor20);
	r.m00 = aInvDet * aCofactor00;
	r.m01 = aInvDet * (m02 * m21 - m01 * m22);
	r.m02 = aInvDet * (m01 * m12 - m02 * m11);
	r.m10 = aInvDet * aCofactor10;
	r.m11 = aInvDet * (m22 * m00 - m02 * m20);
	r.m12 = aInvDet * (m02 * m10 - m12 * m00);
	r.m20 = aInvDet * aCofactor20;
	r.m21 = aInvDet * (m20 * m01 - m21 * m00);
	r.m22 = aInvDet * (m11 * m00 - m10 * m01);
}

void SexyMatrix3Multiply(Sexy::SexyMatrix3& m, const Sexy::SexyMatrix3& l, const Sexy::SexyMatrix3& r)
{
	float l01 = l.m01;
	float r10 = r.m10;
	float r11 = r.m11;
	float r12 = r.m12;
	float l11 = l.m11;
	float l21 = l.m21;
	float l00 = l.m00;
	float r00 = r.m00;
	float r01 = r.m01;
	float r02 = r.m02;
	float l10 = l.m10;
	float l20 = l.m20;
	float l02 = l.m02;
	float r20 = r.m20;
	float r21 = r.m21;
	float r22 = r.m22;
	float l12 = l.m12;
	float l22 = l.m22;
	m.m00 = r10 * l01 + l00 * r00 + l02 * r20;
	m.m01 = r11 * l01 + l00 * r01 + l02 * r21;
	m.m10 = l11 * r10 + r00 * l10 + r20 * l12;
	m.m11 = l11 * r11 + r01 * l10 + r21 * l12;
	m.m20 = l21 * r10 + r00 * l20 + r20 * l22;
	m.m02 = r12 * l01 + l00 * r02 + l02 * r22;
	m.m12 = l11 * r12 + r02 * l10 + r22 * l12;
	m.m21 = l21 * r11 + r01 * l20 + r21 * l22;
	m.m22 = l21 * r12 + r02 * l20 + r22 * l22;
}

SexyString TodReplaceString(const SexyString& theText, const SexyChar* theStringToFind, const SexyString& theStringToSubstitute)
{
	SexyString aFinalString = TodStringTranslate(theText);
	size_t aPos = aFinalString.find(theStringToFind, 0);
	if (aPos != SexyString::npos)
		aFinalString.replace(aPos, wcslen(theStringToFind), TodStringTranslate(theStringToSubstitute));
	return aFinalString;
}

std::string TodReplaceString(const std::string& theSourceText, const std::string& theFindText, const std::string& theSubstitution)
{
	SexyString aResult = TodReplaceString(Sexy::UTF8StringToWString(theSourceText), Sexy::UTF8StringToWString(theFindText).c_str(), Sexy::UTF8StringToWString(theSubstitution));
	return Sexy::WStringToString(aResult);
}

SexyString TodReplaceNumberString(const SexyString& theText, const SexyChar* theStringToFind, int theNumber)
{
	SexyString aFinalString = TodStringTranslate(theText);
	size_t aPos = aFinalString.find(theStringToFind, 0);
	if (aPos != SexyString::npos)
		aFinalString.replace(aPos, wcslen(theStringToFind), Sexy::StrFormat(L"%d", theNumber));
	return aFinalString;
}

void TodStringRemoveReturnChars(SexyString& theString)
{
	int i = 0;
	while (i < (int)theString.size())
	{
		if (theString[i] == L'\r')
			theString.replace(i, 1, L"");
		else
			i++;
	}
}

bool CharIsSpaceInFormat(SexyChar theChar, TodStringListFormat* theFormat)
{
	if (theChar == L' ')
		return true;
	return TestFlag<unsigned int>(theFormat->m_formatFlags, TOD_FORMAT_IGNORE_NEWLINES) && theChar == L'\n';
}

SexyString TodStringListFind(const SexyString& theName);
bool TodStringListReadFile(const char* theFileName);
bool TodStringListReadName(const SexyChar*& thePtr, SexyString& theName);
bool TodStringListReadValue(const SexyChar*& thePtr, SexyString& theValue);
bool TodStringListReadItems(const SexyChar* theFileText);

TodStringListFormat* gTodStringFormats = NULL;
int gTodStringFormatCount = 0;

void TodStringListSetColors(TodStringListFormat* theFormats, int theCount)
{
	gTodStringFormats = theFormats;
	gTodStringFormatCount = theCount;
}

SexyString TodStringListFind(const SexyString& theName)
{
	std::string aKey = Sexy::WStringToString(theName);
	std::map<std::string, std::wstring>::iterator anItr = Sexy::gSexyAppBase->mStringProperties.find(aKey);
	if (anItr != Sexy::gSexyAppBase->mStringProperties.end())
		return Sexy::SexyStringToWString(anItr->second);
	return Sexy::StrFormat(L"<Missing %ls>", theName.c_str());
}

SexyString TodStringTranslate(const SexyString& theString)
{
	size_t aLen = theString.size();
	if (aLen >= 3 && theString[0] == L'[')
	{
		SexyString aName = theString.substr(1, aLen - 2);
		SexyString aTranslated = TodStringListFind(aName);
		return aTranslated;
	}
	return theString;
}

SexyString TodStringTranslate(const SexyChar* theString)
{
	if (theString == NULL)
		return SexyString(L"");

	size_t aLen = wcslen(theString);
	if (aLen >= 3 && theString[0] == L'[')
	{
		SexyString aName(theString + 1, aLen - 2);
		return TodStringListFind(aName);
	}
	return SexyString(theString);
}

bool TodStringListExists(const SexyString& theString)
{
	bool aExists = false;
	size_t aLen = theString.size();
	if (aLen >= 3 && theString[0] == L'[')
	{
		std::string aKey = Sexy::WStringToString(theString.substr(1, aLen - 2));
		aExists = Sexy::gSexyAppBase->mStringProperties.find(aKey) != Sexy::gSexyAppBase->mStringProperties.end();
	}
	return aExists;
}

SexyString TodStringTranslateAll(const SexyString& theString)
{
	SexyString aString = theString;
	size_t aStart;
	size_t aEnd;
	while ((aStart = aString.find(L"[", 0)) != SexyString::npos && (aEnd = aString.find(L"]", aStart)) != SexyString::npos)
	{
		SexyString aKey = aString.substr(aStart, aEnd - aStart + 1);
		SexyString aTranslated = TodStringTranslate(aKey);
		aString = aString.substr(0, aStart) + aTranslated + aString.substr(aEnd + 1);
	}
	return aString;
}

bool TodStringListReadName(const SexyChar*& thePtr, SexyString& theName)
{
	const SexyChar* aStart = wcschr(thePtr, L'[');
	if (aStart == NULL)
	{
		if (wcsspn(thePtr, L" \n\r\t") == wcslen(thePtr))
		{
			theName = L"";
			return true;
		}
	}
	else
	{
		aStart++;
		const SexyChar* aEnd = wcschr(aStart, L']');
		if (aEnd != NULL)
		{
			int aLen = aEnd - aStart;
			theName.assign(aStart, aLen);
			theName = Sexy::Trim(theName);
			if (theName.size() != 0)
			{
				thePtr += aLen + 2;
				return true;
			}
		}
	}
	return false;
}

void TodStringListLoad(const char* theFileName)
{
	if (!TodStringListReadFile(theFileName))
	{
		std::string aMessage = Sexy::StrFormat("Failed to load string list file '%s'", theFileName);
		TodErrorMessageBox(aMessage.c_str(), "Error");
	}
}

void TodDrawImageCelF(Sexy::Graphics* g, Sexy::Image* theImageStrip, float thePosX, float thePosY, int theCelCol, int theCelRow)
{
	int aCelWidth = theImageStrip->GetCelWidth();
	int aCelHeight = theImageStrip->GetCelHeight();
	Sexy::Rect aSrcRect(aCelWidth * theCelCol, aCelHeight * theCelRow, aCelWidth, aCelHeight);
	g->DrawImageF(theImageStrip, thePosX, thePosY, aSrcRect);
}

void TodDrawImageCelScaled(Sexy::Graphics* g, Sexy::Image* theImageStrip, int thePosX, int thePosY, int theCelCol, int theCelRow, float theScaleX, float theScaleY)
{
	int aCelWidth = theImageStrip->GetCelWidth();
	int aCelHeight = theImageStrip->GetCelHeight();
	Sexy::Rect aSrcRect(aCelWidth * theCelCol, aCelHeight * theCelRow, aCelWidth, aCelHeight);
	int aDestWidth = FloatRoundToInt(aCelWidth * theScaleX);
	int aDestHeight = FloatRoundToInt(aCelHeight * theScaleY);
	Sexy::Rect aDestRect(thePosX, thePosY, aDestWidth, aDestHeight);
	g->DrawImage(theImageStrip, aDestRect, aSrcRect);
}

void TodDrawImageCelScaledF(Sexy::Graphics* g, Sexy::Image* theImageStrip, float thePosX, float thePosY, int theCelCol, int theCelRow, float theScaleX, float theScaleY)
{
	int aCelWidth = theImageStrip->GetCelWidth();
	int aCelHeight = theImageStrip->GetCelHeight();
	Sexy::Rect aSrcRect(aCelWidth * theCelCol, aCelHeight * theCelRow, aCelWidth, aCelHeight);
	Sexy::SexyMatrix3 aMatrix;
	TodScaleTransformMatrix(aMatrix, thePosX + g->mTransX + theScaleX * 0.5f * aCelWidth, thePosY + g->mTransY + theScaleY * 0.5f * aCelHeight, theScaleX, theScaleY);
	Sexy::Color aColor = g->mColorizeImages ? g->mColor : Sexy::Color(Sexy::Color::White);
	TodBltMatrix(g, theImageStrip, aMatrix, g->mClipRect, aColor, g->mDrawMode, aSrcRect);
}

void TodDrawImageCelCenterScaledF(Sexy::Graphics* g, Sexy::Image* theImageStrip, float thePosX, float thePosY, int theCelCol, float theScaleX, float theScaleY)
{
	int aCelWidth = theImageStrip->GetCelWidth();
	int aCelHeight = theImageStrip->GetCelHeight();
	Sexy::Rect aSrcRect(aCelWidth * theCelCol, 0, aCelWidth, aCelHeight);
	Sexy::SexyMatrix3 aMatrix;
	TodScaleTransformMatrix(aMatrix, thePosX + g->mTransX + aCelWidth * 0.5f, thePosY + g->mTransY + aCelHeight * 0.5f, theScaleX, theScaleY);
	Sexy::Color aColor = g->mColorizeImages ? g->mColor : Sexy::Color(Sexy::Color::White);
	TodBltMatrix(g, theImageStrip, aMatrix, g->mClipRect, aColor, g->mDrawMode, aSrcRect);
}

void TodDrawImageScaledF(Sexy::Graphics* g, Sexy::Image* theImage, float thePosX, float thePosY, float theScaleX, float theScaleY)
{
	Sexy::Rect aSrcRect(0, 0, theImage->mWidth, theImage->mHeight);
	Sexy::SexyMatrix3 aMatrix;
	TodScaleTransformMatrix(aMatrix, thePosX + g->mTransX + theImage->mWidth * 0.5f * theScaleX, thePosY + g->mTransY + theImage->mHeight * 0.5f * theScaleY, theScaleX, theScaleY);
	Sexy::Color aColor = g->mColorizeImages ? g->mColor : Sexy::Color(Sexy::Color::White);
	TodBltMatrix(g, theImage, aMatrix, g->mClipRect, aColor, g->mDrawMode, aSrcRect);
}

void TodDrawImageCenterScaledF(Sexy::Graphics* g, Sexy::Image* theImage, float thePosX, float thePosY, float theScaleX, float theScaleY)
{
	Sexy::Rect aSrcRect(0, 0, theImage->mWidth, theImage->mHeight);
	Sexy::SexyMatrix3 aMatrix;
	TodScaleTransformMatrix(aMatrix, g->mTransX + theImage->mWidth * 0.5f + thePosX, g->mTransY + theImage->mHeight * 0.5f + thePosY, theScaleX, theScaleY);
	Sexy::Color aColor = g->mColorizeImages ? g->mColor : Sexy::Color(Sexy::Color::White);
	TodBltMatrix(g, theImage, aMatrix, g->mClipRect, aColor, g->mDrawMode, aSrcRect);
}

bool TodAppCloseRequest()
{
	return false;
}

bool TodAppHasUsedCheatKeys()
{
	return false;
}

void TodADeviceImageToMap(Sexy::SharedImageRef* theImage, const std::string& thePath)
{
}

void TodMarkImageForSanding(Sexy::Image* theImage)
{
}

void TodSandImageIfNeeded(Sexy::Image* theImage)
{
}

void TodGetExeDirectory(char* theBuffer)
{
}

bool TodFindImagePath(Sexy::Image* theImage, std::string& thePath)
{
	thePath = theImage->mFilePath;
	return true;
}

TodWeightedGridArray* TodPickFromWeightedGridArray(TodWeightedGridArray* theArray, int theCount)
{
	int aTotalWeight = 0;
	for (int i = 0; i < theCount; i++)
		aTotalWeight += theArray[i].m_weight;

	int aRandom = Sexy::Rand(aTotalWeight);
	int aAccum = 0;
	for (int i = 0; i < theCount; i++)
	{
		aAccum += theArray[i].m_weight;
		if (aRandom < aAccum)
			return &theArray[i];
	}
	return NULL;
}

float TodCalcSmoothWeight(float theWeight, float theLastPicked, float theSecondLastPicked)
{
	if (theWeight < 0.000001f)
		return 0.0f;

	float aInverse = 1.0f / theWeight;
	float aFactor = ClampFloat(((((theSecondLastPicked + 1.0f) - (aInverse + aInverse)) / (aInverse + aInverse)) * 2.0f + 1.0f) * 0.25f
		+ ((((theLastPicked + 1.0f) - aInverse) / aInverse) * 2.0f + 1.0f) * 0.75f, 0.01f, 100.0f);
	return aFactor * theWeight;
}

void TodUpdateSmoothArrayPick(TodSmoothArray* theArray, int theCount, int thePickIndex)
{
	for (int i = 0; i < theCount; i++)
	{
		if (theArray[i].m_weight > 0.0f)
		{
			theArray[i].m_lastPicked += 1.0f;
			theArray[i].m_secondLastPicked += 1.0f;
		}
	}

	theArray[thePickIndex].m_secondLastPicked = theArray[thePickIndex].m_lastPicked;
	theArray[thePickIndex].m_lastPicked = 0.0f;
}

int TodPickFromSmoothArray(TodSmoothArray* theArray, int theCount, Sexy::MTRand* theRand)
{
	float aTotalWeight = 0.0f;
	for (int i = 0; i < theCount; i++)
		aTotalWeight += theArray[i].m_weight;

	float aNormalize = 1.0f / aTotalWeight;
	float aNormalizedTotal = 0.0f;
	for (int i = 0; i < theCount; i++)
		aNormalizedTotal += TodCalcSmoothWeight(aNormalize * theArray[i].m_weight, theArray[i].m_lastPicked, theArray[i].m_secondLastPicked);

	float aRandom;
	if (theRand == NULL)
		aRandom = Sexy::Rand(aNormalizedTotal);
	else
		aRandom = theRand->Next(aNormalizedTotal);

	float aAccum = 0.0f;
	int aPickIndex = 0;
	TodSmoothArray* aPicked = theArray;
	if (theCount >= 2)
	{
		for (aPickIndex = 0; aPickIndex < theCount - 1; aPickIndex++)
		{
			aAccum += TodCalcSmoothWeight(aNormalize * theArray[aPickIndex].m_weight, theArray[aPickIndex].m_lastPicked, theArray[aPickIndex].m_secondLastPicked);
			if (aRandom <= aAccum)
				break;
		}
		aPicked = &theArray[aPickIndex];
	}

	TodUpdateSmoothArrayPick(theArray, theCount, aPickIndex);
	return aPicked->m_item;
}

void DrawImageCentered(Sexy::Graphics* g, Sexy::Image* theImage, float theCX, float theCY, float theScaleX, float theScaleY)
{
	DrawImageCentered(g, theImage, theCX, theCY, JUST_CENTERX | JUST_CENTERY, theScaleX, theScaleY);
}

bool TodIsPointInPolygon(Sexy::SexyVector2* theVertices, int theCount, const Sexy::SexyVector2& thePoint)
{
	for (int i = 0; i < theCount; i++)
	{
		Sexy::SexyVector2 aStart = theVertices[i];
		Sexy::SexyVector2 aEnd;
		if (i == theCount - 1)
			aEnd = theVertices[0];
		else
			aEnd = theVertices[i + 1];

		Sexy::SexyVector2 aEdge = aEnd - aStart;
		Sexy::SexyVector2 aNormal = aEdge.Perp();
		Sexy::SexyVector2 aToPoint = thePoint - aStart;
		if (aNormal.Dot(aToPoint) < 0.0f)
			return false;
	}
	return true;
}

void DrawImageCentered(Sexy::Graphics* g, Sexy::Image* theImage, float theX, float theY, int theJust, float theScaleX, float theScaleY)
{
	if (theScaleX != 1.0f && theScaleY != 1.0f && (theJust & (JUST_CENTERX | JUST_CENTERY)))
	{
		Sexy::Transform aTransform;
		aTransform.Scale(theScaleX, theScaleY);
		aTransform.Translate(theX, theY);
		g->DrawImageTransformF(theImage, aTransform, 0.0f, 0.0f);
		return;
	}

	float aWidth = theImage->mWidth * theScaleX;
	float aHeight = theImage->mHeight * theScaleY;
	if ((theJust & (JUST_CENTERX)))
		theX -= aWidth * 0.5f;
	else if ((theJust & (JUST_RIGHT)))
		theX -= aWidth;

	if ((theJust & (JUST_CENTERY)))
		theY -= aHeight * 0.5f;
	else if ((theJust & (JUST_BOTTOM)))
		theY -= aHeight;

	int anIntX = (int)theX;
	if (theScaleX == 1.0f && theScaleY == 1.0f)
	{
		if ((anIntX == theX && (int)theY == theY) || !Sexy::gIs3D)
			g->DrawImage(theImage, anIntX, (int)theY);
		else
			g->DrawImageF(theImage, theX, theY);
	}
	else
	{
		g->DrawImage(theImage, anIntX, (int)theY, (int)aWidth, (int)aHeight);
	}
}

void SexyMatrix3ExtractScale(const Sexy::SexyMatrix3& m, float& theScaleX, float& theScaleY)
{
	float aAngle = (float)atan2((double)m.m00, (double)m.m10);
	float aAbsAngle = (float)abs((int)aAngle);
	if (aAbsAngle < CIRCLE_EIGHTH || aAbsAngle > CIRCLE_EIGHTH * 3.0f)
		theScaleX = (float)((double)m.m10 / cos((double)aAngle));
	else
		theScaleX = (float)((double)m.m00 / sin((double)aAngle));

	aAngle = (float)atan2((double)m.m11, (double)m.m01);
	aAbsAngle = (float)abs((int)aAngle);
	if (aAbsAngle >= CIRCLE_EIGHTH && aAbsAngle <= CIRCLE_EIGHTH * 3.0f)
		theScaleY = (float)((double)m.m11 / sin((double)aAngle));
	else
		theScaleY = (float)((double)m.m01 / cos((double)aAngle));
}

void TodDrawString(Sexy::Graphics* g, const SexyString& theText, int thePosX, int thePosY, Sexy::Font* theFont, Sexy::Color theColor, DrawStringJustification theJustification)
{
	SexyString aString = TodStringTranslate(theText);
	if (theJustification == DS_ALIGN_RIGHT || theJustification == DS_ALIGN_RIGHT_VERTICAL_MIDDLE)
	{
		int aWidth = theFont->StringWidth(aString);
		thePosX -= aWidth;
	}
	else if (theJustification == DS_ALIGN_CENTER || theJustification == DS_ALIGN_CENTER_VERTICAL_MIDDLE)
	{
		int aWidth = theFont->StringWidth(aString);
		thePosX -= aWidth / 2;
	}
	theFont->DrawString(g, thePosX, thePosY, aString, theColor, g->mClipRect);
}

void TodDrawString(Sexy::Graphics* g, const SexyString& theText, int thePosX, int thePosY, Sexy::PrimeTypeface* theFont, Sexy::Color theColor, DrawStringJustification theJustification)
{
	SexyString aString = TodStringTranslate(theText);
	if (theJustification == DS_ALIGN_RIGHT || theJustification == DS_ALIGN_RIGHT_VERTICAL_MIDDLE)
	{
		int aWidth;
		int aHeight;
		theFont->SizeString_Paragraph(aString, aWidth, aHeight);
		thePosX -= aWidth;
	}
	else if (theJustification == DS_ALIGN_CENTER || theJustification == DS_ALIGN_CENTER_VERTICAL_MIDDLE)
	{
		int aWidth;
		int aHeight;
		theFont->SizeString_Paragraph(aString, aWidth, aHeight);
		thePosX -= aWidth / 2;
	}
	theFont->DrawString_Simple(g, (float)thePosX, (float)thePosY, aString, theColor, NULL);
}

static unsigned int AverageNearbyPixels(Sexy::MemoryImage* theImage, unsigned int* thePixel, int theX, int theY)
{
	int aRed = 0;
	int aGreen = 0;
	int aBlue = 0;
	int aCount = 0;
	for (int aDy = -1; aDy <= 1; aDy++)
	{
		for (int aDx = -1; aDx <= 1; aDx++)
		{
			if (aDx == 0 && aDy == 0)
				continue;
			int aNX = theX + aDx;
			int aNY = theY + aDy;
			if (aNX < 0 || aNY < 0 || aNX >= theImage->mWidth || aNY >= theImage->mHeight)
				continue;

			unsigned int aPixel = thePixel[aDy * theImage->mWidth + aDx];
			if ((aPixel & 0xFF000000) != 0)
			{
				aRed += (aPixel >> 16) & 0xFF;
				aGreen += (aPixel >> 8) & 0xFF;
				aBlue += aPixel & 0xFF;
				aCount++;
			}
		}
	}

	if (aCount == 0)
		return 0;
	return (std::min(aRed / aCount, 255) << 16) | (std::min(aGreen / aCount, 255) << 8) | std::min(aBlue / aCount, 255);
}

void FixPixelsOnAlphaEdgeForBlending(Sexy::Image* theImage)
{
	Sexy::MemoryImage* aImage = (Sexy::MemoryImage*)theImage;
	if (aImage->mBits == NULL)
		return;
	aImage->CommitBits();
	if (!aImage->mHasTrans)
		return;

	Sexy::PerfTimer aTimer;
	aTimer.Start();
	unsigned int* aBits = aImage->mBits;
	for (int y = 0; y < aImage->mHeight; y++)
	{
		for (int x = 0; x < aImage->mWidth; x++)
		{
			unsigned int* aPixel = aBits++;
			if ((*aPixel & 0xFF000000) == 0)
				*aPixel = AverageNearbyPixels(aImage, aPixel, x, y);
		}
	}
	aImage->mBitsChangedCount++;
	aTimer.GetDuration();
}

void TodBltMatrix(Sexy::Graphics* g, Sexy::Image* theImage, const Sexy::SexyMatrix3& theTransform, const Sexy::Rect& theClipRect, const Sexy::Color& theColor, int theDrawMode, const Sexy::Rect& theSrcRect)
{
	float aOffsetX = -g->mTransX;
	float aOffsetY = -g->mTransY;
	if (Sexy::gSexyAppBase->Is3DAccelerated())
	{
		aOffsetX -= 0.5f;
		aOffsetY -= 0.5f;
	}
	else
	{
		if (theDrawMode == Sexy::Graphics::DRAWMODE_ADDITIVE)
			gTodTriangleDrawAdditive = true;
	}

	Sexy::Rect aOldClipRect = g->mClipRect;
	Sexy::Color aOldColor = g->mColor;
	int aOldDrawMode = g->GetDrawMode();
	bool aOldColorizeImages = g->GetColorizeImages();

	if (theClipRect.mX == 0 && theClipRect.mY == 0 && theClipRect.mWidth == Sexy::gSexyAppBase->mWidth && theClipRect.mHeight == Sexy::gSexyAppBase->mHeight && !Sexy::gSexyAppBase->Is3DAccelerated())
		g->mClipRect = Sexy::Rect(0, 0, Sexy::gSexyAppBase->mWidth + 1, Sexy::gSexyAppBase->mHeight + 1);
	else
		g->mClipRect = theClipRect;

	g->SetColor(theColor);
	g->SetDrawMode(theDrawMode);
	if (theColor == Sexy::Color(Sexy::Color::White))
		g->SetColorizeImages(false);
	else
		g->SetColorizeImages(true);

	g->DrawImageMatrix(theImage, theTransform, theSrcRect, aOffsetX, aOffsetY);

	g->mClipRect = aOldClipRect;
	g->SetColor(aOldColor);
	g->SetDrawMode(aOldDrawMode);
	g->SetColorizeImages(aOldColorizeImages);
	gTodTriangleDrawAdditive = false;
}

bool TodStringListReadValue(const SexyChar*& thePtr, SexyString& theValue)
{
	const SexyChar* aBracket = wcschr(thePtr, L'[');
	if (aBracket == NULL)
	{
		int aLen = wcslen(thePtr);
		theValue.assign(thePtr, aLen);
		theValue = Sexy::Trim(theValue);
		TodStringRemoveReturnChars(theValue);
		thePtr += aLen;
	}
	else
	{
		int aLen = aBracket - thePtr;
		theValue.assign(thePtr, aLen);
		theValue = Sexy::Trim(theValue);
		TodStringRemoveReturnChars(theValue);
		thePtr += aLen;
		if (aBracket[-1] == L'\\')
		{
			SexyString aRest;
			thePtr++;
			TodStringListReadValue(thePtr, aRest);
			theValue = theValue.erase(theValue.size() - 1) + L"[" + aRest;
		}
	}
	return true;
}

bool TodStringListReadItems(const SexyChar* theFileText)
{
	const SexyChar* aPtr = theFileText;
	bool aResult;
	for (;;)
	{
		SexyString aName;
		aResult = TodStringListReadName(aPtr, aName);
		if (!aResult || aName.size() == 0)
			break;

		SexyString aValue;
		if (!TodStringListReadValue(aPtr, aValue))
		{
			aResult = false;
			break;
		}
		SexyString aUpperName = Sexy::StringToUpper(aName);
		Sexy::gSexyAppBase->SetString(Sexy::WStringToString(aUpperName), aValue);
	}
	return aResult;
}

bool TodStringListReadFile(const char* theFileName)
{
	Sexy::Buffer aBuffer;
	Sexy::EncodingParser* aParser = new Sexy::EncodingParser();
	bool aResult = aParser->OpenFile(theFileName);
	if (aResult)
	{
		SexyString aFileText(L"");
		wchar_t aChar;
		for (;;)
		{
			aResult = aParser->EndOfFile();
			if (aResult)
				break;
			for (;;)
			{
				Sexy::EncodingParser::GetCharReturnType aType = aParser->GetChar(&aChar);
				if (aType == Sexy::EncodingParser::END_OF_FILE)
					break;
				if (aType != Sexy::EncodingParser::SUCCESSFUL)
					return aResult;
				aFileText.push_back(aChar);
			}
		}

		aParser->CloseFile();
		delete aParser;
		if (wcslen(aFileText.c_str()) != 0)
			aResult = TodStringListReadItems(aFileText.c_str());
	}
	return aResult;
}
