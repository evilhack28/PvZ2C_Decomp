//
//  BeghouledZombieSpawner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BeghouledZombieSpawner.h"

BeghouledZombieSpawnerProperties::BeghouledZombieSpawnerProperties()
{
}

BeghouledZombieSpawnerProperties::~BeghouledZombieSpawnerProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BeghouledZombieSpawnerProperties);

void BeghouledZombieSpawnerProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MatchStageMap);
	REFLECTION_CLASSBUILDER_END(MatchStageMap);

	REFLECTION_CLASSBUILDER_BEGIN(BeghouledZombieSpawnerProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SimpleZombieSpawnerProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<MatchStageMap>, MatchCountsToStageAdvance);
	REFLECTION_CLASSBUILDER_END(BeghouledZombieSpawnerProperties);
}
