//
//  AdaptorRiftLeaderBoardScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorRiftLeaderBoardScreen.h"

AdaptorRiftLeaderBoardScreen::AdaptorRiftLeaderBoardScreen()
{
	m_leaderboard = 0;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorRiftLeaderBoardScreen);

void AdaptorRiftLeaderBoardScreen::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorRiftLeaderBoardScreen);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorRiftLeaderBoardScreen);
}

#include "AdaptorRiftLeaderBoardScreen.h"
void AdaptorRiftLeaderBoardScreen::onLinkToUIViewCreated()
{
	 AdaptorRiftLeaderBoardScreen::setup();
}
