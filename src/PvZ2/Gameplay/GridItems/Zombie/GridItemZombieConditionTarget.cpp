//
//  GridItemZombieConditionTarget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemZombieConditionTarget.h"

GridItemZombieConditionTarget::~GridItemZombieConditionTarget()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieConditionTarget);

void GridItemZombieConditionTarget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieConditionTarget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTarget);

		REFLECTION_CLASSBUILDER_FIELD(ZombieConditions, m_conditionToRemoveOnDeath);
		REFLECTION_CLASSBUILDER_FIELD(EntityComponent_GroundEffect, m_groundEffect);
	REFLECTION_CLASSBUILDER_END(GridItemZombieConditionTarget);
}
