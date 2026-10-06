//
//  TutorialLevel4.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "TutorialLevel4.h"

TutorialLevel4::TutorialLevel4()
{
}

TutorialLevel4::~TutorialLevel4()
{
}

TutorialLevel4Properties::~TutorialLevel4Properties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TutorialLevel4);

void TutorialLevel4::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TutorialLevel4);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(IntroModule);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
	REFLECTION_CLASSBUILDER_END(TutorialLevel4);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TutorialLevel4Properties);

void TutorialLevel4Properties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TutorialLevel4Properties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

	REFLECTION_CLASSBUILDER_END(TutorialLevel4Properties);
}
