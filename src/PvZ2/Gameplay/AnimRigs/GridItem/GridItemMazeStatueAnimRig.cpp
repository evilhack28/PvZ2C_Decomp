//
//  GridItemMazeStatueAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemMazeStatue.h"

GridItemMazeStatueAnimRig::GridItemMazeStatueAnimRig()
{
}

GridItemMazeStatueAnimRig::~GridItemMazeStatueAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMazeStatueAnimRig);

void GridItemMazeStatueAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMazeStatueAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemMazeStatueAnimRig);
}
