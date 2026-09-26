//
//  PlantAnimRig_Sunshroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Sunshroom.h"

PlantAnimRig_Sunshroom::~PlantAnimRig_Sunshroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Sunshroom);

void PlantAnimRig_Sunshroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Sunshroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig_Sunflower);

	REFLECTION_CLASSBUILDER_FIELD(uint8, m_currentGrowthStage);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Sunshroom);
}
