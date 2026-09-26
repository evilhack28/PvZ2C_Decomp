//
//  GridItemCraterTimed.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCrater.h"

GridItemCraterTimed::GridItemCraterTimed()
{
}

GridItemCraterTimed::~GridItemCraterTimed()
{
}

GridItemCraterTimedProps::GridItemCraterTimedProps()
{
}

GridItemCraterTimedProps::~GridItemCraterTimedProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCraterTimed);

void GridItemCraterTimed::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCraterTimed);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCrater);

	REFLECTION_CLASSBUILDER_END(GridItemCraterTimed);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCraterTimedProps);

void GridItemCraterTimedProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCraterTimedProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCraterProps);

		REFLECTION_CLASSBUILDER_FIELD(float, Lifetime);
	REFLECTION_CLASSBUILDER_END(GridItemCraterTimedProps);
}
