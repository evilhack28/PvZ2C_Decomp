//
//  Plant_Lotus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Lotus.h"

PlantLotus::PlantLotus()
{
}

PlantLotus::~PlantLotus()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantLotus);

#include "PlantFramework.h"
void PlantLotus::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

bool PlantLotus::CanApplyPlantfood()
{
	return true;
}
