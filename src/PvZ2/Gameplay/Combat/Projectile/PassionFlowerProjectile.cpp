//
//  PassionFlowerProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PassionFlowerProjectile.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

PassionFlowerProjectileProps::~PassionFlowerProjectileProps()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PassionFlowerProjectileProps);

void PassionFlowerProjectileProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PassionFlowerProjectileProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ProjectilePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, smallBullets);
	REFLECTION_CLASSBUILDER_END(PassionFlowerProjectileProps);
}
