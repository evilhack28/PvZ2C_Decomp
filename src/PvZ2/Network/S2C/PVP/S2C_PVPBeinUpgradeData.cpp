//
//  S2C_PVPBeinUpgradeData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

S2C_PVPBeinUpgradeData::S2C_PVPBeinUpgradeData()
{
	m_coin = 0;
	m_medal = 0;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PVPBeinUpgradeData);

void S2C_PVPBeinUpgradeData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_PVPBeinUpgradeData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_coin, ag);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_medal, am);
	REFLECTION_CLASSBUILDER_END(S2C_PVPBeinUpgradeData);

}
