//
//  RainDarkModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "RainDarkModule.h"

RainDarkModule::RainDarkModule()
{
}

RainDarkModule::~RainDarkModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RainDarkModule);

void RainDarkModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RainDarkModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_numDarkDropped);
	REFLECTION_CLASSBUILDER_END(RainDarkModule);
}
