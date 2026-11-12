//
//  S2C_PVPCompleteUpgradeData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

S2C_PVPCompleteUpgradeData::S2C_PVPCompleteUpgradeData() : m_id(0), m_level(0), m_id2(0), m_gem(0)
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PVPCompleteUpgradeData);

void S2C_PVPCompleteUpgradeData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_PVPCompleteUpgradeData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_id, t);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_level, nl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_id2, id);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_gem, p);
	REFLECTION_CLASSBUILDER_END(S2C_PVPCompleteUpgradeData);

}
