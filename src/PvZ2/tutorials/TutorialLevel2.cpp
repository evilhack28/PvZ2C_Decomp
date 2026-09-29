//
//  TutorialLevel2.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "TutorialLevel2.h"

TutorialLevel2::TutorialLevel2()
{
}

TutorialLevel2::~TutorialLevel2()
{
}

TutorialLevel2Properties::TutorialLevel2Properties()
{
}

TutorialLevel2Properties::~TutorialLevel2Properties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TutorialLevel2);

void TutorialLevel2::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TutorialLevel2);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(IntroModule);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
	REFLECTION_CLASSBUILDER_END(TutorialLevel2);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TutorialLevel2Properties);

void TutorialLevel2Properties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TutorialLevel2Properties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

	REFLECTION_CLASSBUILDER_END(TutorialLevel2Properties);
}
