//
//  SpeedChange.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SpeedChange.h"

void SpeedChange::unregisterForEvents()
{
}

void SpeedChange::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SpeedChange);

void SpeedChange::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SpeedChange);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(SpeedChange);
}
