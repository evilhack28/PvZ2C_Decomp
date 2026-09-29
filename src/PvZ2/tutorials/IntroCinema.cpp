//
//  IntroCinema.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "IntroCinema.h"

IntroCinema::~IntroCinema()
{
}

IntroCinemaProperties::IntroCinemaProperties()
{
}

IntroCinemaProperties::~IntroCinemaProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(IntroCinema);

void IntroCinema::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSpawnLoc);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<const ZombieType>, ZombieType);
	REFLECTION_CLASSBUILDER_END(ZombieSpawnLoc);

	REFLECTION_CLASSBUILDER_BEGIN(PFTrigger);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, TimeToPlantfood);
		REFLECTION_CLASSBUILDER_FIELD(bool, Triggered);
	REFLECTION_CLASSBUILDER_END(PFTrigger);

	REFLECTION_CLASSBUILDER_BEGIN(IntroCinema);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntro);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<const ZombieType> >, m_zombiesToUse);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<const PlantType> >, m_plantsToUse);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_introState);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PFTrigger>, m_plantfoodTriggers);
		REFLECTION_CLASSBUILDER_FIELD(int, m_plantsPlantfooded);
	REFLECTION_CLASSBUILDER_END(IntroCinema);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(IntroCinemaProperties);

void IntroCinemaProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(IntroCinemaProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

	REFLECTION_CLASSBUILDER_END(IntroCinemaProperties);
}
