//
//  Plant_WaterRabbit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_WaterRabbit.h"

PlantWaterRabbit::~PlantWaterRabbit()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantWaterRabbit);

void PlantWaterRabbit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantWaterRabbit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_currentTarget);
	REFLECTION_CLASSBUILDER_END(PlantWaterRabbit);
}

bool PlantWaterRabbit::CanApplyPlantfood()
{
	return true;
}
