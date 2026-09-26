//
//  ZombieAnimRig_EndlessWealth.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEndlessWealth.h"

ZombieAnimRig_EndlessWealth::ZombieAnimRig_EndlessWealth()
{
}

ZombieAnimRig_EndlessWealth::~ZombieAnimRig_EndlessWealth()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_EndlessWealth);

void ZombieAnimRig_EndlessWealth::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_EndlessWealth);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_EndlessWealth);
}
