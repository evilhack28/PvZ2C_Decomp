//
//  WorldMap_ActivityHomeButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_ActivityHomeButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_ActivityHomeButton);

void WorldMap_ActivityHomeButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_ActivityHomeButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_ActivityHomeButton);
}
