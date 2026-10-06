//
//  GridItemObstacle.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "IntroWorldCup.h"

GridItemObstacle::GridItemObstacle()
{
}

GridItemObstacle::~GridItemObstacle()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemObstacle);

void GridItemObstacle::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemObstacle);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemObstacle);
}

bool GridItemObstacle::CanBeTargetedBy(const BoardEntity* i_arg) const
{
	return false;
}
