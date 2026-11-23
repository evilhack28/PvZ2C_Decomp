//
//  LineLayout.cpp
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

/////////////// Lifecycle ///////////////

void LineLayout::Clear(bool bThisArgumentIsDeprecated)
{
    mCharScheduleIndex = 0;
    mLineCount = 0;
    NewLine();
}

void LineLayout::NewLine()
{
    mCharArray.clear();
    mAnalysisInfoArray.clear();
    NewGlyphs();
}

void LineLayout::NewGlyphs()
{
    mGlyphArray.clear();
    mGlyphInfoArray.clear();
    mGlyphLayoutInfoArray.clear();
    mGlyphIndexArray.clear();
    mCharIndexArray.clear();
    memset(&mLineMetrics, 0, sizeof(mLineMetrics));
    mbSimpleLayout = false;
}

/////////////// Layout ///////////////

void LineLayout::OffsetSegment(float fDeltaX, float fDeltaY, index_t iGlyphBegin, index_t iGlyphEnd)
{
    if (fabsf(fDeltaX) > 0.1f || fabsf(fDeltaY) > 0.1f)
    {
        GlyphLayoutInfo* p = mGlyphLayoutInfoArray.begin() + iGlyphBegin;
        GlyphLayoutInfo* pEnd = mGlyphLayoutInfoArray.begin() + iGlyphEnd;
        for (; p < pEnd; ++p)
        {
            p->mfPenX += fDeltaX;
            p->mfPenY += fDeltaY;
            p->mfX1 += fDeltaX;
            p->mfY1 += fDeltaY;
            p->mfX2 += fDeltaX;
            p->mfY2 += fDeltaY;
        }
    }
}

void LineLayout::CalculateVisibleSpace()
{
    index_t n = mLineMetrics.mnLineLength;
    while (n)
    {
        Char c = mCharArray[n - 1];
        if (c != 0x20 && c != 0xA0 && c != 0x3000)
            break;
        n--;
    }
    mLineMetrics.mnVisibleLineLength = n;
    index_t iGlyph = GetGlyphIndexFromCharIndex(n);
    if (iGlyph)
    {
        const GlyphLayoutInfo& first = mGlyphLayoutInfoArray[0];
        const GlyphLayoutInfo& last = mGlyphLayoutInfoArray[iGlyph - 1];
        float fEnd = last.mfAdvance > 0.f ? last.mfPenX + last.mfAdvance : last.mfPenX;
        mLineMetrics.mfVisibleSpace = fEnd - first.mfPenX;
    }
    else
        mLineMetrics.mfVisibleSpace = 0.f;
}

void LineLayout::Append(const LineLayout& lineLayout, int componentFlags)
{
    mLineMetrics.mnVisibleLineLength = 0;
    mLineMetrics.mnLineLength += lineLayout.mLineMetrics.mnLineLength;
    mLineMetrics.mfSpace = std::max(mLineMetrics.mfSpace, lineLayout.mLineMetrics.mfSpace);
    mLineMetrics.mfVisibleSpace = std::max(mLineMetrics.mfVisibleSpace, lineLayout.mLineMetrics.mfVisibleSpace);
    mLineMetrics.mfBaseline = std::max(mLineMetrics.mfBaseline, lineLayout.mLineMetrics.mfBaseline);
    mLineMetrics.mfDescent = std::min(mLineMetrics.mfDescent, lineLayout.mLineMetrics.mfDescent);

    if ((componentFlags & (kComponentCharArray | kComponentGlyphArray | kComponentGlyphIndexArray)) ==
        (kComponentCharArray | kComponentGlyphArray | kComponentGlyphIndexArray))
    {
        index_t nGlyphs = mGlyphArray.size();
        index_t nOld = mGlyphIndexArray.size();
        mGlyphIndexArray.insert(mGlyphIndexArray.end(), lineLayout.mGlyphIndexArray.begin(), lineLayout.mGlyphIndexArray.end());
        index_t* p = mGlyphIndexArray.begin() + nOld;
        index_t* pEnd = p + lineLayout.mGlyphIndexArray.size();
        for (; p < pEnd; ++p)
            *p += nGlyphs;
    }

    if ((componentFlags & (kComponentCharArray | kComponentGlyphArray | kComponentCharIndexArray)) ==
        (kComponentCharArray | kComponentGlyphArray | kComponentCharIndexArray))
    {
        index_t nChars = mCharArray.size();
        index_t nOld = mCharIndexArray.size();
        mCharIndexArray.insert(mCharIndexArray.end(), lineLayout.mCharIndexArray.begin(), lineLayout.mCharIndexArray.end());
        index_t* p = mCharIndexArray.begin() + nOld;
        index_t* pEnd = p + lineLayout.mCharIndexArray.size();
        for (; p < pEnd; ++p)
            *p += nChars;
    }

    if (componentFlags & kComponentCharArray)
        mCharArray += lineLayout.mCharArray;
    if (componentFlags & kComponentCharAnalysis)
        mAnalysisInfoArray.insert(mAnalysisInfoArray.end(), lineLayout.mAnalysisInfoArray.begin(), lineLayout.mAnalysisInfoArray.end());
    if (componentFlags & kComponentGlyphArray)
        mGlyphArray.insert(mGlyphArray.end(), lineLayout.mGlyphArray.begin(), lineLayout.mGlyphArray.end());
    if (componentFlags & kComponentGlyphInfoArray)
        mGlyphInfoArray.insert(mGlyphInfoArray.end(), lineLayout.mGlyphInfoArray.begin(), lineLayout.mGlyphInfoArray.end());
    if (componentFlags & kComponentGlyphLayoutInfoArray)
        mGlyphLayoutInfoArray.insert(mGlyphLayoutInfoArray.end(), lineLayout.mGlyphLayoutInfoArray.begin(), lineLayout.mGlyphLayoutInfoArray.end());
}

}
}
