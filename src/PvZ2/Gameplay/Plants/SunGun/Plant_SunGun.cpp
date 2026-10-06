//
//  Plant_SunGun.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_SunGun.h"

PlantSunGun::PlantSunGun()
{
}

PlantSunGun::~PlantSunGun()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSunGun);

bool PlantSunGun::CanBeShoveled()
{
	return false;
}

bool PlantSunGun::CanBeTargeted()
{
	return false;
}

void PlantSunGun::TakeSmashAttack(ZombiePtr i_arg)
{
}

bool PlantSunGun::CanApplyPlantfood()
{
	return false;
}
