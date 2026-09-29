//
//  GridItemOliveOil.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Olive.h"

GridItemOliveOil::~GridItemOliveOil()
{
}

GridItemOliveOilProps::~GridItemOliveOilProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemOliveOil);

void GridItemOliveOil::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemOliveOil);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(GridItemOliveOilLabel, m_label);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_directBurn);
	REFLECTION_CLASSBUILDER_END(GridItemOliveOil);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemOliveOilProps);

void GridItemOliveOilProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemOliveOilProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

	REFLECTION_CLASSBUILDER_END(GridItemOliveOilProps);
}
