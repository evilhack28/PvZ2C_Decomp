//
//  S2C_BuyPvpShopData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_BuyPvpShopData);

void S2C_BuyPvpShopData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PvpShopBuyItem);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_iObjectId, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_iCount, q);
	REFLECTION_CLASSBUILDER_END(PvpShopBuyItem);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_BuyPvpShopData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<PvpShopBuyItem>, m_buyList, b);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_leftPvpCoin, ag);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_leftPvpMetal, am);
	REFLECTION_CLASSBUILDER_END(S2C_BuyPvpShopData);

}
