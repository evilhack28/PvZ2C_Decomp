//
//  S2C_LimitLotteryReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_LimitLotteryReward);

void S2C_LimitLotteryReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NDLoginRewardBonus);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, BonusId, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, Quantity, q);
	REFLECTION_CLASSBUILDER_END(NDLoginRewardBonus);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_LimitLotteryReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, crystalAmounts, cn);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<NDLoginRewardBonus>, normalBonus, nb);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<NDLoginRewardBonus>, rareBonus, rb);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<NDLoginRewardBonus>, cupBonus, cb);
	REFLECTION_CLASSBUILDER_END(S2C_LimitLotteryReward);

}
