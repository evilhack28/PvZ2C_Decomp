//
//  ZombieYearMonster.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieYearMonster.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieYearMonster);

void ZombieYearMonster::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieYearMonster);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_target);
	REFLECTION_CLASSBUILDER_END(ZombieYearMonster);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieYearMonsterProps);

void ZombieYearMonsterProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieYearMonsterProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActionsProps);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Projectile);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, whitelist);
	REFLECTION_CLASSBUILDER_END(ZombieYearMonsterProps);
}
