//
//  S2C_BillingReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_BillingReward);

void S2C_BillingReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LotteryBonus);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, BonusId, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, Quantity, q);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, Weight, w);
	REFLECTION_CLASSBUILDER_END(LotteryBonus);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_BillingReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<LotteryBonus>, billList, bl);
	REFLECTION_CLASSBUILDER_END(S2C_BillingReward);

}
