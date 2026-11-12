//
//  S2C_7DaysLoginReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_7DaysLoginReward);

void S2C_7DaysLoginReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NDLoginRewardBonus);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, BonusId, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, Quantity, q);
	REFLECTION_CLASSBUILDER_END(NDLoginRewardBonus);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_7DaysLoginReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<NDLoginRewardBonus>, m_vecRewardBonus, bl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, awardDay, dk);
	REFLECTION_CLASSBUILDER_END(S2C_7DaysLoginReward);

}
