//
//  WorldMap_TopBar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_TopBar.h"

WorldMap_TopBar::WorldMap_TopBar()
{
}

WorldMap_TopBar::~WorldMap_TopBar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_TopBar);

void WorldMap_TopBar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_TopBar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_TopBar);
}
