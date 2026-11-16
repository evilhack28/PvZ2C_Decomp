//
//  Plant_Asparagus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Asparagus.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAsparagus);

void PlantAsparagus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAsparagus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_iSleepTime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<Point>, m_vPlantFoodGrid);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_vPushZombie);
	REFLECTION_CLASSBUILDER_END(PlantAsparagus);
}

bool PlantAsparagus::CanApplyPlantfood()
{
	return true;
}
