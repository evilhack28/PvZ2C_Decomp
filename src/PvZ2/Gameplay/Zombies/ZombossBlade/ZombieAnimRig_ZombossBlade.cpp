//
//  ZombieAnimRig_ZombossBlade.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_ZombossBlade.h"

ZombieAnimRig_ZombossBlade::ZombieAnimRig_ZombossBlade()
{
}

ZombieAnimRig_ZombossBlade::~ZombieAnimRig_ZombossBlade()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ZombossBlade);

void ZombieAnimRig_ZombossBlade::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZombossBlade);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Zomboss);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZombossBlade);
}
