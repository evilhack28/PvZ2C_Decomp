//
//  ZombieShooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieShooter.h"

ZombieShooterProps::~ZombieShooterProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieShooterProps);

void ZombieShooterProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieShooterProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_FIELD(SexyVector3, SpawnOffset);
	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Projectile);

	REFLECTION_CLASSBUILDER_END(ZombieShooterProps);
}

#include "Zombie.h"
void ZombieShooter::onZombieInitialize()
{
	 Zombie::onZombieInitialize();
}

ZombieShooter::ZombieShooter()
{
}

ZombieShooter::~ZombieShooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieShooter);

void ZombieShooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieShooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

	REFLECTION_CLASSBUILDER_END(ZombieShooter);
}

bool ZombieShooter::hasHeadParticle() const
{
	return false;
}
