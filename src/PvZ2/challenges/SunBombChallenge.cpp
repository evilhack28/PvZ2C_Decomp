//
//  SunBombChallenge.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SunBombChallenge.h"

SunBombChallengeProperties::~SunBombChallengeProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SunBombChallengeProperties);

void SunBombChallengeProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SunBombChallengeProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(SunBombChallengeProperties);
}
