//
//  GridItemGravestone.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGravestone.h"

GridItemGravestone::~GridItemGravestone()
{
}

GridItemGravestonePropertySheet::~GridItemGravestonePropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGravestone);

void GridItemGravestone::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGravestone);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(float, m_eatenProgress);
		REFLECTION_CLASSBUILDER_FIELD(EntityComponent_GroundEffect, m_groundEffect);
	REFLECTION_CLASSBUILDER_END(GridItemGravestone);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGravestonePropertySheet);

void GridItemGravestonePropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGravestonePropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(int8, DamageStateCount);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, ArtCenter);
		REFLECTION_CLASSBUILDER_FIELD(float, GraveBusterEatTimeOveride);
		REFLECTION_CLASSBUILDER_FIELD(Point, GridExtents);
	REFLECTION_CLASSBUILDER_END(GridItemGravestonePropertySheet);
}
