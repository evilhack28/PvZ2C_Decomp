//
//  StarChallengeModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "StarChallengeModule.h"

StarChallengeModule::StarChallengeModule()
{
}

StarChallengeModule::~StarChallengeModule()
{
}

StarChallengeModuleProperties::~StarChallengeModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeModule);

void StarChallengeModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BaseChallengeModule);

	REFLECTION_CLASSBUILDER_END(StarChallengeModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeModuleProperties);

void StarChallengeModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BaseChallengeModuleProperties);

	REFLECTION_CLASSBUILDER_END(StarChallengeModuleProperties);
}
