//
//  WorldMap_PlantTrialButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_PlantTrialButton.h"

WorldMap_PlantTrialButton::~WorldMap_PlantTrialButton()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_PlantTrialButton);

void WorldMap_PlantTrialButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_PlantTrialButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_PlantTrialButton);
}
