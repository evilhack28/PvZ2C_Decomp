//
//  PVZ1SeeingStarsModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PVZ1SeeingStarsModule.h"

PVZ1SeeingStarsModuleProperties::PVZ1SeeingStarsModuleProperties()
{
}

PVZ1SeeingStarsModuleProperties::~PVZ1SeeingStarsModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZ1SeeingStarsModule);

void PVZ1SeeingStarsModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZ1SeeingStarsModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(PVZ1SeeingStarsModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZ1SeeingStarsModuleProperties);

void PVZ1SeeingStarsModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MatchPlantData);
		REFLECTION_CLASSBUILDER_FIELD(std::string, MatchTypeName);
	REFLECTION_CLASSBUILDER_END(MatchPlantData);

	REFLECTION_CLASSBUILDER_BEGIN(PVZ1SeeingStarsModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<MatchPlantData>, MatchPlants);
		REFLECTION_CLASSBUILDER_FIELD(int, CycleIndex);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, SettlementDuration);
	REFLECTION_CLASSBUILDER_END(PVZ1SeeingStarsModuleProperties);
}

void PVZ1SeeingStarsModule::postInitialize()
{
}

void PVZ1SeeingStarsModule::initializeModule()
{
}

void PVZ1SeeingStarsModule::unregisterForEvents()
{
}
