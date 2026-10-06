//
//  ZombieIceYearMonster.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Zombie_IceYearMonster.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceYearMonster);

void ZombieIceYearMonster::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceYearMonster);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

		REFLECTION_CLASSBUILDER_FIELD(bool, Walkflag);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_target);
	REFLECTION_CLASSBUILDER_END(ZombieIceYearMonster);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceYearMonsterProps);

void ZombieIceYearMonsterProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceYearMonsterProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActionsProps);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Projectile);
	REFLECTION_CLASSBUILDER_END(ZombieIceYearMonsterProps);
}

void ZombieIceYearMonster::onResilienceRecoverAnimStopped(const std::string& i_arg)
{
}
