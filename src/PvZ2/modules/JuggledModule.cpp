//
//  JuggledModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "JuggledModule.h"

JuggledModule::JuggledModule()
{
}

JuggledModule::~JuggledModule()
{
}

JuggledModuleProperties::~JuggledModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JuggledModule);

void JuggledModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JuggledModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(JuggledModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JuggledModuleProperties);

void JuggledModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JuggledModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_FIELD(ValueRange, LaunchHeight);
	REFLECTION_CLASSBUILDER_FIELD(int, MaxProjectilesToJuggle);

	REFLECTION_CLASSBUILDER_END(JuggledModuleProperties);
}
