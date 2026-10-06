//
//  ZombieAnimRig_WolfImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieWolfImp.h"

ZombieAnimRig_WolfImp::ZombieAnimRig_WolfImp()
{
}

ZombieAnimRig_WolfImp::~ZombieAnimRig_WolfImp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_WolfImp);

void ZombieAnimRig_WolfImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_WolfImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_WolfImp);
}
