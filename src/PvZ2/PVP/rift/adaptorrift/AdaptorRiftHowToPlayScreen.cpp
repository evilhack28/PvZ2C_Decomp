//
//  AdaptorRiftHowToPlayScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorRiftHowToPlayScreen.h"

AdaptorRiftHowToPlayScreen::AdaptorRiftHowToPlayScreen()
{
}

AdaptorRiftHowToPlayScreen::~AdaptorRiftHowToPlayScreen()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorRiftHowToPlayScreen);

void AdaptorRiftHowToPlayScreen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorRiftHowToPlayScreen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HowToPlayScreen);

	REFLECTION_CLASSBUILDER_END(AdaptorRiftHowToPlayScreen);
}
