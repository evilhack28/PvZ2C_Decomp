//
//  Plant_NarcissusShooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_NarcissusShooter.h"

PlantNarcissusShooter::PlantNarcissusShooter()
{
}

PlantNarcissusShooter::~PlantNarcissusShooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantNarcissusShooter);

void PlantNarcissusShooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantNarcissusShooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, m_plantfood_projectile_num);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_superEndTime);
	REFLECTION_CLASSBUILDER_END(PlantNarcissusShooter);
}

#include "PlantFramework.h"
void PlantNarcissusShooter::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}
