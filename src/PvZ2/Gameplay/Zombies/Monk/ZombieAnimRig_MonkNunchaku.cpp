//
//  ZombieAnimRig_MonkNunchaku.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_MonkNunchaku.h"

void ZombieAnimRig_MonkNunchaku::PlayRest()
{
}

ZombieAnimRig_MonkNunchaku::ZombieAnimRig_MonkNunchaku()
{
}

ZombieAnimRig_MonkNunchaku::~ZombieAnimRig_MonkNunchaku()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_MonkNunchaku);

void ZombieAnimRig_MonkNunchaku::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_MonkNunchaku);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Hammer);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_MonkNunchaku);
}
