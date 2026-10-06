//
//  WorldMap_BackButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_BackButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_BackButton);

void WorldMap_BackButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_BackButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_BackButton);
}
