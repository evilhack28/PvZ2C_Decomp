//
//  S2C_PVP_ChangeEnemy.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PVP_ChangeEnemy);

void S2C_PVP_ChangeEnemy::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_PVP_ChangeEnemy);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_gold, ag);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PVP_BigMapInfo, m_mapInfo, ml);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PVP_BigMapPVPInfo, m_mapPVPInfo, mpl);
	REFLECTION_CLASSBUILDER_END(S2C_PVP_ChangeEnemy);

}
