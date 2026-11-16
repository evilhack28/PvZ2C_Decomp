//
//  PlantAnimRig_GroundCherry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_GroundCherry.h"

PlantAnimRig_GroundCherry::~PlantAnimRig_GroundCherry()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_GroundCherry);

void PlantAnimRig_GroundCherry::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_GroundCherry);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_pPlantGroundCherry);
	REFLECTION_CLASSBUILDER_FIELD(std::string, m_idleLabel);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_GroundCherry);
}
