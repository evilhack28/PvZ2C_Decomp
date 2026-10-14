//
//  GridItemHeianBoxLevelUp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemHeianBox.h"

GridItemHeianBoxLevelUp::GridItemHeianBoxLevelUp()
{
}

GridItemHeianBoxLevelUp::~GridItemHeianBoxLevelUp()
{
}

GridItemHeianBoxLevelUpProps::~GridItemHeianBoxLevelUpProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHeianBoxLevelUp);

void GridItemHeianBoxLevelUp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeianBoxLevelUp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemHeianBox);

	REFLECTION_CLASSBUILDER_END(GridItemHeianBoxLevelUp);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemHeianBoxLevelUpProps);

void GridItemHeianBoxLevelUpProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeianBoxLevelUpProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemHeianBoxProps);

		REFLECTION_CLASSBUILDER_FIELD(int, AddLevel);
		REFLECTION_CLASSBUILDER_FIELD(PlantingRestrictionSet, DisabledPlants);
	REFLECTION_CLASSBUILDER_END(GridItemHeianBoxLevelUpProps);
}
