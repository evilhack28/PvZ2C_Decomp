//
//  AdaptorRiftTourneyResultsScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorRiftTourneyResultsScreen.h"

void AdaptorRiftTourneyResultsScreen::sendTournamentRegistrationRequest()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorRiftTourneyResultsScreen);

void AdaptorRiftTourneyResultsScreen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorRiftTourneyResultsScreen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorRiftTourneyResultsScreen);
}

#include "AdaptorRiftTourneyResultsScreen.h"
void AdaptorRiftTourneyResultsScreen::onLinkToUIViewCreated()
{
	 AdaptorRiftTourneyResultsScreen::setup();
}
