//
//  ZombieChickenFarmer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieChickenFarmer.h"

ZombieChickenFarmerProps::~ZombieChickenFarmerProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieChickenFarmer);

void ZombieChickenFarmer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieChickenFarmer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasChickened);
	REFLECTION_CLASSBUILDER_END(ZombieChickenFarmer);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieChickenFarmerProps);

void ZombieChickenFarmerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieChickenFarmerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, ChickeningHealthPercentage);
	REFLECTION_CLASSBUILDER_END(ZombieChickenFarmerProps);
}

bool ZombieChickenFarmer::shouldSpawnChickensOnEatAttack()
{
	return true;
}
