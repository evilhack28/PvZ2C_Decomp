//
//  ZombieAnimRig_MonkImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_MonkImp.h"

ZombieAnimRig_MonkImp::ZombieAnimRig_MonkImp()
{
}

ZombieAnimRig_MonkImp::~ZombieAnimRig_MonkImp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_MonkImp);

void ZombieAnimRig_MonkImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_MonkImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_MonkImp);
}
