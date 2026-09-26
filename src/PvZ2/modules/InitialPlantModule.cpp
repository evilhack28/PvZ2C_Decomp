//
//  InitialPlantModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "InitialPlantModule.h"

InitialPlantModule::InitialPlantModule()
{
}

InitialPlantModule::~InitialPlantModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(InitialPlantModule);

void InitialPlantModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(InitialPlantModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(InitialPlantModule);
}

void InitialPlantModule::initializeModule()
{
}
