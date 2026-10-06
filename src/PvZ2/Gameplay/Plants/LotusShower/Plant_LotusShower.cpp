//
//  Plant_LotusShower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_LotusShower.h"

PlantLotusShower::PlantLotusShower()
{
}

PlantLotusShower::~PlantLotusShower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantLotusShower);

void PlantLotusShower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantLotusShower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantLotusShower);
}

#include "PlantFramework.h"
void PlantLotusShower::Initialize()
{
	 PlantFramework::Initialize();
}

#include "PlantFramework.h"
void PlantLotusShower::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

#include "PlantFramework.h"
bool PlantLotusShower::CanEndPlantfood()
{
	return PlantFramework::CanEndPlantfood();
}

bool PlantLotusShower::CanApplyPlantfood()
{
	return true;
}
