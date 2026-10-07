//
//  GridItemHeianBoxPlantfoodAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemHeianBox.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

GridItemHeianBoxPlantfoodAnimRig::GridItemHeianBoxPlantfoodAnimRig()
{
}

GridItemHeianBoxPlantfoodAnimRig::~GridItemHeianBoxPlantfoodAnimRig()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(GridItemHeianBoxPlantfoodAnimRig);

void GridItemHeianBoxPlantfoodAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemHeianBoxPlantfoodAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemHeianBoxAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemHeianBoxPlantfoodAnimRig);
}
