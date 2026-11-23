//
//  Typesetter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-23.
//

#include "SexyAppFramework/Common.h"

#include <EAText/EATextTypesetter.h>

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

} // namespace Text
} // namespace EA
