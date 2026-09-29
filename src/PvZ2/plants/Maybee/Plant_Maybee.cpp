//
//  Plant_Maybee.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Maybee.h"

PlantMaybee::PlantMaybee()
{
}

PlantMaybee::~PlantMaybee()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantMaybee);

void PlantMaybee::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantMaybee);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_beesToRelease);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_rechargeTime);
	REFLECTION_CLASSBUILDER_END(PlantMaybee);
}

bool PlantMaybee::CanApplyPlantfood()
{
	return true;
}
