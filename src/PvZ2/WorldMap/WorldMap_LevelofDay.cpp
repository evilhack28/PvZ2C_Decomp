//
//  WorldMap_LevelofDay.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_LevelofDay.h"

void WorldMap_LevelofDay::onUpdate()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_LevelofDay);

void WorldMap_LevelofDay::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_LevelofDay);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_LevelofDay);
}

#include "WorldMap_LevelofDay.h"
void WorldMap_LevelofDay::OnWorldLoaded()
{
	 WorldMap_LevelofDay::CheckActivated();
}

void WorldMap_LevelofDay::initLoadingResourcesGroupList()
{
}
