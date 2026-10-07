//
//  Plant_Hammerflower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Hammerflower.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHammerflower);

void PlantHammerflower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHammerflower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_plantfoodDamageEndTime);
	REFLECTION_CLASSBUILDER_END(PlantHammerflower);
}

void PlantHammerflower::UpdatePlantfood()
{
}

bool PlantHammerflower::CanApplyPlantfood()
{
	return true;
}

void PlantHammerflower::onStandaloneEffectFinishedCallback(class StandaloneEffect* i_effect)
{
}
