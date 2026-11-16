//
//  PlantAnimRig_Reincarnation.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Reincarnation.h"

PlantAnimRig_Reincarnation::PlantAnimRig_Reincarnation()
{
}

PlantAnimRig_Reincarnation::~PlantAnimRig_Reincarnation()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Reincarnation);

void PlantAnimRig_Reincarnation::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Reincarnation);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(int32_t, m_growthLevel);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Reincarnation);
}

bool PlantAnimRig_Reincarnation::PlayPlantFoodEnd()
{
	return true;
}

std::string PlantAnimRig_Reincarnation::getPlantFoodOnAnimName()
{
	return m_bAvatar ? "plantfood2" : "plantfood";
}


std::string PlantAnimRig_Reincarnation::getPlantFoodMainAnimName()
{
	return m_bAvatar ? "plantfood2" : "plantfood";
}

