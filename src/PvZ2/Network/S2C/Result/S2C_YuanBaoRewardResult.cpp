//
//  S2C_YuanBaoRewardResult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_YuanBaoRewardResult);

void S2C_YuanBaoRewardResult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_WechatReward);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, ObjectId, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, Quantity, q);
	REFLECTION_CLASSBUILDER_END(S2C_WechatReward);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_YuanBaoRewardResult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_WechatReward>, m_rewardList, b);
	REFLECTION_CLASSBUILDER_END(S2C_YuanBaoRewardResult);

}
