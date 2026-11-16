//
//  StarChallengeSaveBombs.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "StarChallengeSaveBombs.h"

StarChallengeSaveBombs::~StarChallengeSaveBombs()
{
}

StarChallengeSaveBombsProps::~StarChallengeSaveBombsProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeSaveBombs);

void StarChallengeSaveBombs::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeSaveBombs);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Challenge);

	REFLECTION_CLASSBUILDER_END(StarChallengeSaveBombs);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeSaveBombsProps);

void StarChallengeSaveBombsProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeSaveBombsProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(StarChallengeSaveBombsProps);
}
