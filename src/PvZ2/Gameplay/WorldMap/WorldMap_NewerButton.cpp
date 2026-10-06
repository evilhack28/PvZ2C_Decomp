//
//  WorldMap_NewerButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_NewerButton.h"

void WorldMap_NewerButton::initLoadingResourcesGroupList()
{
}

void WorldMap_NewerButton::onUpdate()
{
}

WorldMap_NewerButton::WorldMap_NewerButton()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_NewerButton);

void WorldMap_NewerButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_NewerButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_NewerButton);
}
