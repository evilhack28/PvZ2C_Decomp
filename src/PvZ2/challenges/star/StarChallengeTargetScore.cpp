//
//  StarChallengeTargetScore.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StarChallengeTargetScore.h"

StarChallengeTargetScore::~StarChallengeTargetScore()
{
}

StarChallengeTargetScoreProps::~StarChallengeTargetScoreProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeTargetScore);

void StarChallengeTargetScore::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeTargetScore);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Challenge);

		REFLECTION_CLASSBUILDER_FIELD(float, m_currentScore);
	REFLECTION_CLASSBUILDER_END(StarChallengeTargetScore);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeTargetScoreProps);

void StarChallengeTargetScoreProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeTargetScoreProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(float, TargetScore);
	REFLECTION_CLASSBUILDER_END(StarChallengeTargetScoreProps);
}
