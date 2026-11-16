//
//  ZombieMoneyTree.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieMoneyTree.h"

ZombieMoneyTreeProps::~ZombieMoneyTreeProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMoneyTree);

void ZombieMoneyTree::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieMoneyTree);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<Sexy::Point>, targetGrid);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, attackTime);
	REFLECTION_CLASSBUILDER_END(ZombieMoneyTree);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMoneyTreeProps);

void ZombieMoneyTreeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieMoneyTreeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActionsProps);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Projectile);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, attackTargetInterval);
	REFLECTION_CLASSBUILDER_END(ZombieMoneyTreeProps);
}
