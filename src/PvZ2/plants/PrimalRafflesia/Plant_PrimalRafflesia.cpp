//
//  Plant_PrimalRafflesia.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PrimalRafflesia.h"

PlantPrimalRafflesia::PlantPrimalRafflesia()
{
}

PlantPrimalRafflesia::~PlantPrimalRafflesia()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPrimalRafflesia);

void PlantPrimalRafflesia::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPrimalRafflesia);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, m_entitiesHitDuringPlantfood);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_nextPlantFoodTarget);
	REFLECTION_CLASSBUILDER_END(PlantPrimalRafflesia);
}

bool PlantPrimalRafflesia::CanApplyPlantfood()
{
	return true;
}

void PlantPrimalRafflesia::DoSpecial(int i_arg)
{
}
