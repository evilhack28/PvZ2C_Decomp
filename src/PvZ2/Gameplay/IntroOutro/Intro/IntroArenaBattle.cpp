//
//  IntroArenaBattle.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "IntroArenaBattle.h"

IntroArenaBattle::IntroArenaBattle()
{
}

IntroArenaBattle::~IntroArenaBattle()
{
}

IntroArenaBattleProperties::~IntroArenaBattleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(IntroArenaBattle);

void IntroArenaBattle::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(IntroArenaBattle);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntro);

	REFLECTION_CLASSBUILDER_END(IntroArenaBattle);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(IntroArenaBattleProperties);

void IntroArenaBattleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(IntroArenaBattleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

	REFLECTION_CLASSBUILDER_END(IntroArenaBattleProperties);
}

bool IntroArenaBattle::preventSave()
{
	return true;
}

#include "StandardLevelIntro.h"
void IntroArenaBattle::initializeModule()
{
	 StandardLevelIntro::initializeModule();
}
