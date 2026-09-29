//
//  ZombieElecShieldGenerator.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieElecShieldGenerator.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieElecShieldGenerator);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieElecShieldGeneratorProps);

void ZombieElecShieldGeneratorProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieElecShieldGeneratorProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieMechProps);

		REFLECTION_CLASSBUILDER_FIELD(int32, ShieldCount);
		REFLECTION_CLASSBUILDER_FIELD(bool, ShieldDiesUponLossOfControl);
	REFLECTION_CLASSBUILDER_END(ZombieElecShieldGeneratorProps);
}
