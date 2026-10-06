//
//  CamelMinigame.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CamelMinigame.h"

CamelMinigameProperties::~CamelMinigameProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CamelMinigameProperties);

void CamelMinigameProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CamelMinigameProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

	REFLECTION_CLASSBUILDER_FIELD(bool, ShowTutorial);
	REFLECTION_CLASSBUILDER_FIELD(int, CardTypesUsed);

	REFLECTION_CLASSBUILDER_END(CamelMinigameProperties);
}
