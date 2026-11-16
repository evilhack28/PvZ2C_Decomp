//
//  ZombieAnimRig_EightiesBreakDancer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesBreakDancer.h"

ZombieAnimRig_EightiesBreakDancer::~ZombieAnimRig_EightiesBreakDancer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_EightiesBreakDancer);

void ZombieAnimRig_EightiesBreakDancer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_EightiesBreakDancer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_jamActive);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_EightiesBreakDancer);
}
