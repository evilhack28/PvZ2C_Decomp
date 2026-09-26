//
//  ZombieAnimRig_EightiesArcade.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesArcade.h"

ZombieAnimRig_EightiesArcade::ZombieAnimRig_EightiesArcade()
{
}

ZombieAnimRig_EightiesArcade::~ZombieAnimRig_EightiesArcade()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_EightiesArcade);

void ZombieAnimRig_EightiesArcade::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_EightiesArcade);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithPushingActionAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_EightiesArcade);
}
