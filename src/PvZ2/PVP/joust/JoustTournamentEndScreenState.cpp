//
//  JoustTournamentEndScreenState.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "JoustTournamentEndScreenState.h"

JoustTournamentEndScreenState::JoustTournamentEndScreenState()
{
}

JoustTournamentEndScreenState::~JoustTournamentEndScreenState()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JoustTournamentEndScreenState);

void JoustTournamentEndScreenState::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JoustTournamentEndScreenState);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PVZHotUIGameState);

	REFLECTION_CLASSBUILDER_END(JoustTournamentEndScreenState);
}

#include "AdaptorJoustTourneyResultsScreen.h"
RtClass* JoustTournamentEndScreenState::getHotUIAdaptorClass()
{
	return AdaptorJoustTourneyResultsScreen::StaticGetClass();
}
