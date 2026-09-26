//
//  GridItemRunningSubwayObstacle.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RunningSubway.h"

GridItemRunningSubwayObstacle::~GridItemRunningSubwayObstacle()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRunningSubwayObstacle);

void GridItemRunningSubwayObstacle::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRunningSubwayObstacle);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemRunningSubwayObject);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_hasHitted);

	REFLECTION_CLASSBUILDER_END(GridItemRunningSubwayObstacle);
}
