//
//  Plant_TupistraStalker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_TupistraStalker.h"

PlantTupistraStalker::PlantTupistraStalker()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTupistraStalker);

void PlantTupistraStalker::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTupistraStalker);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_lastAttack);
	REFLECTION_CLASSBUILDER_END(PlantTupistraStalker);
}

#include "Plant_TupistraStalker.h"
void PlantTupistraStalker::CallPlantfoodAttack()
{
	 PlantTupistraStalker::dealAreaDamage();
}

void PlantTupistraStalker::TakeSmashAttack(ZombiePtr i_srcZombie)
{
	if (m_plant->IsInvincible())
	{
		return;
	}

	m_plant->KillPlant();
}

