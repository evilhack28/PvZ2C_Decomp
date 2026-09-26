//
//  TutorialPeashooterDeath.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "TutorialPeashooterDeath.h"

TutorialPeashooterDeathProperties::TutorialPeashooterDeathProperties()
{
}

TutorialPeashooterDeathProperties::~TutorialPeashooterDeathProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TutorialPeashooterDeathProperties);

void TutorialPeashooterDeathProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TutorialPeashooterDeathProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(TutorialPeashooterDeathProperties);
}
