//
//  PlantAnimRig_Chomper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Chomper.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Chomper);

void PlantAnimRig_Chomper::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Chomper);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(int, m_currentAnimationHandle);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Chomper);
}

bool PlantAnimRig_Chomper::PlayPlantFoodEnd()
{
	return true;
}
