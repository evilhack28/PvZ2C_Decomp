//
//  GridItemHeianBoxPlantfood.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemHeianBox.h"

GridItemHeianBoxPlantfood::~GridItemHeianBoxPlantfood()
{
}

GridItemHeianBoxPlantfoodProps::~GridItemHeianBoxPlantfoodProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHeianBoxPlantfood);

void GridItemHeianBoxPlantfood::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeianBoxPlantfood);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemHeianBox);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_endTime);

	REFLECTION_CLASSBUILDER_END(GridItemHeianBoxPlantfood);
}
