//
//  ZombieAnimRig_FutureProtector.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_FutureProtector.h"

ZombieAnimRig_FutureProtector::ZombieAnimRig_FutureProtector()
{
}

ZombieAnimRig_FutureProtector::~ZombieAnimRig_FutureProtector()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_FutureProtector);

void ZombieAnimRig_FutureProtector::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_FutureProtector);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Mech);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_FutureProtector);
}
