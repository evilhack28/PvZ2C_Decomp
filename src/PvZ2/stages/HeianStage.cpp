//
//  HeianStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "HeianStage.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HeianStage);
void HeianStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HeianStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(HeianStage);
}

RT_CLASS_IMPLEMENT(HeianStageProperties);
void HeianStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HeianStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(HeianStageProperties);
}

void HeianStage::initializeModule()
{
	StageModule::initializeModule();
}

void HeianStage::registerForEvents()
{
	StageModule::registerForEvents();
}
