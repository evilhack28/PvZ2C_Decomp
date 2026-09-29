//
//  AdaptorJoustLeaderboard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorJoustLeaderboard.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorJoustLeaderboard);

void AdaptorJoustLeaderboard::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorJoustLeaderboard);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorJoustLeaderboard);
}

void AdaptorJoustLeaderboard::ScrollTargetReached(ScrollWidget* i_arg)
{
}

void AdaptorJoustLeaderboard::ScrollTargetInterrupted(ScrollWidget* i_arg)
{
}
