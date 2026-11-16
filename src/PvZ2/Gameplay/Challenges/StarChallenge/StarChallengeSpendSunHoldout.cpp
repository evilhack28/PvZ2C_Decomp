//
//  StarChallengeSpendSunHoldout.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StarChallengeSpendSunHoldout.h"

StarChallengeSpendSunHoldout::~StarChallengeSpendSunHoldout()
{
}

StarChallengeSpendSunHoldoutProps::~StarChallengeSpendSunHoldoutProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeSpendSunHoldout);

void StarChallengeSpendSunHoldout::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeSpendSunHoldout);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Challenge);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_lastSunSpentTime);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<UIWidget>, m_sunCounterWidget);
	REFLECTION_CLASSBUILDER_END(StarChallengeSpendSunHoldout);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeSpendSunHoldoutProps);

void StarChallengeSpendSunHoldoutProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeSpendSunHoldoutProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(int, HoldoutSeconds);
	REFLECTION_CLASSBUILDER_END(StarChallengeSpendSunHoldoutProps);
}
