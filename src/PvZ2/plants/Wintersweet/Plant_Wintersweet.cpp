//
//  Plant_Wintersweet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Wintersweet.h"

PlantWintersweet::PlantWintersweet()
{
}

PlantWintersweet::~PlantWintersweet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantWintersweet);

void PlantWintersweet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantWintersweet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, m_plantfood_flower_num);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_plantfood_index);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_cooldown_time);
	REFLECTION_CLASSBUILDER_END(PlantWintersweet);
}

bool PlantWintersweet::CanApplyPlantfood()
{
	return true;
}
