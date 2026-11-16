//
//  RangedPlantProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RangedPlantProjectile.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RangedPlantProjectile);

void RangedPlantProjectile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RangedPlantProjectile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

	REFLECTION_CLASSBUILDER_FIELD(int32, m_projectileRange);
	REFLECTION_CLASSBUILDER_FIELD(float, m_traveledDistance);

	REFLECTION_CLASSBUILDER_END(RangedPlantProjectile);
}
