//
//  ZombieAnimRig_TombRaiser.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_TombRaiser.h"

ZombieAnimRig_TombRaiser::ZombieAnimRig_TombRaiser()
{
}

ZombieAnimRig_TombRaiser::~ZombieAnimRig_TombRaiser()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_TombRaiser);

void ZombieAnimRig_TombRaiser::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_TombRaiser);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_TombRaiser);
}
