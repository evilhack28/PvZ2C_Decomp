//
//  BowlingMinigame.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BowlingMinigame.h"

BowlingMinigameProperties::~BowlingMinigameProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BowlingMinigameProperties);

void BowlingMinigameProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BowlingMinigameProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(BowlingMinigameProperties);
}
