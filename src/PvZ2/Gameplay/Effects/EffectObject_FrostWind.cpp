//
//  EffectObject_FrostWind.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "EffectObject_FrostWind.h"

EffectObject_FrostWind::EffectObject_FrostWind()
{
}

EffectObject_FrostWind::~EffectObject_FrostWind()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectObject_FrostWind);

void EffectObject_FrostWind::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectObject_FrostWind);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(EffectObject);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_timeToApplyFrost);
	REFLECTION_CLASSBUILDER_FIELD(int, m_row);

	REFLECTION_CLASSBUILDER_END(EffectObject_FrostWind);
}
