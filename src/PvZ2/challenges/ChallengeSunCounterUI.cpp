//
//  ChallengeSunCounterUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ChallengeSunCounterUI.h"

ChallengeSunCounterUI::~ChallengeSunCounterUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ChallengeSunCounterUI);

void ChallengeSunCounterUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ChallengeSunCounterUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ChallengeUI);

	REFLECTION_CLASSBUILDER_END(ChallengeSunCounterUI);
}
