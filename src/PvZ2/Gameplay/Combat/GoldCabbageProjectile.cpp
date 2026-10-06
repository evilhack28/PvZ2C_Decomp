//
//  GoldCabbageProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GoldCabbageProjectile.h"

GoldCabbageProjectile::~GoldCabbageProjectile()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GoldCabbageProjectile);

void GoldCabbageProjectile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GoldCabbageProjectile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_targetVec);
	REFLECTION_CLASSBUILDER_END(GoldCabbageProjectile);
}
