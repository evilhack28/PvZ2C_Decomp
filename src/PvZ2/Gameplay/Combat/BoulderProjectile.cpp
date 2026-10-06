//
//  BoulderProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "BoulderProjectile.h"

BoulderProjectileProps::~BoulderProjectileProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BoulderProjectileProps);

void BoulderProjectileProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BoulderProjectileProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ProjectilePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, RollingVelocity);
	REFLECTION_CLASSBUILDER_END(BoulderProjectileProps);
}
