//
//  ArenaPlantModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ArenaPlantModule.h"

bool ArenaPlantModule::preventSave()
{
	return true;
}

ArenaPlantModule::~ArenaPlantModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArenaPlantModule);

void ArenaPlantModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArenaPlantModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntro);

	REFLECTION_CLASSBUILDER_END(ArenaPlantModule);
}

#include "ArenaPlantModule.h"
void ArenaPlantModule::onReadyForBrains()
{
	 ArenaPlantModule::createBrains();
}

bool ArenaPlantModule::suppressReadySetGo() const
{
	return true;
}
