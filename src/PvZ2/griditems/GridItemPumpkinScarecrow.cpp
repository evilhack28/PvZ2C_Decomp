//
//  GridItemPumpkinScarecrow.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemPumpkinScarecrow.h"

GridItemPumpkinScarecrow::~GridItemPumpkinScarecrow()
{
}

GridItemPumpkinScarecrowProps::~GridItemPumpkinScarecrowProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemPumpkinScarecrow);

void GridItemPumpkinScarecrow::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemPumpkinScarecrow);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_damageState);
	REFLECTION_CLASSBUILDER_END(GridItemPumpkinScarecrow);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemPumpkinScarecrowProps);

void GridItemPumpkinScarecrowProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemPumpkinScarecrowProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, HitpointsPercentSeparators);
		REFLECTION_CLASSBUILDER_FIELD(float, BirdEnterInterval);
	REFLECTION_CLASSBUILDER_END(GridItemPumpkinScarecrowProps);
}
