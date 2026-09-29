//
//  AdaptorJoustResultsScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorJoustResultsScreen.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorJoustResultsScreen);

void AdaptorJoustResultsScreen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorJoustResultsScreen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorJoustResultsScreen);
}

#include "AdaptorJoustResultsScreen.h"
void AdaptorJoustResultsScreen::onLinkToUIViewCreated()
{
	 AdaptorJoustResultsScreen::setup();
}
