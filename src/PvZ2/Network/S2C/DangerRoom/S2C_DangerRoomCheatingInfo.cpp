//
//  S2C_DangerRoomCheatingInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_DangerRoomCheatingInfo);

void S2C_DangerRoomCheatingInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TinyCheatPlantInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, plantId, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, level, s);
	REFLECTION_CLASSBUILDER_END(TinyCheatPlantInfo);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_DangerRoomCheatingInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<TinyCheatPlantInfo>, m_plantList, pl);
	REFLECTION_CLASSBUILDER_END(S2C_DangerRoomCheatingInfo);

}
