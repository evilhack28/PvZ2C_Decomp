//
//  Plant_Sunflower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Sunflower.h"

PlantSunflower::PlantSunflower()
{
	m_ProduceSunfirst = 1;
}

PlantSunflower::~PlantSunflower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSunflower);

void PlantSunflower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSunflower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_plantFoodSunsToSpawn);
	REFLECTION_CLASSBUILDER_END(PlantSunflower);
}

bool PlantSunflower::CanApplyPlantfood()
{
	return true;
}
