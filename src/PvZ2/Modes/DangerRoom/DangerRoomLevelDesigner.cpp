//
//  DangerRoomLevelDesigner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DangerRoomLevelDesigner.h"

DangerRoomLevelDesigner::DangerRoomLevelDesigner()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DangerRoomLevelDesigner);

void DangerRoomLevelDesigner::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DangerRoomLevelDesigner);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_END(DangerRoomLevelDesigner);
}
