//
//  GridItemEliminateShield.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemEliminateShield.h"

void GridItemEliminateShield::updateState()
{
}

void GridItemEliminateShield::onEliminateOnce()
{
}

GridItemEliminateShield::~GridItemEliminateShield()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemEliminateShield);

void GridItemEliminateShield::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemEliminateShield);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemEliminateShield);
}

#include "GridItemAnimation.h"
void GridItemEliminateShield::initializeAnimRig()
{
	 GridItemAnimation::setDefaultAnimRig();
}

#include "GridItemAnimation.h"
void GridItemEliminateShield::onUpdate()
{
	 GridItemAnimation::onUpdate();
}

#include "GridItem.h"
void GridItemEliminateShield::onDestroy()
{
	 GridItem::onDestroy();
}
