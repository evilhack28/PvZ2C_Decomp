//
//  Plant_KiwiBeast.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_KiwiBeast.h"

PlantKiwiBeast::PlantKiwiBeast()
{
}

PlantKiwiBeast::~PlantKiwiBeast()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantKiwiBeast);

void PlantKiwiBeast::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantKiwiBeast);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentDamageTossRadius>, m_damageRadius);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_timeOfNextAttack);
		REFLECTION_CLASSBUILDER_FIELD(float, m_damageTaken);
		REFLECTION_CLASSBUILDER_FIELD(int32_t, m_growthLevel);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_firstPlantfoodAttack);
	REFLECTION_CLASSBUILDER_END(PlantKiwiBeast);
}

bool PlantKiwiBeast::HasGravity()
{
	return true;
}
