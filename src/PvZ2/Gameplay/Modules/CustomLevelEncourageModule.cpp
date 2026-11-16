//
//  CustomLevelEncourageModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "CustomLevelEncourageModule.h"

CustomLevelEncourageModule::CustomLevelEncourageModule()
{
}

CustomLevelEncourageModule::~CustomLevelEncourageModule()
{
}

CustomLevelEncourageModuleProperties::~CustomLevelEncourageModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CustomLevelEncourageModule);

void CustomLevelEncourageModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CustomLevelEncourageModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(CustomLevelEncourageModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CustomLevelEncourageModuleProperties);

void CustomLevelEncourageModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CustomLevelEncourageModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(CustomLevelEncourageModuleProperties);
}
