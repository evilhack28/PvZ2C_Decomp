//
//  HeroPlantModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "HeroPlantModule.h"

HeroPlantModule::~HeroPlantModule()
{
}

HeroPlantModuleProperties::HeroPlantModuleProperties()
{
}

HeroPlantModuleProperties::~HeroPlantModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HeroPlantModule);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HeroPlantModuleProperties);

void HeroPlantModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HeroPlantModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, LevelBlacklist);
	REFLECTION_CLASSBUILDER_END(HeroPlantModuleProperties);
}
