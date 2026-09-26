//
//  EffectAnimRig_DelayReplayAnim.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "EffectAnimRig_DelayReplayAnim.h"

EffectAnimRig_DelayReplayAnim::~EffectAnimRig_DelayReplayAnim()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_DelayReplayAnim);

void EffectAnimRig_DelayReplayAnim::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectAnimRig_DelayReplayAnim);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(std::string, m_animName);

	REFLECTION_CLASSBUILDER_END(EffectAnimRig_DelayReplayAnim);
}
