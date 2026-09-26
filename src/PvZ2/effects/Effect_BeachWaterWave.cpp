//
//  Effect_BeachWaterWave.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Effect_BeachWaterWave.h"

Effect_BeachWaterWave::~Effect_BeachWaterWave()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_BeachWaterWave);

void Effect_BeachWaterWave::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_BeachWaterWave);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_tChangerColorStarTime);

	REFLECTION_CLASSBUILDER_END(Effect_BeachWaterWave);
}
