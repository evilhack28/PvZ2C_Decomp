//
//  ZombieSkyCityElectricProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSkyCityElectric.h"

ZombieSkyCityElectricProjectileProps::~ZombieSkyCityElectricProjectileProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSkyCityElectricProjectile);

void ZombieSkyCityElectricProjectile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSkyCityElectricProjectile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

	REFLECTION_CLASSBUILDER_END(ZombieSkyCityElectricProjectile);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSkyCityElectricProjectileProps);

void ZombieSkyCityElectricProjectileProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSkyCityElectricProjectileProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ProjectilePropertySheet);

	REFLECTION_CLASSBUILDER_FIELD(int, PlantCondition);

	REFLECTION_CLASSBUILDER_END(ZombieSkyCityElectricProjectileProps);
}
