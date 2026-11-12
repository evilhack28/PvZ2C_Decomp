//
//  S2C_StopExplore.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_StopExplore);

void S2C_StopExplore::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_StopExplore);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, diamondLess, d);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<S2C_Explore_Team>, m_teamList, e);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlayerInfo, m_playerInfo, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_flag, f);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_adCount, times);
	REFLECTION_CLASSBUILDER_END(S2C_StopExplore);

}
