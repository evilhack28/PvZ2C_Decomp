//
//  New_S2C_BuyCardGameReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"
#include "ReflectionBuilder.h"

#include "UICardGameReward.h"

New_S2C_BuyCardGameReward::New_S2C_BuyCardGameReward()
{
}

New_S2C_BuyCardGameReward::~New_S2C_BuyCardGameReward()
{
}

void New_S2C_BuyCardGameReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_BuyCardGameReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<S2C_BonusInfo>, BonusList, bonus);
	REFLECTION_CLASSBUILDER_END(New_S2C_BuyCardGameReward);
}

RT_CLASS_IMPLEMENT(New_S2C_BuyCardGameReward);
