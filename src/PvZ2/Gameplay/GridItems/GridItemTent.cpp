//
//  GridItemTent.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityImpPorter.h"

GridItemTent::GridItemTent()
{
	m_hasPlayedDeathAnim = 0;
}

GridItemTent::~GridItemTent()
{
}

GridItemTentProps::GridItemTentProps()
{
	ZombieSpawnPointOffset = -80;
}

GridItemTentProps::~GridItemTentProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemTent);

void GridItemTent::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemTent);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

		REFLECTION_CLASSBUILDER_FIELD(EntityComponent_GroundEffect, m_groundEffect);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextSpawnTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasPlayedDeathAnim);
	REFLECTION_CLASSBUILDER_END(GridItemTent);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemTentProps);

void GridItemTentProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemTentProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestonePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(ValueRange, TimeBetweenSpawns);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<BasicZombieWeights>, ZombieTypesToSpawn);
		REFLECTION_CLASSBUILDER_FIELD(int, ZombieSpawnPointOffset);
	REFLECTION_CLASSBUILDER_END(GridItemTentProps);
}

PlantingReason GridItemTent::GetCantPlantReason() const
{
	return PLANTING_NOT_ON_TENT;
}
