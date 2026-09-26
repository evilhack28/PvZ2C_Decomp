//
//  CowboyMinigame.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CowboyMinigame.h"

CowboyMinigameProperties::~CowboyMinigameProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CowboyMinigameProperties);

void CowboyMinigameProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CowboyMinigameProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_FIELD(bool, ShowTutorial);
	REFLECTION_CLASSBUILDER_FIELD(std::string, BeginString);

	REFLECTION_CLASSBUILDER_END(CowboyMinigameProperties);
}
