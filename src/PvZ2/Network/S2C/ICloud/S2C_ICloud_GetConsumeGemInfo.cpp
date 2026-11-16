//
//  S2C_ICloud_GetConsumeGemInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ICloud_GetConsumeGemInfo);

void S2C_ICloud_GetConsumeGemInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_ICloud_GetConsumeGemInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlayerInfo, m_playerInfo, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_needRefreshList, nrl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_actid, oi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_ICloud_IDCount, m_item, o);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_times, times);
	REFLECTION_CLASSBUILDER_END(S2C_ICloud_GetConsumeGemInfo);
}
