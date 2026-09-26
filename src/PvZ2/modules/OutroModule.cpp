//
//  OutroModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "OutroModule.h"

OutroModule::OutroModule()
{
}

OutroModule::~OutroModule()
{
}

OutroModuleProperties::OutroModuleProperties()
{
}

OutroModuleProperties::~OutroModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(OutroModule);

void OutroModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(OutroModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(OutroModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(OutroModuleProperties);

void OutroModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(OutroModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(OutroModuleProperties);
}
