//
//  GridItemPowerTile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemPowerTile.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemPowerTile);

void GridItemPowerTile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemPowerTile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isPlantFoodActive);
	REFLECTION_CLASSBUILDER_END(GridItemPowerTile);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemPowerTileProps);

#include "GridItemPowerTile.h"
void GridItemPowerTile::onRegionChanged(class BoardRegion* i_arg)
{
	 GridItemPowerTile::updateVisibility();
}
