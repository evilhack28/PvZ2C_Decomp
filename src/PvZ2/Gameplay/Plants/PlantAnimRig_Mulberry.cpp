//
//  PlantAnimRig_Mulberry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Mulberry.h"

PlantAnimRig_Mulberry::PlantAnimRig_Mulberry()
{
}

PlantAnimRig_Mulberry::~PlantAnimRig_Mulberry()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Mulberry);

void PlantAnimRig_Mulberry::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Mulberry);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int32, m_attackType);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Mulberry);
}

std::string PlantAnimRig_Mulberry::getPlantFoodMainAnimName()
{
	return m_bAvatar ? "plantfood2" : "plantfood";
}

