//
//  PlantAnimRig_PlantPassion.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PassionFlower.h"

PlantAnimRig_PlantPassion::PlantAnimRig_PlantPassion()
{
}

PlantAnimRig_PlantPassion::~PlantAnimRig_PlantPassion()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_PlantPassion);

std::string PlantAnimRig_PlantPassion::getPlantFoodMainAnimName()
{
	return m_bAvatar ? "plantfood2" : "plantfood";
}

