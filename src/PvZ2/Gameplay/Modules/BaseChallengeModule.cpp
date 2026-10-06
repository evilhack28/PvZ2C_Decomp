//
//  BaseChallengeModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "BaseChallengeModule.h"

BaseChallengeModule::BaseChallengeModule()
{
}

BaseChallengeModule::~BaseChallengeModule()
{
}

BaseChallengeModuleProperties::~BaseChallengeModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BaseChallengeModule);

void BaseChallengeModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BaseChallengeModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ChallengeModule);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_challengesActive);
	REFLECTION_CLASSBUILDER_END(BaseChallengeModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BaseChallengeModuleProperties);

void BaseChallengeModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BaseChallengeModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ChallengeModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, Difficulties);
		REFLECTION_CLASSBUILDER_FIELD(bool, ChallengesAlwaysAvailable);
	REFLECTION_CLASSBUILDER_END(BaseChallengeModuleProperties);
}
