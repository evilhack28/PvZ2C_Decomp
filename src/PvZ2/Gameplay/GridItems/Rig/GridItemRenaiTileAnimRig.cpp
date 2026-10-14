//
//  GridItemRenaiTileAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemRenaiTile.h"

GridItemRenaiTileAnimRig::GridItemRenaiTileAnimRig()
{
}

GridItemRenaiTileAnimRig::~GridItemRenaiTileAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRenaiTileAnimRig);

void GridItemRenaiTileAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRenaiTileAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemRenaiTileAnimRig);
}
