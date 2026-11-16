//
//  ZombieAnimRig_ParkourBucket.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Tutorial.h"

ZombieAnimRig_ParkourBucket::ZombieAnimRig_ParkourBucket()
{
}

ZombieAnimRig_ParkourBucket::~ZombieAnimRig_ParkourBucket()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ParkourBucket);

void ZombieAnimRig_ParkourBucket::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ParkourBucket);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ParkourBasic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ParkourBucket);
}
