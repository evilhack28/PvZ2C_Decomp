//
//  StarChallengeSaveMowers.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "StarChallengeSaveMowers.h"

StarChallengeSaveMowers::~StarChallengeSaveMowers()
{
}

StarChallengeSaveMowersProps::~StarChallengeSaveMowersProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeSaveMowers);

void StarChallengeSaveMowers::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeSaveMowers);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Challenge);

	REFLECTION_CLASSBUILDER_END(StarChallengeSaveMowers);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeSaveMowersProps);

void StarChallengeSaveMowersProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeSaveMowersProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(StarChallengeSaveMowersProps);
}
