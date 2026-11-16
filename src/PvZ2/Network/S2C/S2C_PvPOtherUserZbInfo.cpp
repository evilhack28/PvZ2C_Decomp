//
//  S2C_PvPOtherUserZbInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PvPOtherUserZbInfo);

void S2C_PvPOtherUserZbInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_PvPOtherUserZbInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int64, m_profileId, qpi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_PVP_ZombieInfo>, m_zbInfoList, zi);
	REFLECTION_CLASSBUILDER_END(S2C_PvPOtherUserZbInfo);

}
