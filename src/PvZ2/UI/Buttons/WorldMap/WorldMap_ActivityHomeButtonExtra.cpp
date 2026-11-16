//
//  WorldMap_ActivityHomeButtonExtra.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_ActivityHomeButtonExtra.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_ActivityHomeButtonExtra);

void WorldMap_ActivityHomeButtonExtra::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_ActivityHomeButtonExtra);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_ActivityHomeButtonExtra);
}
