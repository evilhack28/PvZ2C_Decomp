//
//  S2C_ICloud_SignReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ICloud_SignReward);

void S2C_ICloud_SignReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_DailySignContent);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, itemId, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, amount, q);
	REFLECTION_CLASSBUILDER_END(S2C_DailySignContent);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_DailySign);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, m_loginCount, mlc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_lastRequestTime, lct);
	REFLECTION_CLASSBUILDER_END(S2C_DailySign);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_ICloud_SignReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, m_needRefreshList, nrl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_DailySign, m_dailySign, ds);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, m_dateList, gdl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_DailySignContent>, m_rewardList, bl);
	REFLECTION_CLASSBUILDER_END(S2C_ICloud_SignReward);
}
