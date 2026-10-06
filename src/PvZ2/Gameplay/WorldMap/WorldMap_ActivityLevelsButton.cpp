//
//  WorldMap_ActivityLevelsButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_ActivityLevelsButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_ActivityLevelsButton);

void WorldMap_ActivityLevelsButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_ActivityLevelsButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_ActivityLevelsButton);
}
