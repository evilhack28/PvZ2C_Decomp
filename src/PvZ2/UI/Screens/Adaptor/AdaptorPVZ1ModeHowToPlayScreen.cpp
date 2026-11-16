//
//  AdaptorPVZ1ModeHowToPlayScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorPVZ1ModeHowToPlayScreen.h"

AdaptorPVZ1ModeHowToPlayScreen::AdaptorPVZ1ModeHowToPlayScreen()
{
}

AdaptorPVZ1ModeHowToPlayScreen::~AdaptorPVZ1ModeHowToPlayScreen()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorPVZ1ModeHowToPlayScreen);

void AdaptorPVZ1ModeHowToPlayScreen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorPVZ1ModeHowToPlayScreen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HowToPlayScreen);

	REFLECTION_CLASSBUILDER_END(AdaptorPVZ1ModeHowToPlayScreen);
}
