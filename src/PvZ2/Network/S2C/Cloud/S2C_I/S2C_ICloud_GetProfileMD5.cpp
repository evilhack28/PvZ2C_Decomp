//
//  S2C_ICloud_GetProfileMD5.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ICloud_GetProfileMD5);

void S2C_ICloud_GetProfileMD5::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_ProfileMD5);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, summary, s);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, md5, m);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, lastUpdateTime, lut);
	REFLECTION_CLASSBUILDER_END(S2C_ProfileMD5);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_ICloud_GetProfileMD5);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_ProfileMD5, m_profile, pr);
	REFLECTION_CLASSBUILDER_END(S2C_ICloud_GetProfileMD5);
}
