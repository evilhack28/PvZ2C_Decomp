//
//  StarChallengePlantFoodNonuse.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StarChallengePlantFoodNonuse.h"

StarChallengePlantFoodNonuse::StarChallengePlantFoodNonuse()
{
	m_showTip = 1;
}

StarChallengePlantFoodNonuse::~StarChallengePlantFoodNonuse()
{
}

StarChallengePlantFoodNonuseProps::StarChallengePlantFoodNonuseProps()
{
}

StarChallengePlantFoodNonuseProps::~StarChallengePlantFoodNonuseProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengePlantFoodNonuse);

void StarChallengePlantFoodNonuse::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengePlantFoodNonuse);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Challenge);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_showTip);
	REFLECTION_CLASSBUILDER_END(StarChallengePlantFoodNonuse);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengePlantFoodNonuseProps);

void StarChallengePlantFoodNonuseProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengePlantFoodNonuseProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(StarChallengePlantFoodNonuseProps);
}
