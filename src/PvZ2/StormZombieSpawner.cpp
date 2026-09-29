//
//  StormZombieSpawner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StormZombieSpawner.h"

StormZombieSpawner::~StormZombieSpawner()
{
}

StormZombieSpawnerProps::~StormZombieSpawnerProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StormZombieSpawner);

void StormZombieSpawner::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StormZombieSpawner);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSpawnerAction);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<Loot>, m_zombieLoot);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<Point>, m_stormTargets);
		REFLECTION_CLASSBUILDER_FIELD(int, m_nextZombieIndex);
	REFLECTION_CLASSBUILDER_END(StormZombieSpawner);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StormZombieSpawnerProps);

void StormZombieSpawner::SetLoot(const std::vector<Loot>& i_loot)
{
	m_zombieLoot = i_loot;
}

