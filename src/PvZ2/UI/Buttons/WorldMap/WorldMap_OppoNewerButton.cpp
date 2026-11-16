//
//  WorldMap_OppoNewerButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_OppoNewerButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_OppoNewerButton);

void WorldMap_OppoNewerButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_OppoNewerButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_OppoNewerButton);
}
