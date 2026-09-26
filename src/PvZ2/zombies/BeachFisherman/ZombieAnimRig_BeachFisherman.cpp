//
//  ZombieAnimRig_BeachFisherman.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieBeachFisherman.h"

ZombieAnimRig_BeachFisherman::ZombieAnimRig_BeachFisherman()
{
}

ZombieAnimRig_BeachFisherman::~ZombieAnimRig_BeachFisherman()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_BeachFisherman);

void ZombieAnimRig_BeachFisherman::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_BeachFisherman);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_BeachFisherman);
}
