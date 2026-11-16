//
//  SeedRainModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SeedRainModule.h"

SeedRainModule::SeedRainModule()
{
}

SeedRainModule::~SeedRainModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SeedRainModule);

void SeedRainModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SeedRainModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_TimeRain);
	REFLECTION_CLASSBUILDER_END(SeedRainModule);
}

void SeedRainModule::onLoadComplete()
{
}
