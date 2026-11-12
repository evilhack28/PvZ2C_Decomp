//
//  S2C_StoneLotteryReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_StoneLotteryReward);

void S2C_StoneLotteryReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LotteryBonus);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, BonusId, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, Quantity, q);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, Weight, w);
	REFLECTION_CLASSBUILDER_END(LotteryBonus);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_StoneLotteryReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, Period, pd);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, OncePay, onp);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, LeftChance, lgt);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, TotalChance, tcn);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, IsFirstToLottery, ift);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(LotteryBonus, Bonus, b);
	REFLECTION_CLASSBUILDER_END(S2C_StoneLotteryReward);

}
