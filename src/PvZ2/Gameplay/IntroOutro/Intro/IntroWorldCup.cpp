//
//  IntroWorldCup.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "IntroWorldCup.h"

IntroWorldCup::~IntroWorldCup()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(IntroWorldCup);

void IntroWorldCup::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(IntroWorldCup);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntro);

		REFLECTION_CLASSBUILDER_FIELD(float, m_remainTime);
	REFLECTION_CLASSBUILDER_END(IntroWorldCup);
}

#include "IntroWorldCup.h"
void IntroWorldCup::OnEffectDone(class StandaloneEffect* i_effect)
{
	 IntroWorldCup::CreateCountDownEffect();
}

#include "IntroWorldCup.h"
void IntroWorldCup::OnCountDownEffectDone(class StandaloneEffect* i_effect)
{
	 IntroWorldCup::MoveOffIntroIcons();
}

#include "IntroWorldCup.h"
void IntroWorldCup::onNotifyLeft30Seconds()
{
	 IntroWorldCup::CreateLeftTime();
}
