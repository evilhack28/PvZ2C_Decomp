//
//  EffectAnimRig_EndLevel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "EffectAnimRig_EndLevel.h"

EffectAnimRig_EndLevel::~EffectAnimRig_EndLevel()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_EndLevel);

void EffectAnimRig_EndLevel::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectAnimRig_EndLevel);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(EffectAnimRig_EndLevel);
}
