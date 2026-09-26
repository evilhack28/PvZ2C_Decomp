//
//  WorldMap_OfflineBundleButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_OfflineBundleButton.h"

void WorldMap_OfflineBundleButton::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_OfflineBundleButton);

void WorldMap_OfflineBundleButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_OfflineBundleButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_OfflineBundleButton);
}
