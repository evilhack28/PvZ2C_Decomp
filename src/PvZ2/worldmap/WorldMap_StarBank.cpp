//
//  WorldMap_StarBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_StarBank.h"

void WorldMap_StarBank::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_StarBank);

void WorldMap_StarBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_StarBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_StarBank);
}

void WorldMap_StarBank::Draw(Graphics* i_arg)
{
}
