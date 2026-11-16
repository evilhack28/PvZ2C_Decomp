//
//  S2C_ICloud_GetGachaInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ICloud_GetGachaInfo);

void S2C_ICloud_GetGachaInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_GachaInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, profileId, pi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, lastFreeTime, lft);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, isFirstPaidDrawDone, fpd);
	REFLECTION_CLASSBUILDER_END(S2C_GachaInfo);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_ICloud_GetGachaInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(S2C_GachaInfo, gachaInfo, g);
	REFLECTION_CLASSBUILDER_END(S2C_ICloud_GetGachaInfo);
}
