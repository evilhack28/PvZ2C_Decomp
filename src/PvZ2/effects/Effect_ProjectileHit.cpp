//
//  Effect_ProjectileHit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_OrchidMage.h"

Effect_ProjectileHit::Effect_ProjectileHit()
{
	m_renderDifferenceFromPlant = (decltype(m_renderDifferenceFromPlant))6000;
}

Effect_ProjectileHit::~Effect_ProjectileHit()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_ProjectileHit);

void Effect_ProjectileHit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_ProjectileHit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_ProjectileHit);
}
