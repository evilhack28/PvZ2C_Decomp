//
//  S2C_InstanceStatus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_InstanceStatus);

void S2C_InstanceStatus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_InstanceStatus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_instantId, ii);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_remainNum, s);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_queryStatus, a);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_gem, g);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_PlayerInfo, m_playerInfo, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_leftBuyTimes, lbt);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_adTimes, times);
	REFLECTION_CLASSBUILDER_END(S2C_InstanceStatus);

}
