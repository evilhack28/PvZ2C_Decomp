//
//  ZombieAnimRig_ElecShieldGenerator.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieElecShieldGenerator.h"

ZombieAnimRig_ElecShieldGenerator::ZombieAnimRig_ElecShieldGenerator()
{
}

ZombieAnimRig_ElecShieldGenerator::~ZombieAnimRig_ElecShieldGenerator()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ElecShieldGenerator);

void ZombieAnimRig_ElecShieldGenerator::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ElecShieldGenerator);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Mech);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ElecShieldGenerator);
}
