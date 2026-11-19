//
//  ChallengeModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "ChallengeModule.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ChallengeModule);

void ChallengeModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ChallengeModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_challengesWereCompleted);
	REFLECTION_CLASSBUILDER_END(ChallengeModule);
}

RT_CLASS_IMPLEMENT(ChallengeModuleProperties);

void ChallengeModule::GatherDependentModulePropertySheets(std::vector<LevelModulePropertiesPtr>& i_arg)
{
}

void ChallengeModule::getChallenges(std::vector<Challenge*>& o_challenges)
{
	getActiveChallenges(o_challenges);
}
