//
//  ZombieAnimRig_EightiesGlitter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesGlitter.h"

ZombieAnimRig_EightiesGlitter::ZombieAnimRig_EightiesGlitter()
{
}

ZombieAnimRig_EightiesGlitter::~ZombieAnimRig_EightiesGlitter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_EightiesGlitter);

void ZombieAnimRig_EightiesGlitter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_EightiesGlitter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_EightiesGlitter);
}
