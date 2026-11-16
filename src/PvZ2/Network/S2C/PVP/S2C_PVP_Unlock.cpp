//
//  S2C_PVP_Unlock.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PVP_Unlock);

void S2C_PVP_Unlock::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_PVP_Unlock);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_gold, ag);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_unlockPrice, up);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_PVP_BigMapInfo>, m_mapInfoList, ml);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_PVP_BigMapPVPInfo>, m_mapPVPInfoList, mpl);
	REFLECTION_CLASSBUILDER_END(S2C_PVP_Unlock);

}
