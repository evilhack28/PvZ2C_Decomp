//
//  RunningSubwayStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "RunningSubway.h"
#include "StageModule.h"
#include "ReflectionBuilder.h"

RunningSubwayStage::~RunningSubwayStage()
{
}

RT_CLASS_IMPLEMENT(RunningSubwayStage);

void RunningSubwayStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RunningSubwayStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

		REFLECTION_CLASSBUILDER_FIELD(int, m_offset_x);
		REFLECTION_CLASSBUILDER_FIELD(float, m_rollValue);
	REFLECTION_CLASSBUILDER_END(RunningSubwayStage);
}

void RunningSubwayStage::onLevelLoaded()
{
	StageModule::onLevelLoaded();
}

void RunningSubwayStage::initializeModule()
{
	StageModule::initializeModule();
}

void RunningSubwayStage::onGameplayStarted()
{
	RunningSubwayStage::generateDisabledRegion();
}
