//
//  PlantAnimRig_WaterRabbit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_WaterRabbit.h"

PlantAnimRig_WaterRabbit::PlantAnimRig_WaterRabbit()
{
}

PlantAnimRig_WaterRabbit::~PlantAnimRig_WaterRabbit()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_WaterRabbit);

void PlantAnimRig_WaterRabbit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_WaterRabbit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_WaterRabbit);
}
