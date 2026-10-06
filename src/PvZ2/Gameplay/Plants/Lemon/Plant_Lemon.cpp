//
//  Plant_Lemon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Lemon.h"

PlantLemon::PlantLemon()
{
}

PlantLemon::~PlantLemon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantLemon);

void PlantLemon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantLemon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(LemonPlantFoodCounter, m_LemonPlantFoodCounter);
		REFLECTION_CLASSBUILDER_FIELD(LemonNormalShooter, m_LemonNormalShooter);
		REFLECTION_CLASSBUILDER_FIELD(Lemon_State, m_LemonState);
	REFLECTION_CLASSBUILDER_END(PlantLemon);
}

#include "PlantFramework.h"
void PlantLemon::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

#include "PlantFramework.h"
bool PlantLemon::CanEndPlantfood()
{
	return PlantFramework::CanEndPlantfood();
}

#include "PlantFramework.h"
void PlantLemon::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}
