//
//  S2C_PVP128Data.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

S2C_PVP128Data::S2C_PVP128Data()
    : m_gem(0)
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PVP128Data);

void S2C_PVP128Data::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_PVP128Data);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_gem, c);
	REFLECTION_CLASSBUILDER_END(S2C_PVP128Data);
}
