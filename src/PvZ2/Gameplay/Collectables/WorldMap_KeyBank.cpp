//
//  WorldMap_KeyBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_KeyBank.h"

void WorldMap_KeyBank::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_KeyBank);

void WorldMap_KeyBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_KeyBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_KeyBank);
}

void WorldMap_KeyBank::Draw(Graphics* i_arg)
{
}
