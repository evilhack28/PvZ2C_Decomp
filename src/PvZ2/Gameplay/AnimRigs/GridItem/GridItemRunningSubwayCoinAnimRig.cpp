//
//  GridItemRunningSubwayCoinAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RunningSubway.h"

GridItemRunningSubwayCoinAnimRig::GridItemRunningSubwayCoinAnimRig()
{
}

GridItemRunningSubwayCoinAnimRig::~GridItemRunningSubwayCoinAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRunningSubwayCoinAnimRig);

void GridItemRunningSubwayCoinAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRunningSubwayCoinAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemRunningSubwayObjectAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemRunningSubwayCoinAnimRig);
}
