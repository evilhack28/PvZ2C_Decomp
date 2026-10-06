//
//  GridItemRunningSubwayCoin.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RunningSubway.h"

GridItemRunningSubwayCoin::GridItemRunningSubwayCoin()
{
}

GridItemRunningSubwayCoin::~GridItemRunningSubwayCoin()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRunningSubwayCoin);

void GridItemRunningSubwayCoin::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRunningSubwayCoin);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemRunningSubwayObject);

	REFLECTION_CLASSBUILDER_END(GridItemRunningSubwayCoin);
}
