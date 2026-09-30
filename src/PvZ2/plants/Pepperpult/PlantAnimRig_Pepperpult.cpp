//
//  PlantAnimRig_Pepperpult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Pepperpult.h"

PlantAnimRig_Pepperpult::PlantAnimRig_Pepperpult()
{
}

PlantAnimRig_Pepperpult::~PlantAnimRig_Pepperpult()
{
}

#include "PlantAnimRig.h"
void PlantAnimRig_Pepperpult::onPopAnimInitialized()
{
	 PlantAnimRig::onPopAnimInitialized();
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Pepperpult);

std::string PlantAnimRig_Pepperpult::getPlantFoodMainAnimName()
{
	return m_bAvatar ? "plantfood2" : "plantfood";
}

