//
//  EffectObject_DinoTread.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "EffectObject_DinoTread.h"

EffectObject_DinoTread::EffectObject_DinoTread()
{
}

EffectObject_DinoTread::~EffectObject_DinoTread()
{
}

EffectObject_DinoTreadProps::~EffectObject_DinoTreadProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectObject_DinoTread);

void EffectObject_DinoTread::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectObject_DinoTread);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(EffectObject);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_cachedBramble);
	REFLECTION_CLASSBUILDER_END(EffectObject_DinoTread);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectObject_DinoTreadProps);

void EffectObject_DinoTreadProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectObject_DinoTreadProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(EffectObjectPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, TreadStayTime);
		REFLECTION_CLASSBUILDER_FIELD(float, TreadDamage);
	REFLECTION_CLASSBUILDER_END(EffectObject_DinoTreadProps);
}

void EffectObject_DinoTread::onDestroy()
{
}
