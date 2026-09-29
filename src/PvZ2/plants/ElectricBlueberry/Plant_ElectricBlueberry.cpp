//
//  Plant_ElectricBlueberry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ElectricBlueberry.h"

PlantElectricBlueberry::PlantElectricBlueberry()
{
}

PlantElectricBlueberry::~PlantElectricBlueberry()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantElectricBlueberry);

bool PlantElectricBlueberry::CanApplyPlantfood()
{
	return true;
}

BoardEntityTypeFlag PlantElectricBlueberry::GetTargetEntityTypesForWeapon(PlantWeapon i_arg)
{
	return (BoardEntityTypeFlag)2;
}
