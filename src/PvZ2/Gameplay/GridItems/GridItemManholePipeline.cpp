//
//  GridItemManholePipeline.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ManholePipeline.h"

GridItemManholePipeline::GridItemManholePipeline()
{
}

GridItemManholePipeline::~GridItemManholePipeline()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemManholePipeline);

void GridItemManholePipeline::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemManholePipeline);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

	REFLECTION_CLASSBUILDER_END(GridItemManholePipeline);
}
