//
//  IntroFishing.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "IntroFishing.h"

IntroFishingProperties::IntroFishingProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(IntroFishing);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(IntroFishingProperties);

void IntroFishingProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(IntroFishingProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

	REFLECTION_CLASSBUILDER_END(IntroFishingProperties);
}

#include "StandardLevelIntro.h"
void IntroFishing::initializeModule()
{
	 StandardLevelIntro::initializeModule();
}

void IntroFishing::onGameplayStarted()
{
}
