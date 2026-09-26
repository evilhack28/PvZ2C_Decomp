//
//  ZombieAnimRig_ZombieTarget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_ZombieTarget.h"

ZombieAnimRig_ZombieTarget::ZombieAnimRig_ZombieTarget()
{
}

ZombieAnimRig_ZombieTarget::~ZombieAnimRig_ZombieTarget()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ZombieTarget);

void ZombieAnimRig_ZombieTarget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZombieTarget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZombieTarget);
}
