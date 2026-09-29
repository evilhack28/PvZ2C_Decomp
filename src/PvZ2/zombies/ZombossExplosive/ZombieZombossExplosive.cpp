//
//  ZombieZombossExplosive.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossExplosive.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossExplosive);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossExplosiveProps);

void ZombieZombossExplosiveProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossExplosiveImp);
		REFLECTION_CLASSBUILDER_FIELD(int, ImpTargetColumn);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, ImpSpawnOffset);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ImpType);
	REFLECTION_CLASSBUILDER_END(ZombossExplosiveImp);

	REFLECTION_CLASSBUILDER_BEGIN(ZombossExplosiveStage);
		REFLECTION_CLASSBUILDER_FIELD(CZombieSummonDataPool, ZombieSummonDataPool);
	REFLECTION_CLASSBUILDER_END(ZombossExplosiveStage);

	REFLECTION_CLASSBUILDER_BEGIN(ZombieZombossExplosiveProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombossProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ZombossExplosiveStage>, Stages);
		REFLECTION_CLASSBUILDER_FIELD(ZombossExplosiveImp, ZombossImp);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Projectile);
	REFLECTION_CLASSBUILDER_END(ZombieZombossExplosiveProps);
}

#include "Zombie.h"
void ZombieZombossExplosive::registerForEvents()
{
	 Zombie::registerForEvents();
}

void ZombieZombossExplosive::onJumpToSkyAnimDone(const std::string& i_arg)
{
}

void ZombieZombossExplosive::unregisterForEvents()
{
}

void ZombieZombossExplosive::onJumpToChangeLaneAnimDone(const std::string& i_arg)
{
}
