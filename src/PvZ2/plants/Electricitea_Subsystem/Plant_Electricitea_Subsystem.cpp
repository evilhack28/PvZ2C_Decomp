//
//  Plant_Electricitea_Subsystem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Electricitea_Subsystem.h"

PlantElectriciteaSubSystem::PlantElectriciteaSubSystem()
{
}

PlantElectriciteaSubSystem::~PlantElectriciteaSubSystem()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantElectriciteaSubSystem);

void PlantElectriciteaSubSystem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SparkingZombieTracker);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, Zombie);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, RootPosition);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, BurstTime);
		REFLECTION_CLASSBUILDER_FIELD(float, ResistancePiercing);
		REFLECTION_CLASSBUILDER_FIELD(ElectriciteaBurstProperties, Props);
	REFLECTION_CLASSBUILDER_END(SparkingZombieTracker);

	REFLECTION_CLASSBUILDER_BEGIN(PlantElectriciteaSubSystem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameSubSystem);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<SparkingZombieTracker>, m_sparkingZombies);
	REFLECTION_CLASSBUILDER_END(PlantElectriciteaSubSystem);
}
