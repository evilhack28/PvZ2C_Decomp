//
//  EffectAnimRig_ZombieStatue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemRenaiStatue.h"

EffectAnimRig_ZombieStatue::EffectAnimRig_ZombieStatue()
{
}

EffectAnimRig_ZombieStatue::~EffectAnimRig_ZombieStatue()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_ZombieStatue);

void EffectAnimRig_ZombieStatue::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectAnimRig_ZombieStatue);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(EffectAnimRig_ZombieStatue);
}
