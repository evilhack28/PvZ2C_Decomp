//
//  PlantAnimRig_Fishhookgrass.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Fishhookgrass.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Fishhookgrass);

void PlantAnimRig_Fishhookgrass::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Fishhookgrass);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Fishhookgrass);
}

bool PlantAnimRig_Fishhookgrass::PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_arg)
{
	return true;
}

bool PlantAnimRig_Fishhookgrass::PlayPlantFoodEnd()
{
	return true;
}

void PlantAnimRig_Fishhookgrass::onChewingContinued(const std::string& i_arg)
{
}
