//
//  GridItemHeianBox.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemHeianBox.h"

GridItemHeianBox::GridItemHeianBox()
{
	m_state = (decltype(m_state))0;
}

GridItemHeianBox::~GridItemHeianBox()
{
}

GridItemHeianBoxProps::GridItemHeianBoxProps()
{
}

GridItemHeianBoxProps::~GridItemHeianBoxProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHeianBox);

void GridItemHeianBox::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeianBox);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
	REFLECTION_CLASSBUILDER_END(GridItemHeianBox);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHeianBoxProps);

void GridItemHeianBoxProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeianBoxProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

	REFLECTION_CLASSBUILDER_END(GridItemHeianBoxProps);
}

void GridItemHeianBox::updateState()
{
}

#include "GridItem.h"
void GridItemHeianBox::registerForEvents()
{
	 GridItem::registerForEvents();
}

bool GridItemHeianBox::OverrideProjectileCollision(Projectile* i_projectile)
{
	return false;
}

bool GridItemHeianBox::CollidesWithType(const CollisionTypeFlags i_collisionTypes) const
{
	return true;
}

PlantingReason GridItemHeianBox::GetCantPlantReason() const
{
	return PLANTING_NEED_FLOWERPOT_FIRST;
}
