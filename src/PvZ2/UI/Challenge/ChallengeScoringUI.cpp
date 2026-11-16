//
//  ChallengeScoringUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ChallengeScoringUI.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ChallengeScoringUI);

void ChallengeScoringUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ChallengeScoringUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ChallengeUI);

		REFLECTION_CLASSBUILDER_FIELD(ScoreType, m_score);
		REFLECTION_CLASSBUILDER_FIELD(int, m_multiplier);
	REFLECTION_CLASSBUILDER_END(ChallengeScoringUI);
}
