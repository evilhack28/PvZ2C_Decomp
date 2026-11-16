//
//  EffectObject_DamageOverTime.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "EffectObject_DamageOverTime.h"

EffectObject_DamageOverTimeProps::~EffectObject_DamageOverTimeProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectObject_DamageOverTime);

void EffectObject_DamageOverTime::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectObject_DamageOverTime);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(EffectObject);

		REFLECTION_CLASSBUILDER_FIELD(int32_t, m_currentState);
	REFLECTION_CLASSBUILDER_END(EffectObject_DamageOverTime);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectObject_DamageOverTimeProps);
