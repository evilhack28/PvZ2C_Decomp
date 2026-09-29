//
//  StarChallengeLevelTimer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StarChallengeLevelTimer.h"

StarChallengeLevelTimer::StarChallengeLevelTimer()
{
}

StarChallengeLevelTimer::~StarChallengeLevelTimer()
{
}

StarChallengeLevelTimerProperties::~StarChallengeLevelTimerProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeLevelTimer);

void StarChallengeLevelTimer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeLevelTimer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Challenge);

	REFLECTION_CLASSBUILDER_END(StarChallengeLevelTimer);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeLevelTimerProperties);

void StarChallengeLevelTimerProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeLevelTimerProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(float, TimeLimit);
	REFLECTION_CLASSBUILDER_END(StarChallengeLevelTimerProperties);
}

void StarChallengeLevelTimer::onGameplayEnded()
{
}

void StarChallengeLevelTimer::onGameplayUpdate()
{
}

#include "ChallengeModule.h"
void StarChallengeLevelTimer::gameplayWinConditionTest()
{
	 Challenge::HideUI();
}
