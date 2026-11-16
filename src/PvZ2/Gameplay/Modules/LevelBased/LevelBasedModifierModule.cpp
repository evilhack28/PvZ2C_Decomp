//
//  LevelBasedModifierModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "LevelBasedModifierModule.h"

LevelBasedModifierModule::~LevelBasedModifierModule()
{
}

LevelBasedModifierModuleProps::~LevelBasedModifierModuleProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LevelBasedModifierModule);

void LevelBasedModifierModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LevelBasedModifierModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(LevelBasedModifierModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LevelBasedModifierModuleProps);

void LevelBasedModifierModuleProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LevelBasedModifierModuleProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<std::vector<float>>, Values);

	REFLECTION_CLASSBUILDER_END(LevelBasedModifierModuleProps);
}

void LevelBasedModifierModule::postInitialize()
{
}

void LevelBasedModifierModule::registerForEvents()
{
}

LevelBasedModifierModule::LevelBasedModifierModule()
{
	m_level = 1;
	m_type = (decltype(m_type))3;
}
