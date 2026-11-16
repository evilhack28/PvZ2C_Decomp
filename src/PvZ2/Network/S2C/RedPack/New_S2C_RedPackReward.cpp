//
//  New_S2C_RedPackReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"
#include "ReflectionBuilder.h"

#include "UIRedPacket.h"

New_S2C_RedPackReward::New_S2C_RedPackReward()
{
}

New_S2C_RedPackReward::~New_S2C_RedPackReward()
{
}

New_S2C_RedPackReward& New_S2C_RedPackReward::operator=(const New_S2C_RedPackReward& i_other) = default;

void New_S2C_RedPackReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_RedPackSth);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int32, itemId, i);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int32, amount, q);
	REFLECTION_CLASSBUILDER_END(New_S2C_RedPackSth);

	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_RedPackReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int32, m_redpackCount, n);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<New_S2C_RedPackSth>, m_prizeInfos, il);
	REFLECTION_CLASSBUILDER_END(New_S2C_RedPackReward);
}

RT_CLASS_IMPLEMENT(New_S2C_RedPackReward);
