//
//  CustomLevelModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "CustomLevelModule.h"

CustomLevelModule::CustomLevelModule()
{
}

CustomLevelModule::~CustomLevelModule()
{
}

CustomLevelModuleProperties::CustomLevelModuleProperties()
{
}

CustomLevelModuleProperties::~CustomLevelModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CustomLevelModule);

void CustomLevelModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CustomLevelModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(CustomLevelModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CustomLevelModuleProperties);

void CustomLevelModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CustomLevelModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(CustomLevelModuleProperties);
}
