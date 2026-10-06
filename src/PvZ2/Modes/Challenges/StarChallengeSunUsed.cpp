//
//  StarChallengeSunUsed.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StarChallengeSunUsed.h"

StarChallengeSunUsed::~StarChallengeSunUsed()
{
}

StarChallengeSunUsedProps::~StarChallengeSunUsedProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeSunUsed);

void StarChallengeSunUsed::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeSunUsed);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Challenge);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_sunSpent);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<UIWidget>, m_sunCounterWidget);
	REFLECTION_CLASSBUILDER_END(StarChallengeSunUsed);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeSunUsedProps);

void StarChallengeSunUsedProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeSunUsedProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(int, MaximumSun);
	REFLECTION_CLASSBUILDER_END(StarChallengeSunUsedProps);
}
