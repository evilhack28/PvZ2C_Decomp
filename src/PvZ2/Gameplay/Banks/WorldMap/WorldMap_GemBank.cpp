//
//  WorldMap_GemBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_GemBank.h"

void WorldMap_GemBank::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_GemBank);

void WorldMap_GemBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_GemBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GemBank);

	REFLECTION_CLASSBUILDER_END(WorldMap_GemBank);
}
