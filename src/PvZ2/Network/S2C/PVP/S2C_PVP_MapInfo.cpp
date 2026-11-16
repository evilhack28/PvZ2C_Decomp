//
//  S2C_PVP_MapInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PVP_MapInfo);

void S2C_PVP_MapInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_PVP_ZombieInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, zombieId, zi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, num, n);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, level, l);
	REFLECTION_CLASSBUILDER_END(S2C_PVP_ZombieInfo);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_PVP_MapInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, unlockPrice, up);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_PVP_BigMapInfo>, m_mapInfoList, ml);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_PVP_ZombieInfo>, m_zombieInfoList, zl);
	REFLECTION_CLASSBUILDER_END(S2C_PVP_MapInfo);

}
