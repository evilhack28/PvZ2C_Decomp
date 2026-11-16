//
//  WorldMap_WorldKeyBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_WorldKeyBank.h"

WorldMap_WorldKeyBank::WorldMap_WorldKeyBank()
{
}

WorldMap_WorldKeyBank::~WorldMap_WorldKeyBank()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_WorldKeyBank);

void WorldMap_WorldKeyBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_WorldKeyBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_WorldKeyBank);
}
