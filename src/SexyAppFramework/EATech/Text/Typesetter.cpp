//
//  Typesetter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-23.
//

#include "SexyAppFramework/Common.h"

#include <EAText/EATextTypesetter.h>
#include <EAText/EATextBreak.h>
#include <EAText/EATextIterator.h>

namespace EA
{
namespace Text
{

/////////////// Layout ///////////////

void Typesetter::GetObjectMetrics(index_t iGlyph, GlyphMetrics& glyphMetrics)
{
	Item* pItem = GetScheduleItemFromCharIndex(mLineLayout.GetCharIndexFromGlyphIndex(iGlyph), true);
	glyphMetrics = pItem->mObject.mGlyphMetrics;
}

float Typesetter::GetTextWidth(index_t iCharBegin)
{
	if (!iCharBegin)
		return 0;
	index_t iGlyph = mLineLayout.GetGlyphIndexFromCharIndex(iCharBegin);
	const GlyphLayoutInfo& gli = mLineLayout.mGlyphLayoutInfoArray[iGlyph - (iGlyph != 0)];
	return gli.mfAdvance + gli.mfPenX;
}

void Typesetter::ReverseGlyphs(GlyphLayoutInfo* pGLIBegin, GlyphLayoutInfo* pGLILast, float fRunStartPos, float fRunEndPos)
{
	const float fSum = fRunEndPos + fRunStartPos;
	for (; pGLIBegin < pGLILast; ++pGLIBegin)
	{
		const float fPenX = fSum - pGLIBegin->mfPenX;
		const float fDelta = fPenX - pGLIBegin->mfPenX - pGLIBegin->mfAdvance;
		pGLIBegin->mfPenX = fPenX;
		pGLIBegin->mfAdvance = -pGLIBegin->mfAdvance;
		pGLIBegin->mfX1 += fDelta;
		pGLIBegin->mfX2 += fDelta;
	}
}

/////////////// Schedule ///////////////

bool Typesetter::Validate()
{
	bool bResult = mLineLayout.Validate(true);
	if (mLineState == kLineStateComplete && !mLineLayout.mGlyphArray.empty())
	{
		if (mLineLayout.mLineCount == 0)
			bResult = false;
	}
	if (mScheduleEnd.mnScheduleIndex != (unsigned)mSchedule.size())
		bResult = false;
	return mScheduleEnd.mnCharOffset == 0 ? bResult : false;
}

void Typesetter::AddTextRun(const Char* pText, index_t nTextLength)
{
	Validate();
	mSchedule.push_back();
	Item& item = mSchedule.back();
	item.mType = kItemTypeText;
	item.mIndex = mScheduleEnd.mnCharBase;
	item.mCount = nTextLength;
	item.mpStyle = mpCurrentTextStyle;
	item.mText.mpCharData = pText;
	mScheduleEnd.mnScheduleIndex++;
	mScheduleEnd.mnCharBase += nTextLength;
	if (mLineState == kLineStateComplete)
		mLineState = kLineStatePartial;
	Validate();
}

void Typesetter::NextLine(bool bAddLineSpace)
{
	Validate();
	mLineLayout.mCharScheduleIndex = mLineEnd.GetCharIndex();
	mLineState = IsScheduleEmpty() ? kLineStateComplete : kLineStatePartial;
	mLineBegin = mLineEnd;
	mAnalysisEnd = mLineEnd;
	mbEllipsize = false;
	mBidiRunInfoArray.clear();
	mfPenX = 0;
	mfPenXMax = 0;
	if (bAddLineSpace)
	{
		const float fLineSpace = mLayoutSettings.mTextStyleDefault.mfLineSpace;
		if (fLineSpace > 0)
			mfLayoutPenY += mLayoutSettings.mfYScale * fLineSpace;
		else
			mfLayoutPenY += (ceilf(mLineLayout.mLineMetrics.mfBaseline) - floorf(mLineLayout.mLineMetrics.mfDescent)) * mLayoutSettings.mfYScale;
	}
	mLineLayout.NewLine();
	Validate();
}

Point Typesetter::GetParagraphSize(const Char* pText, index_t nTextSize, const TextStyle* pTextStyle, float fLayoutWidth)
{
	Point size(0, 0);
	LineLayout& lineLayout = GetLineLayout();
	Reset(true);
	SetLayoutSpace(fLayoutWidth > 0 ? fLayoutWidth : 10000.f, 0, 0);
	SetDefaultTextStyle(pTextStyle);
	AddTextRun(pText, nTextSize);
	while (GetLineState() != kLineStateComplete)
	{
		FinalizeLine();
		size.mY += lineLayout.GetLineHeight();
		size.mX = std::max(size.mX, lineLayout.mLineMetrics.mfVisibleSpace);
		NextLine(false);
	}
	return size;
}

void Typesetter::AdjustWhitespaceEmbedding()
{
	if (!mBidiRunInfoArray.empty())
	{
		RunInfo* pRunInfo = &mBidiRunInfoArray.back();
		if (pRunInfo->mnBidiLevel % 2 != mLayoutSettings.mDirection)
		{
			const eastl_size_t iLast = mLineLayout.mCharArray.find_last_not_of(EA_CHAR16(" "));
			if (iLast != mLineLayout.mCharArray.size() - 1)
			{
				eastl_size_t iBegin = 0;
				if (iLast == (eastl_size_t)-1)
					mBidiRunInfoArray.pop_back();
				else
				{
					iBegin = iLast + 1;
					pRunInfo->mnCharEnd = iBegin;
				}
				RunInfo newRunInfo(kScriptUnknown, mLayoutSettings.mDirection, iBegin, mLineLayout.mCharArray.size());
				mBidiRunInfoArray.push_back(newRunInfo);
			}
		}
	}
}

void Typesetter::FinalizeLine()
{
	Validate();
	if (mLineState == kLineStatePartial && !IsScheduleEmpty())
		ProcessLine();
	mLineLayout.CalculateVisibleSpace();
	const index_t nLineLength = mLineLayout.mLineMetrics.mnLineLength;
	if (nLineLength != mLineLayout.mCharArray.size())
	{
		const index_t nGlyphCount = mLineLayout.GetGlyphIndexFromCharIndex(nLineLength);
		mLineLayout.mGlyphArray.resize(nGlyphCount);
		mLineLayout.mGlyphInfoArray.resize(nGlyphCount);
		mLineLayout.mGlyphLayoutInfoArray.resize(nGlyphCount);
		mLineLayout.mCharIndexArray.resize(nGlyphCount);
		mLineLayout.mCharArray.resize(nLineLength);
		mLineLayout.mAnalysisInfoArray.resize(nLineLength);
		mLineLayout.mGlyphIndexArray.resize(nLineLength);
		const eastl_size_t nRunCount = mBidiRunInfoArray.size();
		for (eastl_size_t i = 0; i < nRunCount; i++)
		{
			if (nLineLength <= mBidiRunInfoArray[i].mnCharEnd)
			{
				mBidiRunInfoArray[i].mnCharEnd = nLineLength;
				mBidiRunInfoArray.resize(i + 1);
				break;
			}
		}
	}
	mLineLayout.mLineCount = 1;
	GetScheduleLocationFromCharIndex(mLineBegin.GetCharIndex() + mLineLayout.mLineMetrics.mnLineLength, mLineEnd, false);
	mAnalysisEnd = mLineEnd;
	mnLastLineEndIndex += mLineLayout.mLineMetrics.mnLineLength;
	Validate();
	if (mbEllipsize && mLineLayout.mLineMetrics.mfSpace > mfLayoutSpace)
		SubstituteEllipsis();
	AdjustWhitespaceEmbedding();
	AdjustPositioning();
	OrderGlyphs();
	mLineState = kLineStateFull;
	Validate();
}

/////////////// Processing ///////////////

Typesetter::LineState Typesetter::ProcessLine()
{
	Validate();
	if (mLineState != kLineStateFull)
	{
		mfPenX = 0;
		mfPenXMax = 0;
		mBidiRunInfoArray.clear();
		UpdateAnalysis();
		ShapeText();
		UpdateLineState();
	}
	Validate();
	return mLineState;
}

void Typesetter::ShapeGeneral(eastl_size_t iCharBegin, eastl_size_t iCharEnd)
{
	while (iCharBegin < iCharEnd)
	{
		Char charCluster[32];
		eastl_size_t clusterSize;
		eastl_size_t charCount = GetGeneralCharCluster(iCharBegin, iCharEnd, charCluster, clusterSize);
		AppendGeneralCharCluster(iCharBegin, charCount, charCluster, clusterSize);
		iCharBegin += charCount;
	}
}

void Typesetter::ShapeText(Script script, eastl_size_t iCharBegin, eastl_size_t iCharEnd)
{
	switch (script)
	{
	case kScriptArabic:
		ShapeArabic(iCharBegin, iCharEnd);
		break;
	case kScriptBengali:
	case kScriptDevanagari:
	case kScriptGujarati:
	case kScriptGurmukhi:
	case kScriptKannada:
	case kScriptLimbu:
	case kScriptMalayalam:
	case kScriptOriya:
	case kScriptSinhala:
	case kScriptTamil:
	case kScriptTelugu:
	case kScriptTibetan:
		ShapeIndic(iCharBegin, iCharEnd);
		break;
	case kScriptHangul:
		ShapeHangul(iCharBegin, iCharEnd);
		break;
	case kScriptHebrew:
		ShapeHebrew(iCharBegin, iCharEnd);
		break;
	case kScriptThai:
		ShapeThai(iCharBegin, iCharEnd);
		break;
	default:
		ShapeGeneral(iCharBegin, iCharEnd);
		break;
	}
}

Typesetter::Item* Typesetter::GetScheduleItemFromCharIndex(index_t charIndex, bool bCharIndexIsLineRelative)
{
	ScheduleLocation scheduleLocation;
	GetScheduleLocationFromCharIndex(charIndex, scheduleLocation, bCharIndexIsLineRelative);
	return &mSchedule[scheduleLocation.mnScheduleIndex];
}

/////////////// Accessors ///////////////

LayoutSettings& Typesetter::GetLayoutSettings()
{
	return mLayoutSettings;
}

const LayoutSettings& Typesetter::GetLayoutSettings() const
{
	return mLayoutSettings;
}

void Typesetter::SetLayoutSpace(float fSpace, float fPenX, float fPenY)
{
	mfLayoutSpace = fSpace;
	mfLayoutPenX = fPenX;
	mfLayoutPenY = fPenY;
}

void Typesetter::GetLayoutSpace(float& fSpace, float& fPenX, float& fPenY) const
{
	fSpace = mfLayoutSpace;
	fPenX = mfLayoutPenX;
	fPenY = mfLayoutPenY;
}

void Typesetter::SetFontServer(FontServer* pFontServer)
{
	mpFontServer = pFontServer;
}

const TextStyle& Typesetter::GetDefaultTextStyle() const
{
	return mLayoutSettings.mTextStyleDefault;
}

index_t Typesetter::GetEndCharIndex() const
{
	return mScheduleEnd.mnCharBase;
}

Typesetter::LineState Typesetter::GetLineState() const
{
	return mLineState;
}

void Typesetter::EllipsizeLine(bool bEnable)
{
	mbEllipsize = bEnable;
}

LineLayout& Typesetter::GetLineLayout()
{
	return mLineLayout;
}

bool Typesetter::IsScheduleEmpty() const
{
	return mAnalysisEnd.mnScheduleIndex == mScheduleEnd.mnScheduleIndex;
}

void Typesetter::AddStyleChange(const TextStyle* pStyle)
{
	mpCurrentTextStyle = AddTextStyle(pStyle);
}

void Typesetter::AddLineBreak()
{
	Validate();
	mSchedule.push_back();
	Item& item = mSchedule.back();
	item.mType = kItemTypeLineBreak;
	item.mIndex = mScheduleEnd.mnCharBase;
	item.mCount = 1;
	item.mpStyle = mpCurrentTextStyle;
	mScheduleEnd.mnScheduleIndex++;
	mScheduleEnd.mnCharBase++;
	if (mLineState == kLineStateComplete)
		mLineState = kLineStatePartial;
	Validate();
}

void Typesetter::AddParagraphBreak()
{
	Validate();
	mSchedule.push_back();
	Item& item = mSchedule.back();
	item.mType = kItemTypeParagraphBreak;
	item.mIndex = mScheduleEnd.mnCharBase;
	item.mCount = 1;
	item.mpStyle = mpCurrentTextStyle;
	mScheduleEnd.mnScheduleIndex++;
	mScheduleEnd.mnCharBase++;
	if (mLineState == kLineStateComplete)
		mLineState = kLineStatePartial;
	Validate();
}

void Typesetter::ShapeIndic(eastl_size_t iCharBegin, eastl_size_t iCharEnd)
{
	ShapeGeneral(iCharBegin, iCharEnd);
}

void Typesetter::ShapeThai(eastl_size_t iCharBegin, eastl_size_t iCharEnd)
{
	while (iCharBegin < iCharEnd)
	{
		Char charCluster[32];
		eastl_size_t clusterSize;
		eastl_size_t charCount = GetThaiCharCluster(iCharBegin, iCharEnd, charCluster, clusterSize);
		AppendThaiCharCluster(iCharBegin, charCount, charCluster, clusterSize);
		iCharBegin += charCount;
	}
}

void Typesetter::ShapeHebrew(eastl_size_t iCharBegin, eastl_size_t iCharEnd)
{
	while (iCharBegin < iCharEnd)
	{
		Char charCluster[32];
		eastl_size_t clusterSize;
		eastl_size_t charCount = GetHebrewCharCluster(iCharBegin, iCharEnd, charCluster, clusterSize);
		AppendHebrewCharCluster(iCharBegin, charCount, charCluster, clusterSize);
		iCharBegin += charCount;
	}
}

void Typesetter::ShapeHangul(eastl_size_t iCharBegin, eastl_size_t iCharEnd)
{
	int nState = 0;
	while (iCharBegin < iCharEnd)
	{
		Char charCluster[32];
		eastl_size_t clusterSize;
		eastl_size_t charCount = GetHangulCharCluster(iCharBegin, iCharEnd, charCluster, clusterSize, nState);
		AppendHangulCharCluster(iCharBegin, charCount, charCluster, clusterSize, nState);
		iCharBegin += charCount;
	}
}

index_t Typesetter::LayoutLine(const Char* pText, index_t nTextSize, float x, float y, const TextStyle* pTextStyle)
{
	Reset(true);
	SetLayoutSpace(100000.f, x, y);
	SetDefaultTextStyle(pTextStyle);
	mLayoutSettings.mTextStyleDefault.mHAlignment = kHALeft;
	AddTextRun(pText, nTextSize);
	FinalizeLine();
	mLineLayout.Offset(0, 0);
	return mLineLayout.mGlyphArray.size();
}

void Typesetter::AddObject(void* pObject, GlyphMetrics& glyphMetrics, bool bBindPrev, bool bBindNext)
{
	Validate();
	mSchedule.push_back();
	Item& item = mSchedule.back();
	item.mType = kItemTypeObject;
	item.mIndex = mScheduleEnd.mnCharBase;
	item.mCount = (bBindPrev ? 2 : 1) + bBindNext;
	item.mpStyle = mpCurrentTextStyle;
	item.mObject.mpObjectPtr = pObject;
	item.mObject.mGlyphMetrics = glyphMetrics;
	item.mObject.mbBindPrev = bBindPrev;
	item.mObject.mbBindNext = bBindNext;
	mScheduleEnd.mnScheduleIndex++;
	mScheduleEnd.mnCharBase += item.mCount;
	if (mLineState == kLineStateComplete)
		mLineState = kLineStatePartial;
	Validate();
}

const TextStyle* Typesetter::AddTextStyle(const TextStyle* textStyle)
{
	const eastl_size_t count = mTextStyleArray.size();
	for (eastl_size_t i = 0; i < count; i++)
	{
		if (mTextStyleArray[i] && *textStyle == *mTextStyleArray[i])
			return mTextStyleArray[i];
	}
	mTextStyleArray.push_back(textStyle);
	return mTextStyleArray.back();
}

eastl_size_t Typesetter::GetHangulCharCluster(eastl_size_t i, eastl_size_t iCharEnd, Char* pCharCluster, eastl_size_t& clusterSize, int& nState)
{
	nState = 3;
	pCharCluster[0] = mLineLayout.mCharArray[i];
	clusterSize = 1;
	return 1;
}

eastl_size_t Typesetter::GetUnicodeLigatureGlyph(const Char* pChar, eastl_size_t count, Font* pFont, GlyphId& glyphId)
{
	pFont->GetGlyphIds(pChar, 1, &glyphId, true, sizeof(GlyphId), false);
	return 1;
}

Typesetter::ScheduleLocation::ScheduleLocation()
  : mnScheduleIndex(0), mnCharBase(0), mnCharOffset(0)
{
}

bool Typesetter::ScheduleLocation::operator==(const ScheduleLocation& x)
{
	return mnScheduleIndex == x.mnScheduleIndex && mnCharBase == x.mnCharBase && mnCharOffset == x.mnCharOffset;
}

index_t Typesetter::ScheduleLocation::GetCharIndex() const
{
	return mnCharBase + mnCharOffset;
}

void Typesetter::GetScheduleLocationFromCharIndex(index_t charIndex, ScheduleLocation& scheduleLocation, bool bCharIndexIsLineRelative) const
{
	if (bCharIndexIsLineRelative)
		charIndex += mLineLayout.mCharScheduleIndex;
	index_t charBase = 0;
	for (eastl_size_t i = 0, count = mSchedule.size(); i < count; i++)
	{
		if (charIndex < charBase + mSchedule[i].mCount)
		{
			scheduleLocation.mnScheduleIndex = i;
			scheduleLocation.mnCharBase = charBase;
			scheduleLocation.mnCharOffset = charIndex - charBase;
			return;
		}
		charBase += mSchedule[i].mCount;
	}
	scheduleLocation = mScheduleEnd;
}

void Typesetter::Reset(bool bClearSchedule)
{
	Validate();
	if (bClearSchedule)
	{
		mSchedule.clear();
		mScheduleEnd.mnScheduleIndex = 0;
		mScheduleEnd.mnCharOffset = 0;
		mScheduleEnd.mnCharBase = 0;
		mLineBegin = mScheduleEnd;
		mnLastLineEndIndex = 0;
	}
	mLineEnd = mLineBegin;
	mAnalysisEnd = mLineBegin;
	mTextStyleArray.resize(1);
	mpCurrentTextStyle = &mLayoutSettings.mTextStyleDefault;
	mbNonGeneralScriptPresent = false;
	mLineState = kLineStateComplete;
	NextLine(false);
	mLineLayout.mCharScheduleIndex = 0;
	Validate();
}

eastl_size_t Typesetter::AppendGeneralCharCluster(eastl_size_t i, eastl_size_t charCount, const Char* charCluster, eastl_size_t clusterSize)
{
	GlyphId glyphIdArray[32];
	eastl_size_t iGlyph = 0;
	const AnalysisInfo* pAnalysisInfo = &mLineLayout.mAnalysisInfoArray[i];
	eastl_size_t iChar = 0;
	eastl_size_t glyphIdCount = 0;
	while (iChar < clusterSize)
	{
		const eastl_size_t n = GetGlyphsForChar(charCluster + iChar, clusterSize - iChar, pAnalysisInfo, glyphIdArray + iGlyph, glyphIdCount);
		AppendGeneralGlyphCluster(i, charCount, charCluster + iChar, n, glyphIdArray + iGlyph, glyphIdCount - iGlyph, pAnalysisInfo->mnBidiLevel);
		PlaceGeneralGlyphCluster(i + iChar, n);
		iChar += n;
		iGlyph = glyphIdCount;
	}
	return glyphIdCount;
}

} // namespace Text
} // namespace EA
