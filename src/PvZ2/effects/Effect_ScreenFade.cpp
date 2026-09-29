//
//  Effect_ScreenFade.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Effect_ScreenFade.h"

Effect_ScreenFade::Effect_ScreenFade()
{
	m_currentFade = 0;
}

Effect_ScreenFade::~Effect_ScreenFade()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_ScreenFade);

void Effect_ScreenFade::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SingleScreenFade);
		REFLECTION_CLASSBUILDER_FIELD(Color, FadeColor);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, Duration);
	REFLECTION_CLASSBUILDER_END(SingleScreenFade);

	REFLECTION_CLASSBUILDER_BEGIN(Effect_ScreenFade);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandaloneEffect);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<SingleScreenFade>, m_screenFadeSequence);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_currentFade);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_currentFadeTimer);
	REFLECTION_CLASSBUILDER_END(Effect_ScreenFade);
}
