//
//  SecurityGourdModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SecurityGourdModule.h"

SecurityGourdModule::~SecurityGourdModule()
{
}

SecurityGourdModuleProperties::~SecurityGourdModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SecurityGourdModule);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SecurityGourdModuleProperties);

void SecurityGourdModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SecurityGourdModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(bool, ResetPlantCooldowns);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ZombieClassKillWhitelist);
	REFLECTION_CLASSBUILDER_END(SecurityGourdModuleProperties);
}

#include "SecurityGourdModule.h"
void SecurityGourdModule::initializeModule()
{
	 SecurityGourdModule::initializeStateMachine();
}
