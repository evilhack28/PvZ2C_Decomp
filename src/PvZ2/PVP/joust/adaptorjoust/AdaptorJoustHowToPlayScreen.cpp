//
//  AdaptorJoustHowToPlayScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorJoustHowToPlayScreen.h"

void AdaptorJoustHowToPlayScreen::onLayoutFinished()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorJoustHowToPlayScreen);

void AdaptorJoustHowToPlayScreen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorJoustHowToPlayScreen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorJoustHowToPlayScreen);
}
