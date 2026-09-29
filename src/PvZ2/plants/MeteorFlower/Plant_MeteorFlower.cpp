//
//  Plant_MeteorFlower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_MeteorFlower.h"

PlantMeteorFlower::PlantMeteorFlower()
{
}

PlantMeteorFlower::~PlantMeteorFlower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantMeteorFlower);

void PlantMeteorFlower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantMeteorFlower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentWarmingRadius>, m_warmingRadius);
	REFLECTION_CLASSBUILDER_END(PlantMeteorFlower);
}

bool PlantMeteorFlower::CanApplyPlantfood()
{
	return true;
}

Projectile* PlantMeteorFlower::Fire(ZombiePtr i_arg0, int i_arg1, PlantWeapon i_arg2)
{
	return NULL;
}
