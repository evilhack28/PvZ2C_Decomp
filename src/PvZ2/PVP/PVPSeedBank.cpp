//
//  PVPSeedBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PVPSeedBank.h"
#include "PVPSeedBankModule.h"

PVPSeedBank::~PVPSeedBank()
{
}

PVPSeedBankProperties::~PVPSeedBankProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVPSeedBank);

void PVPSeedBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVPSeedBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SeedBankNew);

	REFLECTION_CLASSBUILDER_END(PVPSeedBank);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVPSeedBankProperties);

void PVPSeedBankProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVPSeedSkill);
		REFLECTION_CLASSBUILDER_FIELD(std::string, SkillName);
	REFLECTION_CLASSBUILDER_END(PVPSeedSkill);

	REFLECTION_CLASSBUILDER_BEGIN(PVPSeedPlant);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantName);
	REFLECTION_CLASSBUILDER_END(PVPSeedPlant);

	REFLECTION_CLASSBUILDER_BEGIN(PVPSeedZombie);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ZombieName);
		REFLECTION_CLASSBUILDER_FIELD(int, NeedZoneLevel);
	REFLECTION_CLASSBUILDER_END(PVPSeedZombie);

	REFLECTION_CLASSBUILDER_BEGIN(PVPSeedBankProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SeedBankProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<PVPSeedSkill>, SkillList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PVPSeedPlant>, PlantList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PVPSeedZombie>, ZombieList);
	REFLECTION_CLASSBUILDER_END(PVPSeedBankProperties);
}

void PVPSeedBank::fillSeedPackets()
{
}

void PVPSeedBank::registerForEvents()
{
}
