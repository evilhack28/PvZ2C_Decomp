//
//  ZombieAnimRig_Catapult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCatapult.h"

ZombieAnimRig_Catapult::~ZombieAnimRig_Catapult()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Catapult);

void ZombieAnimRig_Catapult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Catapult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int, Ammo);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Catapult);
}

void ZombieAnimRig_Catapult::SetRemainingAmmo(int i_arg)
{
	Ammo = i_arg;
}
