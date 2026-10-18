//
//  New_S2C_GiftBoxReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"
#include "ReflectionBuilder.h"

#include "VaseBreakerModule.h"

New_S2C_GiftBoxReward::New_S2C_GiftBoxReward()
{
}

New_S2C_GiftBoxReward::~New_S2C_GiftBoxReward()
{
}

void New_S2C_GiftBoxReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_Reward);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int32, itemId, i);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int32, amount, q);
	REFLECTION_CLASSBUILDER_END(New_S2C_Reward);

	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_GiftBoxReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<New_S2C_Reward>, m_rewardInfos, rds);
	REFLECTION_CLASSBUILDER_END(New_S2C_GiftBoxReward);
}

RT_CLASS_IMPLEMENT(New_S2C_GiftBoxReward);
