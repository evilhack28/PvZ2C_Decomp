//
//  UIPVZ1ModeHowToPlayButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "UIPVZ1ModeHowToPlayButton.h"

UIPVZ1ModeHowToPlayButton::~UIPVZ1ModeHowToPlayButton()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(UIPVZ1ModeHowToPlayButton);

void UIPVZ1ModeHowToPlayButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(UIPVZ1ModeHowToPlayButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(UIPVZ1ModeHowToPlayButton);
}
