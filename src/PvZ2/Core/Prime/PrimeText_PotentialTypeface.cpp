//
//  PrimeText_PotentialTypeface.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PrimeText_PotentialTypeface.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PrimeText_PotentialTypeface);

/////////////// Typeface ///////////////

__attribute__((noclone, noinline)) static int UIScaleNum(int i_num)
{
    return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

PrimeTypeface* PrimeText_PotentialTypeface::Typeface()
{
    if (!m_Typeface)
    {
        EA::Text::TextStyle style;
        style = PrimeText::Instance()->TextStyle_Create(Sexy::StringToSexyString(Font), UIScaleNum(Size), Sexy::Color(Color));
        style.mEffectColor = EffectColor;
        style.mSmooth = (EA::Text::Smooth)!Smooth;
        style.mEffect = Effect;
        m_Typeface = PrimeText::Instance()->Typeface(style);
        if (!FontIfShrunk.empty())
            m_Typeface->SetTypefaceIfShrunk(PrimeText_PotentialTypefaceDictionary::GetTypeface(FontIfShrunk));
    }
    return m_Typeface;
}
