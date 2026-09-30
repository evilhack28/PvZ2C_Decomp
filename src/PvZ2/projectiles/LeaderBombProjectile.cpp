//
//  LeaderBombProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "LeaderBombProjectile.h"

bool LeaderBombProjectile::OnCollideGround()
{
	return false;
}

LeaderBombProjectile::LeaderBombProjectile()
{
}

LeaderBombProjectile::~LeaderBombProjectile()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LeaderBombProjectile);

void LeaderBombProjectile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LeaderBombProjectile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

	REFLECTION_CLASSBUILDER_END(LeaderBombProjectile);
}

bool LeaderBombProjectile::OnCollideEntity(BoardEntity* i_arg)
{
	return false;
}
