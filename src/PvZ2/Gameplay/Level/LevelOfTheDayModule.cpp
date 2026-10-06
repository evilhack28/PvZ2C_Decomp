//
//  LevelOfTheDayModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "LevelOfTheDayModule.h"

LevelOfTheDayModule::LevelOfTheDayModule()
{
}

LevelOfTheDayModule::~LevelOfTheDayModule()
{
}

LevelOfTheDayModuleProperties::~LevelOfTheDayModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LevelOfTheDayModule);

void LevelOfTheDayModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LevelOfTheDayModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(LevelOfTheDayModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LevelOfTheDayModuleProperties);

void LevelOfTheDayModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LevelOfTheDayModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(LevelOfTheDayModuleProperties);
}

bool LevelOfTheDayModule::preventSave()
{
	return true;
}

void LevelOfTheDayModule::onLevelEnded()
{
}

void LevelOfTheDayModule::onGameplayEnded()
{
}

void LevelOfTheDayModule::initializeModule()
{
}

void LevelOfTheDayModule::onGameplayStarted()
{
}
