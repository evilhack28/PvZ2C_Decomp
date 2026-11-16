//
//  PlantAnimRig_Spikerock.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Spikerock.h"

bool PlantAnimRig_Spikerock::PlayPlantFoodEnd()
{
	return true;
}

PlantAnimRig_Spikerock::PlantAnimRig_Spikerock()
{
}

PlantAnimRig_Spikerock::~PlantAnimRig_Spikerock()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Spikerock);

void PlantAnimRig_Spikerock::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Spikerock);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int32, m_lostHorns);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Spikerock);
}
