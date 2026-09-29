//
//  GridItemVase.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemVase.h"

GridItemVaseProps::GridItemVaseProps()
{
}

GridItemVaseProps::~GridItemVaseProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemVase);

void GridItemVase::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemVase);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_flags);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_allowPreGameplayInteraction);
		REFLECTION_CLASSBUILDER_FIELD(EntityComponent_GroundEffect, m_groundEffect);
	REFLECTION_CLASSBUILDER_END(GridItemVase);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemVaseProps);

void GridItemVaseProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemVaseProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemPropertySheet);

	REFLECTION_CLASSBUILDER_END(GridItemVaseProps);
}
