//
//  PerkHandlerModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PerkHandlerModule.h"

PerkHandlerModule::PerkHandlerModule()
{
}

PerkHandlerModuleProperties::PerkHandlerModuleProperties()
{
}

PerkHandlerModuleProperties::~PerkHandlerModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PerkHandlerModule);

void PerkHandlerModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PerkHandlerModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(PerkHandlerModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PerkHandlerModuleProperties);

void PerkHandlerModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PerkHandlerModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(PerkHandlerModuleProperties);
}
