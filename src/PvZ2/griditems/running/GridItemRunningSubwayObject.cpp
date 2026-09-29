//
//  GridItemRunningSubwayObject.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "RunningSubway.h"

GridItemRunningSubwayObject::GridItemRunningSubwayObject()
{
}

GridItemRunningSubwayObject::~GridItemRunningSubwayObject()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRunningSubwayObject);

void GridItemRunningSubwayObject::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRunningSubwayObject);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTarget);

		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_nextPosition);
	REFLECTION_CLASSBUILDER_END(GridItemRunningSubwayObject);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRunningSubwayObjectProps);

void GridItemRunningSubwayObjectProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRunningSubwayObjectProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTargetProps);

	REFLECTION_CLASSBUILDER_END(GridItemRunningSubwayObjectProps);
}

void GridItemRunningSubwayObject::OnCollide(BoardEntity* i_arg)
{
}
