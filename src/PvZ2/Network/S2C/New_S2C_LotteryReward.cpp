//
//  New_S2C_LotteryReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"
#include "ReflectionBuilder.h"

#include "FestivalEventUI.h"

New_S2C_LotteryReward::New_S2C_LotteryReward()
{
}

New_S2C_LotteryReward::~New_S2C_LotteryReward()
{
}

void New_S2C_LotteryReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_Lottery);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int32, itemId, i);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int32, amount, q);
	REFLECTION_CLASSBUILDER_END(New_S2C_Lottery);

	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_LotteryReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int32, m_plantIndex, rt);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<New_S2C_Lottery>, m_prizeInfos, b);
	REFLECTION_CLASSBUILDER_END(New_S2C_LotteryReward);
}

RT_CLASS_IMPLEMENT(New_S2C_LotteryReward);
