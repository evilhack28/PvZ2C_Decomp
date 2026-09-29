//
//  GridItemGridRegionAreaOfEffectTrap.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGridRegionAreaOfEffectTrap.h"

GridItemGridRegionAreaOfEffectTrap::~GridItemGridRegionAreaOfEffectTrap()
{
}

GridItemGridRegionAreaOfEffectTrapProps::~GridItemGridRegionAreaOfEffectTrapProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGridRegionAreaOfEffectTrap);

void GridItemGridRegionAreaOfEffectTrap::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGridRegionAreaOfEffectTrap);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemTriggerTile);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextSpawnTime);
		REFLECTION_CLASSBUILDER_FIELD(int32_t, m_currentState);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<Sexy::Point>, m_gridLocationsLeftToSpawn);
	REFLECTION_CLASSBUILDER_END(GridItemGridRegionAreaOfEffectTrap);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGridRegionAreaOfEffectTrapProps);

void GridItemGridRegionAreaOfEffectTrapProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGridRegionAreaOfEffectTrapProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemTriggerTileProps);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, TimeBetweenDamageEffectSpawnsInSeconds);
	REFLECTION_CLASSBUILDER_END(GridItemGridRegionAreaOfEffectTrapProps);
}
