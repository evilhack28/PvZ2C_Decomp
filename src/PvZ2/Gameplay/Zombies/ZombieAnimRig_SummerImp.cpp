//
//  ZombieAnimRig_SummerImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieFutureImp.h"

ZombieAnimRig_SummerImp::ZombieAnimRig_SummerImp()
{
}

ZombieAnimRig_SummerImp::~ZombieAnimRig_SummerImp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_SummerImp);

void ZombieAnimRig_SummerImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_SummerImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_FutureImp);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_SummerImp);
}
