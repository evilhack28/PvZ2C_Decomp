//
//  GridItemZombieBuffTile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemZombieBuffTile.h"

GridItemZombieBuffTile::~GridItemZombieBuffTile()
{
}

GridItemZombieBuffTileProps::~GridItemZombieBuffTileProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieBuffTile);

void GridItemZombieBuffTile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieBuffTile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_creationTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
	REFLECTION_CLASSBUILDER_END(GridItemZombieBuffTile);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieBuffTileProps);

void GridItemZombieBuffTileProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieBuffTileProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, Lifetime);
	REFLECTION_CLASSBUILDER_END(GridItemZombieBuffTileProps);
}

void GridItemZombieBuffTile::doApplyEffect(const BoardEntity* i_arg)
{
}
