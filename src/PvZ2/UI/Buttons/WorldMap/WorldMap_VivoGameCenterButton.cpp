//
//  WorldMap_VivoGameCenterButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_VivoGameCenterButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_VivoGameCenterButton);

void WorldMap_VivoGameCenterButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_VivoGameCenterButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_VivoGameCenterButton);
}

#include "WorldMap_VivoGameCenterButton.h"
void WorldMap_VivoGameCenterButton::onWorldLoaded()
{
	 WorldMap_VivoGameCenterButton::CheckActivated();
}
