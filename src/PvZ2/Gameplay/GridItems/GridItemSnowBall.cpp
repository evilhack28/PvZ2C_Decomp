//
//  GridItemSnowBall.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemSnowBall.h"

GridItemSnowBall::GridItemSnowBall()
{
}

GridItemSnowBall::~GridItemSnowBall()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSnowBall);

void GridItemSnowBall::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSnowBall);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTarget);

		REFLECTION_CLASSBUILDER_FIELD(Point, targetPoint);
	REFLECTION_CLASSBUILDER_END(GridItemSnowBall);
}
