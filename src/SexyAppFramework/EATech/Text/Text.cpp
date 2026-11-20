//
//  Text.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include <EAText/EATextTypesetter.h>
#include <EAText/EATextCache.h>
#include <EAText/internal/EATextBidi.h>

namespace EA
{
namespace Text
{

extern Allocator::ICoreAllocator* gpCoreAllocator;

/////////////// Lifecycle ///////////////

Allocator::ICoreAllocator* GetAllocator()
{
	return gpCoreAllocator;
}

/////////////// LineLayout ///////////////

index_t LineLayout::GetGlyphIndexFromCharIndex(index_t iChar) const
{
	if (iChar < mGlyphIndexArray.size())
		return mGlyphIndexArray[iChar];
	return mGlyphArray.size();
}

index_t LineLayout::GetCharIndexFromGlyphIndex(index_t iGlyph) const
{
	if (iGlyph < mCharIndexArray.size())
		return mCharIndexArray[iGlyph];
	return mCharArray.size();
}

void LineLayout::GetGlyphRangeFromCharRange(index_t iCharBegin, index_t iCharEnd, index_t& iGlyphBegin, index_t& iGlyphEnd) const
{
	iGlyphBegin = GetGlyphIndexFromCharIndex(iCharBegin);
	iGlyphEnd = GetGlyphIndexFromCharIndex(iCharEnd);
}

float LineLayout::GetLineHeight() const
{
	return ceilf(mLineMetrics.mfBaseline) - floorf(mLineMetrics.mfDescent);
}

/////////////// Typesetter ///////////////

bool Typesetter::IsScheduleEmpty() const
{
	return mAnalysisEnd.mnScheduleIndex == mScheduleEnd.mnScheduleIndex;
}

void Typesetter::GetScheduleLocationFromCharIndex(index_t iChar, ScheduleLocation& scheduleLocation, bool bCharIndexIsLineRelative) const
{
	if (bCharIndexIsLineRelative)
		iChar += mnLastLineEndIndex;

	index_t nCharBase = 0;
	for (eastl_size_t i = 0, iEnd = mSchedule.size(); i != iEnd; i++)
	{
		index_t nCharEnd = nCharBase + mSchedule[i].mCount;
		if (iChar < nCharEnd)
		{
			scheduleLocation.mnScheduleIndex = i;
			scheduleLocation.mnCharBase = nCharBase;
			scheduleLocation.mnCharOffset = iChar - nCharBase;
			return;
		}
		nCharBase = nCharEnd;
	}
	scheduleLocation = mScheduleEnd;
}

index_t Typesetter::ScheduleLocation::GetCharIndex() const
{
	return mnCharBase + mnCharOffset;
}

/////////////// Bidi ///////////////

bool BidiClassify(const Char* pText, AnalysisInfo* pAnalysisInfoArray, size_t count)
{
	bool bRTL = false;
	const Char* pEnd = pText + count;
	for (; pText != pEnd; ++pText, ++pAnalysisInfoArray)
	{
		BidiClass bidiClass = GetBidiClass(*pText);
		if (bidiClass == kBidiClassR || bidiClass == kBidiClassAL)
			bRTL = true;
		switch (bidiClass)
		{
		default:
			pAnalysisInfoArray->mBidiClass = bidiClass;
			break;
		case kBidiClassS:
		case kBidiClassWS:
		case kBidiClassB:
			pAnalysisInfoArray->mBidiClass = kBidiClassON;
			break;
		}
	}
	return bRTL;
}

void Bidi(int nBaseEmbeddingLevel, const Char* pText, AnalysisInfo* pAnalysisInfoArray, size_t count)
{
	if (BidiClassify(pText, pAnalysisInfoArray, count))
	{
		BidiResolveExplicit(nBaseEmbeddingLevel, pAnalysisInfoArray, count);
		BidiResolveWeak(nBaseEmbeddingLevel, pAnalysisInfoArray, count);
		BidiResolveNeutral(nBaseEmbeddingLevel, pAnalysisInfoArray, count);
		BidiResolveImplicit(pAnalysisInfoArray, count);
	}
}

} // namespace Text
} // namespace EA
