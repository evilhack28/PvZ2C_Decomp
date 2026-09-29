//
//  ZombieWolfFire.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieWolfFire.h"

ZombieWolfFire::ZombieWolfFire()
{
}

ZombieWolfFire::~ZombieWolfFire()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieWolfFire);

void ZombieWolfFire::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieWolfFire);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieTowerDefendBasic);

	REFLECTION_CLASSBUILDER_END(ZombieWolfFire);
}
