//
//  GridItemRunningSubwayObstacleAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RunningSubway.h"

GridItemRunningSubwayObstacleAnimRig::GridItemRunningSubwayObstacleAnimRig()
{
}

GridItemRunningSubwayObstacleAnimRig::~GridItemRunningSubwayObstacleAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRunningSubwayObstacleAnimRig);

void GridItemRunningSubwayObstacleAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRunningSubwayObstacleAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemRunningSubwayObjectAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemRunningSubwayObstacleAnimRig);
}
