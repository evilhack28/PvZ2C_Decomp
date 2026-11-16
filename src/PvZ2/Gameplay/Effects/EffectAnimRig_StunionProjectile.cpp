//
//  EffectAnimRig_StunionProjectile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Stunion.h"

EffectAnimRig_StunionProjectile::~EffectAnimRig_StunionProjectile()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_StunionProjectile);

void EffectAnimRig_StunionProjectile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectAnimRig_StunionProjectile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_endingAnimationLength);
	REFLECTION_CLASSBUILDER_FIELD(bool, m_advanced);

	REFLECTION_CLASSBUILDER_END(EffectAnimRig_StunionProjectile);
}
