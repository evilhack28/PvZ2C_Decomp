//
//  AdaptorJoustScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorJoustScreen.h"

bool AdaptorJoustScreen::isEASquaredForTicketsAvailable()
{
	return false;
}

AdaptorJoustScreen::AdaptorJoustScreen()
{
	m_leaderboard = 0;
	m_matchmakingScreen = 0;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorJoustScreen);

void AdaptorJoustScreen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorJoustScreen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorJoustScreen);
}

#include "AdaptorJoustScreen.h"
void AdaptorJoustScreen::onHowToPlayTapped()
{
	 AdaptorJoustScreen::showHowToPlayScreen();
}

#include "AdaptorJoustScreen.h"
void AdaptorJoustScreen::onEASquaredAdFinished(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason)
{
	 AdaptorJoustScreen::updateEASquaredForTicketsVisible();
}

#include "AdaptorJoustScreen.h"
void AdaptorJoustScreen::onLinkToUIViewCreated()
{
	 AdaptorJoustScreen::setup();
}
