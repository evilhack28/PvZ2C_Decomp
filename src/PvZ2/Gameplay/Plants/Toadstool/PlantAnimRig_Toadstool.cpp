//
//  PlantAnimRig_Toadstool.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Toadstool.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Toadstool);

void PlantAnimRig_Toadstool::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Toadstool);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Toadstool);
}

bool PlantAnimRig_Toadstool::PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped)
{
	return true;
}

bool PlantAnimRig_Toadstool::PlayPlantFoodEnd()
{
	return true;
}
