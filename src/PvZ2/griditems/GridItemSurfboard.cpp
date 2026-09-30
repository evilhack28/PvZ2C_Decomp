//
//  GridItemSurfboard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieBeachSurfer.h"

GridItemSurfboard::GridItemSurfboard()
{
}

GridItemSurfboard::~GridItemSurfboard()
{
}

GridItemSurfboardProps::GridItemSurfboardProps()
{
}

GridItemSurfboardProps::~GridItemSurfboardProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSurfboard);

void GridItemSurfboard::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSurfboard);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

		REFLECTION_CLASSBUILDER_FIELD(EntityComponent_GroundEffect, m_groundEffect);
	REFLECTION_CLASSBUILDER_END(GridItemSurfboard);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSurfboardProps);

void GridItemSurfboardProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSurfboardProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestonePropertySheet);

	REFLECTION_CLASSBUILDER_END(GridItemSurfboardProps);
}

PlantingReason GridItemSurfboard::GetCantPlantReason() const
{
	return (PlantingReason)22;
}

bool GridItemSurfboard::ShouldClipWithWater() const
{
	return true;
}
