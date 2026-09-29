//
//  ZombieAnimRig_Tutorial.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Tutorial.h"

ZombieAnimRig_Tutorial::ZombieAnimRig_Tutorial()
{
}

ZombieAnimRig_Tutorial::~ZombieAnimRig_Tutorial()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Tutorial);

void ZombieAnimRig_Tutorial::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Tutorial);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Basic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Tutorial);
}
