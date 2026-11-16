//
//  EffectAnimRig_StarGate.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "EffectAnimRig_StarGate.h"

EffectAnimRig_StarGate::~EffectAnimRig_StarGate()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_StarGate);

void EffectAnimRig_StarGate::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectAnimRig_StarGate);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(EffectAnimRig_StarGate);
}

#include "EffectAnimRig_StarGate.h"
void EffectAnimRig_StarGate::onLockingSequenceContinued(const std::string& i_oldAnimName)
{
	 EffectAnimRig_StarGate::PlayLockedIdle();
}
