//
//  GridItemRenaiRoller.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemRenaiRoller.h"

GridItemRenaiRoller::~GridItemRenaiRoller()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRenaiRoller);

void GridItemRenaiRoller::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRenaiRoller);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTarget);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_affectTime);
	REFLECTION_CLASSBUILDER_END(GridItemRenaiRoller);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRenaiRollerProps);

void GridItemRenaiRollerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRenaiRollerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTargetProps);

	REFLECTION_CLASSBUILDER_END(GridItemRenaiRollerProps);
}

#include "GridItemRenaiRoller.h"
void GridItemRenaiRoller::stopMoving()
{
	 GridItemRenaiRoller::checkStopLocation();
}

void GridItemRenaiRoller::onPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params)
{
}

#include "GridItem.h"
void GridItemRenaiRoller::registerForEvents()
{
	 GridItem::registerForEvents();
}

#include "GridItemRenaiRoller.h"
void GridItemRenaiRoller::onLinkedOnAnimDone(const std::string& i_animLabelName)
{
	 GridItemRenaiRoller::playLinkedLoopAnim();
}

void GridItemRenaiRoller::onRollerLoopAnimDone(const std::string& i_animLabelName)
{
}

bool GridItemRenaiRoller::IsDamageable() const
{
	return false;
}

bool GridItemRenaiRoller::CanBeTargetedBy(const BoardEntity* i_entity) const
{
	return false;
}

bool GridItemRenaiRoller::CollidesWithType(const CollisionTypeFlags i_collisionTypes) const
{
	return false;
}

bool GridItemRenaiRoller::ShouldDrawShadow() const
{
	return true;
}

PlantingReason GridItemRenaiRoller::GetCantPlantReason() const
{
	return PLANTING_NOT_ON_ROLLER;
}
