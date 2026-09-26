//
//  PlantAnimRig_PrimalSunflower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PrimalSunflower.h"

PlantAnimRig_PrimalSunflower::~PlantAnimRig_PrimalSunflower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_PrimalSunflower);

void PlantAnimRig_PrimalSunflower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_PrimalSunflower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig_Sunflower);

	REFLECTION_CLASSBUILDER_FIELD(int, level5Idx);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_PrimalSunflower);
}
