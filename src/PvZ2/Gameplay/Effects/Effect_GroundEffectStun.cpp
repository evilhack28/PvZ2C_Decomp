//
//  Effect_GroundEffectStun.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Effect_GroundEffects.h"

Effect_GroundEffectStun::~Effect_GroundEffectStun()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_GroundEffectStun);

void Effect_GroundEffectStun::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_GroundEffectStun);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_BeachWaterWave);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_tEndTime);

	REFLECTION_CLASSBUILDER_END(Effect_GroundEffectStun);
}
