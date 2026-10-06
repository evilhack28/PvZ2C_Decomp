//
//  Effect_BouncingArrow.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Effect_BouncingArrow.h"

Effect_BouncingArrow::Effect_BouncingArrow()
{
}

Effect_BouncingArrow::~Effect_BouncingArrow()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_BouncingArrow);

void Effect_BouncingArrow::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_BouncingArrow);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandaloneEffect);

	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Image>, m_image);
	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_startTime);

	REFLECTION_CLASSBUILDER_END(Effect_BouncingArrow);
}
