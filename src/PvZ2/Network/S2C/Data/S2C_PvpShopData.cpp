//
//  S2C_PvpShopData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PvpShopData);

void S2C_PvpShopData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVPCUPData);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_iObjId, oi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_iQuantity, q);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_iPrice, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_iState, s);
	REFLECTION_CLASSBUILDER_END(PVPCUPData);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_PvpShopData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<PVPCUPData>, m_shopDataList, cs);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_refreshCost, rf);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_leftPvpCoin, ag);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_leftPvpMetal, am);
	REFLECTION_CLASSBUILDER_END(S2C_PvpShopData);

}
