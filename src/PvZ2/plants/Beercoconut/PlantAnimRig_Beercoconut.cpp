//
//  PlantAnimRig_Beercoconut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Beercoconut.h"

PlantAnimRig_Beercoconut::~PlantAnimRig_Beercoconut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Beercoconut);

void PlantAnimRig_Beercoconut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Beercoconut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Beercoconut);
}

PlantAnimRig_Beercoconut::PlantAnimRig_Beercoconut()
{
	m_isLevel5 = 0;
}

std::string PlantAnimRig_Beercoconut::getPlantFoodMainAnimName()
{
	return m_bAvatar ? "plantfood2" : "plantfood";
}

