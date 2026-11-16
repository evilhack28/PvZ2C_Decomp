//
//  PumpkinWitchProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PumpkinWitchProjectile.h"

PumpkinWitchProjectile::PumpkinWitchProjectile()
{
}

PumpkinWitchProjectile::~PumpkinWitchProjectile()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PumpkinWitchProjectile);

void PumpkinWitchProjectile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PumpkinWitchProjectile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

	REFLECTION_CLASSBUILDER_END(PumpkinWitchProjectile);
}
