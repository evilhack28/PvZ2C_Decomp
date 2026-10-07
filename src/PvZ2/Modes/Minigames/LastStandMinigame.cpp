//
//  LastStandMinigame.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "LastStandMinigame.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

LastStandMinigameProperties::~LastStandMinigameProperties()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(LastStandMinigameProperties);

void LastStandMinigameProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LastStandMinigameProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantTag>, DisablePlantTags);

	REFLECTION_CLASSBUILDER_END(LastStandMinigameProperties);
}
