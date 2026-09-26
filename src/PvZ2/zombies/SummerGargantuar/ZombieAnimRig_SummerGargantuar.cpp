//
//  ZombieAnimRig_SummerGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Gargantuar.h"

ZombieAnimRig_SummerGargantuar::ZombieAnimRig_SummerGargantuar()
{
}

ZombieAnimRig_SummerGargantuar::~ZombieAnimRig_SummerGargantuar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_SummerGargantuar);

void ZombieAnimRig_SummerGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_SummerGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Gargantuar);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_SummerGargantuar);
}
