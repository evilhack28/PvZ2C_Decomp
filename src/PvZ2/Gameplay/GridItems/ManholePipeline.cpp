//
//  ManholePipeline.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ManholePipeline.h"

ManholePipeline::~ManholePipeline()
{
}

ManholePipelineProps::ManholePipelineProps()
{
}

ManholePipelineProps::~ManholePipelineProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ManholePipelineProps);

void ManholePipelineProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ManholePipelineProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::string, ImageRes);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, ArtCenter);
	REFLECTION_CLASSBUILDER_END(ManholePipelineProps);
}
