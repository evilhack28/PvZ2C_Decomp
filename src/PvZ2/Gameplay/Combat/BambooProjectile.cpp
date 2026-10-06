//
//  BambooProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "BambooProjectile.h"

BambooProjectile::BambooProjectile()
{
	m_attackDone = 0;
	m_shouldTossZombie = 0;
}

BambooProjectile::~BambooProjectile()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BambooProjectile);

void BambooProjectile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BambooProjectile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_hitEntities);
	REFLECTION_CLASSBUILDER_END(BambooProjectile);
}
