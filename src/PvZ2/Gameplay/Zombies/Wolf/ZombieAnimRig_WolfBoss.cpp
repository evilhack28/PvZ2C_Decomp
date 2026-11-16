//
//  ZombieAnimRig_WolfBoss.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieWolfBoss.h"

ZombieAnimRig_WolfBoss::ZombieAnimRig_WolfBoss()
{
}

ZombieAnimRig_WolfBoss::~ZombieAnimRig_WolfBoss()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_WolfBoss);

void ZombieAnimRig_WolfBoss::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_WolfBoss);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_WolfBoss);
}
