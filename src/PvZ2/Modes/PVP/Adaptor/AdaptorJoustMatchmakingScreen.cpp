//
//  AdaptorJoustMatchmakingScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorJoustMatchmakingScreen.h"

AdaptorJoustMatchmakingScreen::~AdaptorJoustMatchmakingScreen()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorJoustMatchmakingScreen);

void AdaptorJoustMatchmakingScreen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorJoustMatchmakingScreen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorJoustMatchmakingScreen);
}
