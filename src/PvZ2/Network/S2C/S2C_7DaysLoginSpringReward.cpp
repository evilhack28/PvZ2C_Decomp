//
//  S2C_7DaysLoginSpringReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_7DaysLoginSpringReward);

void S2C_7DaysLoginSpringReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SpringLoginRewardBonus);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, plantID, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, nDuration, tv);
	REFLECTION_CLASSBUILDER_END(SpringLoginRewardBonus);

	REFLECTION_CLASSBUILDER_BEGIN(ExpPlantLoginConfig);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, SumDays, s);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, Rewarded, r);
	REFLECTION_CLASSBUILDER_END(ExpPlantLoginConfig);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_7DaysLoginSpringReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<SpringLoginRewardBonus>, m_vecRewardBonus, bonus);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<ExpPlantLoginConfig>, m_loginConfigs, lds);
	REFLECTION_CLASSBUILDER_END(S2C_7DaysLoginSpringReward);

}
