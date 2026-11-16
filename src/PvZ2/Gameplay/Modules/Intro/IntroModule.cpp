//
//  IntroModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "IntroModule.h"

IntroModule::~IntroModule()
{
}

IntroModuleProperties::IntroModuleProperties()
{
}

IntroModuleProperties::~IntroModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(IntroModule);

void IntroModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(IntroModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(IntroModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(IntroModuleProperties);

void IntroModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(IntroModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(IntroModuleProperties);
}
