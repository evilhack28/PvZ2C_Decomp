//
//  GridItemZombieTent.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemZombieTent.h"

GridItemZombieTent::~GridItemZombieTent()
{
}

GridItemZombieTentProps::GridItemZombieTentProps()
{
	ZombieSpawnPointOffset = -80;
}

GridItemZombieTentProps::~GridItemZombieTentProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieTent);

void GridItemZombieTent::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieTent);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

		REFLECTION_CLASSBUILDER_FIELD(EntityComponent_GroundEffect, m_groundEffect);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextSpawnTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasPlayedDeathAnim);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<TentZombieWeights>, m_zombieTypesToSpawn);
	REFLECTION_CLASSBUILDER_END(GridItemZombieTent);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieTentProps);

void GridItemZombieTentProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieTentProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestonePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(ValueRange, TimeBetweenSpawns);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<TentZombieWeights>, ZombieTypesToSpawn);
		REFLECTION_CLASSBUILDER_FIELD(int, ZombieSpawnPointOffset);
		REFLECTION_CLASSBUILDER_FIELD(float, ProductInterval);
	REFLECTION_CLASSBUILDER_END(GridItemZombieTentProps);
}

PlantingReason GridItemZombieTent::GetCantPlantReason() const
{
	return PLANTING_NOT_ON_TENT;
}
