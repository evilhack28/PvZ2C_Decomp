//
//  Plant_KiwiFruit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_KiwiFruit.h"

PlantKiwiFruit::PlantKiwiFruit()
{
}

PlantKiwiFruit::~PlantKiwiFruit()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantKiwiFruit);

void PlantKiwiFruit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantKiwiFruit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_tossZombieTimer);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie> >, m_hitZombies);
		REFLECTION_CLASSBUILDER_FIELD(int, m_smallKiwiCount);
	REFLECTION_CLASSBUILDER_END(PlantKiwiFruit);
}

bool PlantKiwiFruit::CanApplyPlantfood()
{
	return true;
}

#include "Plant_KiwiFruit.h"
void PlantKiwiFruit::DoSpecial(int i_arg)
{
	 PlantKiwiFruit::dealPlantfoodDamage();
}
