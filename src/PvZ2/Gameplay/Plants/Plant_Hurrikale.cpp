//
//  Plant_Hurrikale.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Hurrikale.h"

PlantHurrikale::PlantHurrikale()
{
	m_isBlowing = 0;
}

PlantHurrikale::~PlantHurrikale()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHurrikale);

void PlantHurrikale::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHurrikale);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isBlowing);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_blowStartTime);
	REFLECTION_CLASSBUILDER_END(PlantHurrikale);
}

bool PlantHurrikale::CanBeShoveled()
{
	return false;
}

bool PlantHurrikale::CanBeTargeted()
{
	return false;
}

void PlantHurrikale::TakeSmashAttack(ZombiePtr i_srcZombie)
{
}
