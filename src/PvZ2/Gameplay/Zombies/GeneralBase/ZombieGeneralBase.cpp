//
//  ZombieGeneralBase.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieGeneralBase.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieGeneralBase);

void ZombieGeneralBase::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieGeneralBase);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActions);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_timeToRetreat);
		REFLECTION_CLASSBUILDER_FIELD(int, m_damageStateOverride);
	REFLECTION_CLASSBUILDER_END(ZombieGeneralBase);
}

void ZombieGeneralBase::SetIdleState()
{
}

void ZombieGeneralBase::SetGrabbedState()
{
}

void ZombieGeneralBase::SetWalkingState()
{
}

#include "ZombieGeneralBase.h"
void ZombieGeneralBase::onTakeBodyDamage(const DamageInfo& i_arg)
{
	 ZombieGeneralBase::updateDamageState();
}

bool ZombieGeneralBase::isImmuneToShrinking()
{
	return true;
}
