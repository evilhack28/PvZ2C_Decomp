//
//  GridItemFestivalZombieTent.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemZombieTent.h"

GridItemFestivalZombieTent::~GridItemFestivalZombieTent()
{
}

GridItemFestivalZombieTentProps::~GridItemFestivalZombieTentProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFestivalZombieTent);

void GridItemFestivalZombieTent::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemFestivalZombieTent);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

		REFLECTION_CLASSBUILDER_FIELD(EntityComponent_GroundEffect, m_groundEffect);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextSpawnTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasPlayedDeathAnim);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<TentZombieWeights>, m_zombieTypesToSpawn);
	REFLECTION_CLASSBUILDER_END(GridItemFestivalZombieTent);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFestivalZombieTentProps);

void GridItemFestivalZombieTentProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TentZombieTranStruct);
	REFLECTION_CLASSBUILDER_END(TentZombieTranStruct);

	REFLECTION_CLASSBUILDER_BEGIN(GridItemFestivalZombieTentProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestonePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(ValueRange, TimeBetweenSpawns);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<TentZombieWeights>, ZombieTypesToSpawn);
		REFLECTION_CLASSBUILDER_FIELD(int, ZombieSpawnPointOffset);
		REFLECTION_CLASSBUILDER_FIELD(float, ProductInterval);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<TentZombieTranStruct>, ZombieTransform);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ZombieSpawnOnDestory);
	REFLECTION_CLASSBUILDER_END(GridItemFestivalZombieTentProps);
}

PlantingReason GridItemFestivalZombieTent::GetCantPlantReason() const
{
	return (PlantingReason)23;
}
