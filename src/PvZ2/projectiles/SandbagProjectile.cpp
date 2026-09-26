//
//  SandbagProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SandbagProjectile.h"

SandbagProjectileProps::~SandbagProjectileProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SandbagProjectile);

void SandbagProjectile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SandbagProjectile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

	REFLECTION_CLASSBUILDER_END(SandbagProjectile);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SandbagProjectileProps);

void SandbagProjectileProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SandbagProjectileProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ProjectilePropertySheet);

	REFLECTION_CLASSBUILDER_END(SandbagProjectileProps);
}

bool SandbagProjectile::OnCollideEntity(BoardEntity* i_arg)
{
	return false;
}
