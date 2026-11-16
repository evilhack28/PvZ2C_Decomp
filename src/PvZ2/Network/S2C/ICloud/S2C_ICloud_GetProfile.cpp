//
//  S2C_ICloud_GetProfile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ICloud_GetProfile);

void S2C_ICloud_GetProfile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_Profile);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, userId, ui);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, profile, p);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, md5, m5);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, lastUpdateTime, lut);
	REFLECTION_CLASSBUILDER_END(S2C_Profile);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_ICloud_GetProfile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_Profile, m_profile, pr);
	REFLECTION_CLASSBUILDER_END(S2C_ICloud_GetProfile);
}
