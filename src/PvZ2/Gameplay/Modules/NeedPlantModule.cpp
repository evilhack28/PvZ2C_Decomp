//
//  NeedPlantModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "NeedPlantModule.h"

NeedPlantModule::NeedPlantModule()
{
}

NeedPlantModule::~NeedPlantModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(NeedPlantModule);

void NeedPlantModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NeedPlantModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(NeedPlantModule);
}
