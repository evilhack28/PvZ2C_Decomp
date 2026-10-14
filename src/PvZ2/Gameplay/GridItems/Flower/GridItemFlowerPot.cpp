//
//  GridItemFlowerPot.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_FlowerPot.h"

GridItemFlowerPot::~GridItemFlowerPot()
{
}

GridItemFlowerPotProps::~GridItemFlowerPotProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFlowerPot);

void GridItemFlowerPot::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemFlowerPot);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isDuplicate);
		REFLECTION_CLASSBUILDER_FIELD(EntityComponent_GroundEffect, m_groundEffect);
	REFLECTION_CLASSBUILDER_END(GridItemFlowerPot);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFlowerPotProps);

void GridItemFlowerPotProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemFlowerPotProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(PlantRestrictionSet, PlantsWhichCannotBePlantedOnFlowerPots);
	REFLECTION_CLASSBUILDER_END(GridItemFlowerPotProps);
}
