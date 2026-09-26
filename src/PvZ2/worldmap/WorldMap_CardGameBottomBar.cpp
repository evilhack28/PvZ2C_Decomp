//
//  WorldMap_CardGameBottomBar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_CardGameBottomBar.h"

void WorldMap_CardGameBottomBar::onUpdate()
{
}

WorldMap_CardGameBottomBar::~WorldMap_CardGameBottomBar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_CardGameBottomBar);

void WorldMap_CardGameBottomBar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_CardGameBottomBar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_CardGameBottomBar);
}
