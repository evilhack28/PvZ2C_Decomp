//
//  WorldMap_TreasureButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_TreasureButton.h"

WorldMap_TreasureButton::~WorldMap_TreasureButton()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_TreasureButton);

void WorldMap_TreasureButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_TreasureButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_TreasureButton);
}
