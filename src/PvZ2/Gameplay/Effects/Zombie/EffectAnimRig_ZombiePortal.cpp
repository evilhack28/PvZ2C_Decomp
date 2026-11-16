//
//  EffectAnimRig_ZombiePortal.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "EffectAnimRig_ZombiePortal.h"

EffectAnimRig_ZombiePortal::EffectAnimRig_ZombiePortal()
{
}

EffectAnimRig_ZombiePortal::~EffectAnimRig_ZombiePortal()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_ZombiePortal);

void EffectAnimRig_ZombiePortal::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectAnimRig_ZombiePortal);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(EffectAnimRig_ZombiePortal);
}
