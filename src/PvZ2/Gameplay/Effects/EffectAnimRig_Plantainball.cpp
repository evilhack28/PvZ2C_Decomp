//
//  EffectAnimRig_Plantainball.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Plantain.h"

EffectAnimRig_Plantainball::EffectAnimRig_Plantainball()
{
}

EffectAnimRig_Plantainball::~EffectAnimRig_Plantainball()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_Plantainball);

bool EffectAnimRig_Plantainball::PlayNormalFlightLooped()
{
	return PlayAndContinue("animation") != -1;
}

bool EffectAnimRig_Plantainball::PlayPlantFoodFlightLooped()
{
	return PlayAndContinue("animation") != -1;
}

bool EffectAnimRig_Plantainball::PlayStarPlantFoodFlightLooped()
{
	return PlayAndContinue("animation") != -1;
}
