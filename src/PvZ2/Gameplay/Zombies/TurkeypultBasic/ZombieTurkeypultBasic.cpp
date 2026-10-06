//
//  ZombieTurkeypultBasic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieTurkeypultBasic.h"

#include "Zombie.h"
void ZombieTurkeypultBasic::TurkeyRefreshStats()
{
	 Zombie::RefreshStats();
}

void ZombieTurkeypultBasic::CreateZombieLevelEffect(bool i_arg)
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieTurkeypultBasic);

void ZombieTurkeypultBasic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieTurkeypultBasic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_time);
	REFLECTION_CLASSBUILDER_END(ZombieTurkeypultBasic);
}

bool ZombieTurkeypultBasic::allowAshState() const
{
	return false;
}
