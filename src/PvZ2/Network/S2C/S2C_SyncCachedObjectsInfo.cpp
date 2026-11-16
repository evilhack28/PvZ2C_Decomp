//
//  S2C_SyncCachedObjectsInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_SyncCachedObjectsInfo);

void S2C_SyncCachedObjectsInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_SyncCachedObjectsInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, m_nfc, nfc);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, m_gold, g);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, m_gems, gem);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_BonusInfo>, m_bonusList, bl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_PlantPendantInfo>, m_pendantInfo, pl);
	REFLECTION_CLASSBUILDER_END(S2C_SyncCachedObjectsInfo);

}
