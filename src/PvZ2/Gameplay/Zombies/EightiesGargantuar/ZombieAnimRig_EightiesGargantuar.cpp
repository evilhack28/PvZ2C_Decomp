//
//  ZombieAnimRig_EightiesGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesGargantuar.h"

ZombieAnimRig_EightiesGargantuar::~ZombieAnimRig_EightiesGargantuar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_EightiesGargantuar);

void ZombieAnimRig_EightiesGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_EightiesGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Gargantuar);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_EightiesGargantuar);
}
