//
//  GridItemFairyTaleFog.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "FairyTaleFogWaveAction.h"

GridItemFairyTaleFog::~GridItemFairyTaleFog()
{
}

GridItemFairyTaleFogProps::~GridItemFairyTaleFogProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFairyTaleFog);

void GridItemFairyTaleFog::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FogMovingData);
		REFLECTION_CLASSBUILDER_FIELD(float, m_movingTime);
	REFLECTION_CLASSBUILDER_END(FogMovingData);

	REFLECTION_CLASSBUILDER_BEGIN(GridItemFairyTaleFog);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTarget);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_creationTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(FogMovingData, m_movingData);
	REFLECTION_CLASSBUILDER_END(GridItemFairyTaleFog);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFairyTaleFogProps);

void GridItemFairyTaleFogProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemFairyTaleFogProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTargetProps);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, Lifetime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ZombieBlacklist);
		REFLECTION_CLASSBUILDER_FIELD(ZombieConditions, ConditionApplied);
	REFLECTION_CLASSBUILDER_END(GridItemFairyTaleFogProps);
}
