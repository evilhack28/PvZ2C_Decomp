//
//  Plant_StreetLamp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_StreetLamp.h"

PlantStreetLamp::PlantStreetLamp()
{
}

PlantStreetLamp::~PlantStreetLamp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantStreetLamp);

void PlantStreetLamp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantStreetLamp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_iFoodEndTime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<Point>, m_vLightUpGridVec);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bFoodEffect);
	REFLECTION_CLASSBUILDER_END(PlantStreetLamp);
}

#include "PlantFramework.h"
void PlantStreetLamp::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

bool PlantStreetLamp::CanApplyPlantfood()
{
	return true;
}
