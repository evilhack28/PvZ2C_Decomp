//
//  GridItemBoardEntityConditionTarget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemBoardEntityConditionTarget.h"

GridItemBoardEntityConditionTarget::~GridItemBoardEntityConditionTarget()
{
}

GridItemBoardEntityConditionTargetProps::~GridItemBoardEntityConditionTargetProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemBoardEntityConditionTarget);

void GridItemBoardEntityConditionTarget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemBoardEntityConditionTarget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTarget);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_owner);
	REFLECTION_CLASSBUILDER_END(GridItemBoardEntityConditionTarget);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemBoardEntityConditionTargetProps);

void GridItemBoardEntityConditionTargetProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemBoardEntityConditionTargetProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTargetProps);

	REFLECTION_CLASSBUILDER_END(GridItemBoardEntityConditionTargetProps);
}
