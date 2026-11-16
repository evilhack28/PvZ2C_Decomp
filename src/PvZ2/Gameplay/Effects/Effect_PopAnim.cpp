//
//  Effect_PopAnim.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Effect_PopAnim.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_PopAnim);

void Effect_PopAnim::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AnimationSequenceEntry);
		REFLECTION_CLASSBUILDER_FIELD(std::string, AnimationLabel);
		REFLECTION_CLASSBUILDER_FIELD(int32, SelectionMethod);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, LoopingDuration);
	REFLECTION_CLASSBUILDER_END(AnimationSequenceEntry);

	REFLECTION_CLASSBUILDER_BEGIN(AnimationSequence);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<AnimationSequenceEntry>, m_animationEntries);
	REFLECTION_CLASSBUILDER_END(AnimationSequence);

	REFLECTION_CLASSBUILDER_BEGIN(Effect_PopAnim);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandaloneEffect);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<PopAnimRig>, m_rig);
		REFLECTION_CLASSBUILDER_FIELD(AnimationSequence, m_animSequence);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_animSequenceCurrentIndex);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_animSequenceCurrentIndexStartTime);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, m_translation);
	REFLECTION_CLASSBUILDER_END(Effect_PopAnim);
}

void Effect_PopAnim::OnAnimCommand(const std::string & i_animCommand, const std::string & i_animCommandParam)
{
}

#include "Effect_PopAnim.h"
void Effect_PopAnim::onAnimStopped(const std::string& i_animName)
{
	 Effect_PopAnim::advanceAnimSequence();
}

#include "Effect_PopAnim.h"
void Effect_PopAnim::onOriginChanged()
{
	 Effect_PopAnim::setRigTransform();
}
