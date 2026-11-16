//
//  S2C_DailySignWithTW.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_DailySignWithTW);

void S2C_DailySignWithTW::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_DailySignWithTW_RewardInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_rewardType, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_count, q);
	REFLECTION_CLASSBUILDER_END(S2C_DailySignWithTW_RewardInfo);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_DailySignWithTW);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_day, d);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_DailySignWithTW_RewardInfo>, m_infos, bl);
	REFLECTION_CLASSBUILDER_END(S2C_DailySignWithTW);

}
