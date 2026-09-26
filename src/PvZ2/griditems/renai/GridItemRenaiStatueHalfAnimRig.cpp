//
//  GridItemRenaiStatueHalfAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemRenaiStatue.h"

GridItemRenaiStatueHalfAnimRig::GridItemRenaiStatueHalfAnimRig()
{
}

GridItemRenaiStatueHalfAnimRig::~GridItemRenaiStatueHalfAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRenaiStatueHalfAnimRig);

void GridItemRenaiStatueHalfAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRenaiStatueHalfAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemRenaiStatueAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemRenaiStatueHalfAnimRig);
}
