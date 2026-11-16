//
//  WorldMap_AlmanacButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_AlmanacButton.h"

void WorldMap_AlmanacButton::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_AlmanacButton);

void WorldMap_AlmanacButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_AlmanacButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_AlmanacButton);
}
