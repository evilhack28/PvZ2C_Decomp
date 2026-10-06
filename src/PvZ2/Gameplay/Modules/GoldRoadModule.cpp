//
//  GoldRoadModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GoldRoadModule.h"

void GoldRoadModule::onGameplayStarted()
{
}

GoldRoadModule::GoldRoadModule()
{
}

GoldRoadModule::~GoldRoadModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GoldRoadModule);

void GoldRoadModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GoldRoadModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(GoldRoadModule);
}

void GoldRoadModule::initializeModule()
{
}
