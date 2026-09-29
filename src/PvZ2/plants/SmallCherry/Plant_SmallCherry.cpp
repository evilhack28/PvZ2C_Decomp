//
//  Plant_SmallCherry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_SmallCherry.h"

PlantSmallCherry::PlantSmallCherry()
{
}

PlantSmallCherry::~PlantSmallCherry()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSmallCherry);

bool PlantSmallCherry::OnAnimCommand(const std::string & i_arg0, const std::string & i_arg1)
{
	return true;
}

bool PlantSmallCherry::CanApplyPlantfood()
{
	return false;
}

bool PlantSmallCherry::HasShadow()
{
	return false;
}
