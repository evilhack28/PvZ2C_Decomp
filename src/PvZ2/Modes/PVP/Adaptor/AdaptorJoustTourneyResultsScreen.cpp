//
//  AdaptorJoustTourneyResultsScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorJoustTourneyResultsScreen.h"

AdaptorJoustTourneyResultsScreen::~AdaptorJoustTourneyResultsScreen()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorJoustTourneyResultsScreen);

void AdaptorJoustTourneyResultsScreen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorJoustTourneyResultsScreen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorJoustTourneyResultsScreen);
}

#include "AdaptorJoustTourneyResultsScreen.h"
void AdaptorJoustTourneyResultsScreen::onLinkToUIViewCreated()
{
	 AdaptorJoustTourneyResultsScreen::setup();
}
