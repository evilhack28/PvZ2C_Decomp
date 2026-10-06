//
//  GridItemMazeStatue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemMazeStatue.h"

GridItemMazeStatue::~GridItemMazeStatue()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMazeStatue);

void GridItemMazeStatue::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMazeStatue);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTarget);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_startPosition);
		REFLECTION_CLASSBUILDER_FIELD(Point, m_targetPosition);
	REFLECTION_CLASSBUILDER_END(GridItemMazeStatue);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMazeStatueProps);

void GridItemMazeStatueProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMazeStatueProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTargetProps);

		REFLECTION_CLASSBUILDER_FIELD(float, BonusCredit);
	REFLECTION_CLASSBUILDER_END(GridItemMazeStatueProps);
}

void GridItemMazeStatue::onPopAnimCommand(const std::string& i_arg0, pvztime_t i_arg1, const std::string& i_arg2, const std::string& i_arg3)
{
}

void GridItemMazeStatue::tryUpdatePosition()
{
}

#include "GridItemMazeStatue.h"
void GridItemMazeStatue::onNotifyStatueBreak()
{
	 GridItemMazeStatue::BreakStatue();
}

#include "GridItemBoardEntityConditionTarget.h"
bool GridItemMazeStatue::IsControlled() const
{
	return GridItemBoardEntityConditionTarget::IsControlled();
}

bool GridItemMazeStatue::IsDamageable() const
{
	return false;
}

bool GridItemMazeStatue::CanBeTargetedBy(const BoardEntity* i_arg) const
{
	return false;
}

bool GridItemMazeStatue::CollidesWithType(const CollisionTypeFlags i_arg) const
{
	return false;
}
