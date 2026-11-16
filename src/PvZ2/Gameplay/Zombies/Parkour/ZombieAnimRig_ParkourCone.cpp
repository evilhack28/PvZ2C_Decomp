//
//  ZombieAnimRig_ParkourCone.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Tutorial.h"

ZombieAnimRig_ParkourCone::ZombieAnimRig_ParkourCone()
{
}

ZombieAnimRig_ParkourCone::~ZombieAnimRig_ParkourCone()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ParkourCone);

void ZombieAnimRig_ParkourCone::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ParkourCone);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ParkourBasic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ParkourCone);
}
