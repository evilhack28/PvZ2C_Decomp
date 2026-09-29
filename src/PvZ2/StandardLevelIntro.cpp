//
//  StandardLevelIntro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StandardLevelIntro.h"

StandardLevelIntro::StandardLevelIntro()
{
}

StandardLevelIntro::~StandardLevelIntro()
{
}

StandardLevelIntroProperties::~StandardLevelIntroProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StandardLevelIntro);

void StandardLevelIntro::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StandardLevelIntro);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(IntroModule);

	REFLECTION_CLASSBUILDER_END(StandardLevelIntro);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StandardLevelIntroProperties);

void StandardLevelIntro::OnIntroDone()
{
}

bool StandardLevelIntro::canInit()
{
	return true;
}
