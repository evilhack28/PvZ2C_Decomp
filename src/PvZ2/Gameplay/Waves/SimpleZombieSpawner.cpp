//
//  SimpleZombieSpawner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SimpleZombieSpawner.h"

SimpleZombieSpawnerProperties::SimpleZombieSpawnerProperties()
{
}

SimpleZombieSpawnerProperties::~SimpleZombieSpawnerProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SimpleZombieSpawnerProperties);

void SimpleZombieSpawnerProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSpawnerEntry);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ZombieType);
		REFLECTION_CLASSBUILDER_FIELD(int32, Weight);
	REFLECTION_CLASSBUILDER_END(ZombieSpawnerEntry);

	REFLECTION_CLASSBUILDER_BEGIN(ZSEntryList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ZombieSpawnerEntry>, Types);
		REFLECTION_CLASSBUILDER_FIELD(int32, SpawnCount);
		REFLECTION_CLASSBUILDER_FIELD(float, SpawnDelay);
		REFLECTION_CLASSBUILDER_FIELD(int, PlantFoodInterval);
	REFLECTION_CLASSBUILDER_END(ZSEntryList);

	REFLECTION_CLASSBUILDER_BEGIN(SimpleZombieSpawnerProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ZSEntryList>, Stages);
	REFLECTION_CLASSBUILDER_END(SimpleZombieSpawnerProperties);
}
