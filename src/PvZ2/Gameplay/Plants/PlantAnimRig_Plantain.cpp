//
//  PlantAnimRig_Plantain.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Plantain.h"

PlantAnimRig_Plantain::PlantAnimRig_Plantain()
{
	m_bIsSuperSkill = 0;
}

PlantAnimRig_Plantain::~PlantAnimRig_Plantain()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Plantain);

void PlantAnimRig_Plantain::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Plantain);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastUsedIdleAnim);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Plantain);
}

#include "PlantAnimRig_Plantain.h"
bool PlantAnimRig_Plantain::PlayPlantFoodEnd()
{
	return PlantAnimRig_Plantain::PlayRecoverIn();
}
