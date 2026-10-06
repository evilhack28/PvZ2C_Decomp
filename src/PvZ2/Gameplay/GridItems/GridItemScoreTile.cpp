//
//  GridItemScoreTile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemScoreTile.h"

GridItemScoreTile::GridItemScoreTile()
{
}

GridItemScoreTile::~GridItemScoreTile()
{
}

GridItemScoreTileProps::~GridItemScoreTileProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemScoreTile);

void GridItemScoreTile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemScoreTile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemScoreTile);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemScoreTileProps);

void GridItemScoreTileProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemScoreTileProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(float, ScoreMultiplier);
	REFLECTION_CLASSBUILDER_END(GridItemScoreTileProps);
}
