//
//  ButtonWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "ButtonWidget.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ButtonWidget);

void ButtonWidget::OnPressed()
{
}

void ButtonWidget::SetFont(PrimeTypeface* theFont)
{
	mPrimeFont = theFont;
}
