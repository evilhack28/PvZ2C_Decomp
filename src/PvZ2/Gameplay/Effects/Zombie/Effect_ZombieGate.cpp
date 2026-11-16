//
//  Effect_ZombieGate.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Effect_ZombieGate.h"

Effect_ZombieGate::Effect_ZombieGate()
{
	m_row = -1;
	m_gateVisible = 1;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_ZombieGate);

void Effect_ZombieGate::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_ZombieGate);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandaloneEffect);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<PopAnimRig>, m_gateRig);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_row);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_gateVisible);
	REFLECTION_CLASSBUILDER_END(Effect_ZombieGate);
}

#include "Effect_ZombieGate.h"
void Effect_ZombieGate::OnAnimDone(const std::string & i_animName)
{
	 Effect_ZombieGate::playNormalAnim();
}
