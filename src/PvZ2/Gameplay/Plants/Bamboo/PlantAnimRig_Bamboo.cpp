//
//  PlantAnimRig_Bamboo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Bamboo.h"

bool PlantAnimRig_Bamboo::PlayPlantFoodEnd()
{
	return true;
}

PlantAnimRig_Bamboo::PlantAnimRig_Bamboo()
{
}

PlantAnimRig_Bamboo::~PlantAnimRig_Bamboo()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Bamboo);

void PlantAnimRig_Bamboo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Bamboo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int32, m_lostHorns);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Bamboo);
}
