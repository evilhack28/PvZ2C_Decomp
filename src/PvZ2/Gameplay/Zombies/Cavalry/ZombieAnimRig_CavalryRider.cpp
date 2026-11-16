//
//  ZombieAnimRig_CavalryRider.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCavalryRider.h"

ZombieAnimRig_CavalryRider::ZombieAnimRig_CavalryRider()
{
}

ZombieAnimRig_CavalryRider::~ZombieAnimRig_CavalryRider()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_CavalryRider);

void ZombieAnimRig_CavalryRider::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_CavalryRider);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Basic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_CavalryRider);
}
