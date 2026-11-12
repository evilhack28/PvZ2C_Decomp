//
//  S2C_ChristmasRebate.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ChristmasRebate);

void S2C_ChristmasRebate::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RebateRewardItem);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iObjectId, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, iCount, q);
	REFLECTION_CLASSBUILDER_END(RebateRewardItem);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_ChristmasRebate);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(RebateRewardItem, m_PlantItem, pl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(RebateRewardItem, m_AvatarItem, dl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, m_vStateFlag, rb);
	REFLECTION_CLASSBUILDER_END(S2C_ChristmasRebate);
}
