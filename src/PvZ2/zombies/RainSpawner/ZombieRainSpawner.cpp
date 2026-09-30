//
//  ZombieRainSpawner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WaveActionSpawnZombies.h"

ZombieRainSpawner::~ZombieRainSpawner()
{
}

ZombieRainSpawnerProps::~ZombieRainSpawnerProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieRainSpawner);

void ZombieRainSpawner::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieRainSpawner);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSpawnerAction);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<Loot>, m_zombieLoot);
	REFLECTION_CLASSBUILDER_END(ZombieRainSpawner);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieRainSpawnerProps);

void ZombieRainSpawnerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieRainSpawnerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSpawnerActionProps);

	REFLECTION_CLASSBUILDER_END(ZombieRainSpawnerProps);
}

void ZombieRainSpawner::SetLoot(const std::vector<Loot>& i_loot)
{
	m_zombieLoot = i_loot;
}

SexyString ZombieRainSpawnerProps::GetWaveStartMessage() const
{
	return ToWString(WaveStartMessage);
}

