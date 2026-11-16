//
//  StarChallengeSimultaneousPlants.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StarChallengeSimultaneousPlants.h"

StarChallengeSimultaneousPlants::~StarChallengeSimultaneousPlants()
{
}

StarChallengeSimultaneousPlantsProps::~StarChallengeSimultaneousPlantsProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeSimultaneousPlants);

void StarChallengeSimultaneousPlants::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeSimultaneousPlants);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Challenge);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<UIWidget>, m_plantCountUI);
	REFLECTION_CLASSBUILDER_END(StarChallengeSimultaneousPlants);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeSimultaneousPlantsProps);

void StarChallengeSimultaneousPlantsProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeSimultaneousPlantsProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(int, MaximumPlants);
	REFLECTION_CLASSBUILDER_END(StarChallengeSimultaneousPlantsProps);
}
