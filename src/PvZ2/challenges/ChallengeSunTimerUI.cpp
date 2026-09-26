//
//  ChallengeSunTimerUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ChallengeSunTimerUI.h"

ChallengeSunTimerUI::~ChallengeSunTimerUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ChallengeSunTimerUI);

void ChallengeSunTimerUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ChallengeSunTimerUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ChallengeUI);

	REFLECTION_CLASSBUILDER_FIELD(int, m_seconds);

	REFLECTION_CLASSBUILDER_END(ChallengeSunTimerUI);
}

void ChallengeSunTimerUI::SetSeconds(int i_arg)
{
	m_seconds = i_arg;
}
