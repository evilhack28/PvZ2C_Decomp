//
//  ManholePipelineModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ManholePipelineModule.h"

ManholePipelineModule::ManholePipelineModule()
{
}

ManholePipelineModuleProperties::ManholePipelineModuleProperties()
{
}

ManholePipelineModuleProperties::~ManholePipelineModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ManholePipelineModule);

void ManholePipelineModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ManholePipelineModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ManholePipeline*>, m_piplelineList);
	REFLECTION_CLASSBUILDER_END(ManholePipelineModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ManholePipelineModuleProperties);

void ManholePipelineModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ManholePipelineInfo);
	REFLECTION_CLASSBUILDER_END(ManholePipelineInfo);

	REFLECTION_CLASSBUILDER_BEGIN(ManholePipelineModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ManholePipelineInfo>, PipelineList);
	REFLECTION_CLASSBUILDER_END(ManholePipelineModuleProperties);
}
