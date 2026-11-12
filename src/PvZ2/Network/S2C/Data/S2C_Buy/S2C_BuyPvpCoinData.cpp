//
//  S2C_BuyPvpCoinData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

S2C_BuyPvpCoinData::S2C_BuyPvpCoinData() : m_diamond(0), m_pvpCoin(0)
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_BuyPvpCoinData);

void S2C_BuyPvpCoinData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_BuyPvpCoinData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_diamond, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_pvpCoin, ag);
	REFLECTION_CLASSBUILDER_END(S2C_BuyPvpCoinData);

}
