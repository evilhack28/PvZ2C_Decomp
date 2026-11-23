//
//  PlantAnimRig_OrchidMage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_OrchidMage.h"

PlantAnimRig_OrchidMage::PlantAnimRig_OrchidMage()
{
}

PlantAnimRig_OrchidMage::~PlantAnimRig_OrchidMage()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_OrchidMage);

void PlantAnimRig_OrchidMage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_OrchidMage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_OrchidMage);
}

bool PlantAnimRig_OrchidMage::PlayAttack()
{
	return PlayAndContinue("attack") != -1;
}

bool PlantAnimRig_OrchidMage::PlayAttackIdle()
{
	return PlayAndContinue("attack_idle") != -1;
}

bool PlantAnimRig_OrchidMage::PlayInitialFrame()
{
	return PlayAndContinue("idle") != -1;
}

bool PlantAnimRig_OrchidMage::PlayPassive()
{
	return PlayAndContinue("passive") != -1;
}
