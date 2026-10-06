//
//  DropShipModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DropShipModule.h"

void DropShipModule::unregisterForEvents()
{
}

DropShipModule::DropShipModule()
{
}

DropShipModule::~DropShipModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DropShipModule);

void DropShipModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DropShipModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(DropShipModule);
}

void DropShipModule::initializeModule()
{
}

void DropShipModule::OnUpdate()
{
}
