//
//  WorldSpecificDangerRoomProperties.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "DangerRoomModule.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldSpecificDangerRoomProperties);

void WorldSpecificDangerRoomProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldSpecificDangerRoomProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_END(WorldSpecificDangerRoomProperties);
}
