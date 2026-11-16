//
//  UIWidgetPrimeText.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "UIWidgetPrimeText.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(UIWidgetPrimeText);

void UIWidgetPrimeText::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(UIWidgetPrimeText);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(UIWidgetPrimeText);
}

UIWidgetPrimeText::UIWidgetPrimeText()
{
	mGlyphMesh = 0;
}
