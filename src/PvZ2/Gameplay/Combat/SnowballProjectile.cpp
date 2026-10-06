//
//  SnowballProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SnowballProjectile.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SnowballProjectile);

void SnowballProjectile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SnowballProjectile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

	REFLECTION_CLASSBUILDER_END(SnowballProjectile);
}
