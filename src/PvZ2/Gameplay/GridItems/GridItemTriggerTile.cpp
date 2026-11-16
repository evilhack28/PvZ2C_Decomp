//
//  GridItemTriggerTile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemTriggerTile.h"

GridItemTriggerTile::GridItemTriggerTile()
{
}

GridItemTriggerTile::~GridItemTriggerTile()
{
}

GridItemTriggerTileProps::~GridItemTriggerTileProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemTriggerTile);

void GridItemTriggerTile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemTriggerTile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextTriggerTime);
	REFLECTION_CLASSBUILDER_END(GridItemTriggerTile);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemTriggerTileProps);

#include "GridItemTriggerTile.h"
bool GridItemTriggerTile::CanTriggerTile()
{
	return GridItemTriggerTile::isTimeForNextTrigger();
}

void GridItemTriggerTile::handleTargetCollisions(const std::vector<BoardEntity*>& i_entities)
{
}
