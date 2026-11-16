//
//  EffectAnimRig_SpikeweedSaw.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "EffectAnimRig_SpikeweedSaw.h"

EffectAnimRig_SpikeweedSaw::EffectAnimRig_SpikeweedSaw()
{
}

EffectAnimRig_SpikeweedSaw::~EffectAnimRig_SpikeweedSaw()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_SpikeweedSaw);

void EffectAnimRig_SpikeweedSaw::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectAnimRig_SpikeweedSaw);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int32_t, m_playState);

	REFLECTION_CLASSBUILDER_END(EffectAnimRig_SpikeweedSaw);
}
