//
//  HeianWindModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HeianWindModule.h"

HeianWindModule::~HeianWindModule()
{
}

HeianWindModuleProperties::~HeianWindModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HeianWindModule);

void HeianWindModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HeianWindModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<WindInfo>, m_currentWinds);
		REFLECTION_CLASSBUILDER_FIELD(int, m_currentWindState);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextWind);
	REFLECTION_CLASSBUILDER_END(HeianWindModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HeianWindModuleProperties);

void HeianWindModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HeianWindModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<WaveWindInfo>, WaveWindInfos);
	REFLECTION_CLASSBUILDER_END(HeianWindModuleProperties);
}

void HeianWindModule::onLoadComplete()
{
}

void HeianWindModule::gameplayStarted()
{
}

void HeianWindModule::initializeModule()
{
}

#include "HeianWindModule.h"
void HeianWindModule::onUpdate()
{
	 HeianWindModule::updateStates();
}
