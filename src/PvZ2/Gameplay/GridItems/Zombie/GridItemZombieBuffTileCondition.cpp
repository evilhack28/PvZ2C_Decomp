//
//  GridItemZombieBuffTileCondition.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemZombieBuffTile.h"

GridItemZombieBuffTileCondition::GridItemZombieBuffTileCondition()
{
}

GridItemZombieBuffTileCondition::~GridItemZombieBuffTileCondition()
{
}

GridItemZombieBuffTileConditionProps::~GridItemZombieBuffTileConditionProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieBuffTileCondition);

void GridItemZombieBuffTileCondition::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieBuffTileCondition);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemZombieBuffTile);

	REFLECTION_CLASSBUILDER_END(GridItemZombieBuffTileCondition);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieBuffTileConditionProps);

void GridItemZombieBuffTileConditionProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieBuffTileConditionProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemZombieBuffTileProps);

		REFLECTION_CLASSBUILDER_FIELD(ZombieConditions, Condition);
		REFLECTION_CLASSBUILDER_FIELD(float, Duration);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnimEffect);
	REFLECTION_CLASSBUILDER_END(GridItemZombieBuffTileConditionProps);
}
