//
//  Plant_Ents.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Ents.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantEnts);

void PlantEnts::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantEnts);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_plantfoodDamageEndTime);
	REFLECTION_CLASSBUILDER_END(PlantEnts);
}

void PlantEnts::UpdatePlantfood()
{
}

bool PlantEnts::CanApplyPlantfood()
{
	return true;
}

void PlantEnts::onStandaloneEffectFinishedCallback(class StandaloneEffect* i_effect)
{
}
