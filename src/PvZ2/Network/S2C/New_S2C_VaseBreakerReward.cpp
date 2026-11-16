//
//  New_S2C_VaseBreakerReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"
#include "ReflectionBuilder.h"

#include "DailyAchievement.h"

New_S2C_VaseBreakerReward::New_S2C_VaseBreakerReward()
{
}

New_S2C_VaseBreakerReward::~New_S2C_VaseBreakerReward()
{
}

void New_S2C_VaseBreakerReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_VaseBreakerReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(NetworkRewardContent, m_reward, b);
	REFLECTION_CLASSBUILDER_END(New_S2C_VaseBreakerReward);
}

RT_CLASS_IMPLEMENT(New_S2C_VaseBreakerReward);
