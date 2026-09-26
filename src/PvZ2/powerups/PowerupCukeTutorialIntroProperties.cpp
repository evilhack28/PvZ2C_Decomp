//
//  PowerupCukeTutorialIntroProperties.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupCukeTutorialIntro.h"

PowerupCukeTutorialIntroProperties::PowerupCukeTutorialIntroProperties()
{
}

PowerupCukeTutorialIntroProperties::~PowerupCukeTutorialIntroProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupCukeTutorialIntroProperties);

void PowerupCukeTutorialIntroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupCukeTutorialIntroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

	REFLECTION_CLASSBUILDER_END(PowerupCukeTutorialIntroProperties);
}
