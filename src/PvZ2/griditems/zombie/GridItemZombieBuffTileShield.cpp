//
//  GridItemZombieBuffTileShield.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemZombieBuffTile.h"

GridItemZombieBuffTileShield::GridItemZombieBuffTileShield()
{
}

GridItemZombieBuffTileShield::~GridItemZombieBuffTileShield()
{
}

GridItemZombieBuffTileShieldProps::~GridItemZombieBuffTileShieldProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieBuffTileShield);

void GridItemZombieBuffTileShield::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieBuffTileShield);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemZombieBuffTile);

	REFLECTION_CLASSBUILDER_END(GridItemZombieBuffTileShield);
}
