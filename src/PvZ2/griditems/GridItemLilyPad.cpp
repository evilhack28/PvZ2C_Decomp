//
//  GridItemLilyPad.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_LilyPad.h"

GridItemLilyPad::~GridItemLilyPad()
{
}

GridItemLilyPadProps::~GridItemLilyPadProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemLilyPad);

void GridItemLilyPad::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemLilyPad);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isDuplicate);
	REFLECTION_CLASSBUILDER_END(GridItemLilyPad);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemLilyPadProps);

void GridItemLilyPadProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemLilyPadProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(PlantRestrictionSet, PlantsWhichCannotBePlantedOnLilypads);
	REFLECTION_CLASSBUILDER_END(GridItemLilyPadProps);
}
