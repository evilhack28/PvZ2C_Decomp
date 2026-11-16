//
//  ZombieMirrorQueenPoisonAppleProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieMirrorQueen.h"

ZombieMirrorQueenPoisonAppleProjectile::ZombieMirrorQueenPoisonAppleProjectile()
{
}

ZombieMirrorQueenPoisonAppleProjectile::~ZombieMirrorQueenPoisonAppleProjectile()
{
}

ZombieMirrorQueenPoisonAppleProjectileProps::ZombieMirrorQueenPoisonAppleProjectileProps()
{
}

ZombieMirrorQueenPoisonAppleProjectileProps::~ZombieMirrorQueenPoisonAppleProjectileProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMirrorQueenPoisonAppleProjectile);

void ZombieMirrorQueenPoisonAppleProjectile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieMirrorQueenPoisonAppleProjectile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

	REFLECTION_CLASSBUILDER_END(ZombieMirrorQueenPoisonAppleProjectile);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMirrorQueenPoisonAppleProjectileProps);

void ZombieMirrorQueenPoisonAppleProjectileProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieMirrorQueenPoisonAppleProjectileProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ProjectilePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieMirrorQueenPoisonAppleProjectileProps);
}
