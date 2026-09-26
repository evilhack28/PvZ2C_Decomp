//
//  DaveTaskConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DaveTaskConfig.h"

DaveTaskConfig::DaveTaskConfig()
{
}

DaveTaskConfig::~DaveTaskConfig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DaveTaskConfig);

void DaveTaskConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DaveTaskConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_FIELD(int, DaveTaskVersion);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<RtEmbeddedPtr<DaveTaskData RT_COMMA PVZDB::TABLE_DAVETREASURE_CONFIG>>, DaveTaskDatas);

	REFLECTION_CLASSBUILDER_END(DaveTaskConfig);
}
