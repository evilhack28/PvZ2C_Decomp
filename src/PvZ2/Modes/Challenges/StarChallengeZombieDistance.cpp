//
//  StarChallengeZombieDistance.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StarChallengeZombieDistance.h"

StarChallengeZombieDistance::~StarChallengeZombieDistance()
{
}

StarChallengeZombieDistanceProps::~StarChallengeZombieDistanceProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeZombieDistance);

void StarChallengeZombieDistance::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeZombieDistance);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Challenge);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_goalState);
		REFLECTION_CLASSBUILDER_FIELD(float, m_closestZombie);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Effect_PopAnim> >, m_flowers);
	REFLECTION_CLASSBUILDER_END(StarChallengeZombieDistance);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeZombieDistanceProps);

void StarChallengeZombieDistanceProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeZombieDistanceProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(float, TargetDistance);
	REFLECTION_CLASSBUILDER_END(StarChallengeZombieDistanceProps);
}

void StarChallengeZombieDistance::initializeModule()
{
}
