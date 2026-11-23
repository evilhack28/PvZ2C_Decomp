//
//  EffectAnimRig_CoconutCannonball.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "EffectAnimRig_CoconutCannonball.h"

EffectAnimRig_CoconutCannonball::EffectAnimRig_CoconutCannonball()
{
}

EffectAnimRig_CoconutCannonball::~EffectAnimRig_CoconutCannonball()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_CoconutCannonball);

bool EffectAnimRig_CoconutCannonball::PlayNormalFlightLooped()
{
	return PlayAndContinue("coconut_projectile") != -1;
}

bool EffectAnimRig_CoconutCannonball::PlayPlantFoodFlightLooped()
{
	return PlayAndContinue("coconut_projectile_plantfood") != -1;
}

bool EffectAnimRig_CoconutCannonball::PlayStarPlantFoodFlightLooped()
{
	return PlayAndContinue("coconut_projectile_plantfood2") != -1;
}
