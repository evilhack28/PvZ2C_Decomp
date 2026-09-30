//
//  ActionSubSystem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ActionSubSystem.h"

void ActionSubSystem::registerForEvents()
{
}

ActionSubSystem::ActionSubSystem()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ActionSubSystem);

void ActionSubSystem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ActionSubSystem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameSubSystem);

	REFLECTION_CLASSBUILDER_END(ActionSubSystem);
}

void ActionSubSystem::onInitialized()
{
}
