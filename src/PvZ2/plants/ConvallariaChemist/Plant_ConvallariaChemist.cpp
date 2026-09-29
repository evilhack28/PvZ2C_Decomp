//
//  Plant_ConvallariaChemist.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ConvallariaChemist.h"

PlantConvallariaChemist::PlantConvallariaChemist()
{
}

PlantConvallariaChemist::~PlantConvallariaChemist()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantConvallariaChemist);

void PlantConvallariaChemist::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantConvallariaChemist);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, m_entitiesHitDuringPlantfood);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_nextPlantFoodTarget);
	REFLECTION_CLASSBUILDER_END(PlantConvallariaChemist);
}

#include "PlantFramework.h"
void PlantConvallariaChemist::Initialize()
{
	 PlantFramework::Initialize();
}

bool PlantConvallariaChemist::CanApplyPlantfood()
{
	return true;
}
