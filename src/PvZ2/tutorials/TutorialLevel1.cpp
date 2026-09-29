//
//  TutorialLevel1.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "TutorialLevel1.h"

TutorialLevel1::TutorialLevel1()
{
}

TutorialLevel1::~TutorialLevel1()
{
}

TutorialLevel1Properties::TutorialLevel1Properties()
{
}

TutorialLevel1Properties::~TutorialLevel1Properties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TutorialLevel1);

void TutorialLevel1::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TutorialLevel1);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(IntroModule);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
	REFLECTION_CLASSBUILDER_END(TutorialLevel1);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TutorialLevel1Properties);

void TutorialLevel1Properties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TutorialLevel1Properties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

	REFLECTION_CLASSBUILDER_END(TutorialLevel1Properties);
}

void TutorialLevel1::onNarrationFinished()
{
}
