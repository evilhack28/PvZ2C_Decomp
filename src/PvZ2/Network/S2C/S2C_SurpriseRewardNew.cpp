//
//  S2C_SurpriseRewardNew.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_SurpriseRewardNew);

void S2C_SurpriseRewardNew::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_LeafConsume);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlayerInfo, m_playerInfo, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_objectId, oi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_quantity, q);
	REFLECTION_CLASSBUILDER_END(S2C_LeafConsume);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_SurpriseRewardNew);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_LeafConsume, m_plantSurpriseInfo, cl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlayerInfo, m_playerInfo, p);
	REFLECTION_CLASSBUILDER_END(S2C_SurpriseRewardNew);

}
