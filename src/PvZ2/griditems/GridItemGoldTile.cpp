//
//  GridItemGoldTile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGoldTile.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGoldTile);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGoldTileProps);

void GridItemGoldTileProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGoldTileProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, TimeBetweenPlantSpawnedSunDrops);
	REFLECTION_CLASSBUILDER_END(GridItemGoldTileProps);
}

#include "GridItemGoldTile.h"
void GridItemGoldTile::onAnimDone(const std::string& i_arg)
{
	 GridItemGoldTile::playStateAnim();
}
