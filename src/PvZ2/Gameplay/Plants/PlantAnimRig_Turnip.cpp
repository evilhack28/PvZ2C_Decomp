//
//  PlantAnimRig_Turnip.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Turnip.h"

PlantAnimRig_Turnip::PlantAnimRig_Turnip()
{
}

PlantAnimRig_Turnip::~PlantAnimRig_Turnip()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Turnip);

bool PlantAnimRig_Turnip::PlayDefend()
{
	return PlayAndContinue("idle3") != -1;
}

bool PlantAnimRig_Turnip::PlaySpinningTurnip()
{
	return PlayAndContinue("plantfood3") != -1;
}
