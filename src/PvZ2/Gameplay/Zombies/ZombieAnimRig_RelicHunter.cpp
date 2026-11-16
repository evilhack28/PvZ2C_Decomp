//
//  ZombieAnimRig_RelicHunter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityRelicHunter.h"

ZombieAnimRig_RelicHunter::ZombieAnimRig_RelicHunter()
{
}

ZombieAnimRig_RelicHunter::~ZombieAnimRig_RelicHunter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_RelicHunter);

void ZombieAnimRig_RelicHunter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_RelicHunter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Swashbuckler);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_RelicHunter);
}
