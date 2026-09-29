//
//  Plant_PumpkinWitch.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PumpkinWitch.h"

PlantPumpkinWitch::PlantPumpkinWitch()
{
}

PlantPumpkinWitch::~PlantPumpkinWitch()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPumpkinWitch);

void PlantPumpkinWitch::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPumpkinWitch);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_prepareTime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie> >, m_hitZombies);
		REFLECTION_CLASSBUILDER_FIELD(int, m_plantFoodNum);
	REFLECTION_CLASSBUILDER_END(PlantPumpkinWitch);
}

void PlantPumpkinWitch::UpdatePlantfood()
{
}

bool PlantPumpkinWitch::CanApplyPlantfood()
{
	return true;
}

bool PlantPumpkinWitch::FindTargetAndFire(PlantWeapon i_arg)
{
	return false;
}

Projectile* PlantPumpkinWitch::Fire(ZombiePtr i_arg0, int i_arg1, PlantWeapon i_arg2)
{
	return NULL;
}
