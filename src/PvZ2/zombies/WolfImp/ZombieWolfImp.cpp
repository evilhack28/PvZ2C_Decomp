//
//  ZombieWolfImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-26.
//

#include "SexyAppFramework/Common.h"

#include "ZombieWolfImp.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieWolfImp);

void ZombieWolfImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieWolfImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieTowerDefendBasic);

	REFLECTION_CLASSBUILDER_END(ZombieWolfImp);
}

float ZombieWolfImp::GetAmberScale()
{
	return 0.53f;
}
