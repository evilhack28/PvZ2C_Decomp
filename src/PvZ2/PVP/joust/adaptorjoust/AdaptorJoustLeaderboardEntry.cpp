//
//  AdaptorJoustLeaderboardEntry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorJoustLeaderboardEntry.h"

void AdaptorJoustLeaderboardEntry::onLinkToUIViewCreated()
{
}

AdaptorJoustLeaderboardEntry::~AdaptorJoustLeaderboardEntry()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorJoustLeaderboardEntry);

void AdaptorJoustLeaderboardEntry::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorJoustLeaderboardEntry);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorJoustLeaderboardEntry);
}

#include "HotUIAdaptor.h"
void AdaptorJoustLeaderboardEntry::onLayoutFinished()
{
	 HotUIAdaptor::GetEntryPointWidget();
}
