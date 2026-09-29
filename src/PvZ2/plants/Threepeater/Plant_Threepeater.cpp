//
//  Plant_Threepeater.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Threepeater.h"

PlantThreepeater::PlantThreepeater()
{
	m_plantFoodShotAngle = 0;
}

PlantThreepeater::~PlantThreepeater()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantThreepeater);

void PlantThreepeater::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantThreepeater);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextPlantFoodShotTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_plantFoodShotAngle);
	REFLECTION_CLASSBUILDER_END(PlantThreepeater);
}

bool PlantThreepeater::CanApplyPlantfood()
{
	return true;
}
