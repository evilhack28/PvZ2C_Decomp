//
//  WorldMap_UnchartedBottomBar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_UnchartedBottomBar.h"

void WorldMap_UnchartedBottomBar::onUpdate()
{
}

WorldMap_UnchartedBottomBar::~WorldMap_UnchartedBottomBar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_UnchartedBottomBar);

void WorldMap_UnchartedBottomBar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_UnchartedBottomBar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_UnchartedBottomBar);
}
