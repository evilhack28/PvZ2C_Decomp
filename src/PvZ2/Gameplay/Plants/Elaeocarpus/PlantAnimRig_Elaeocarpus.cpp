//
//  PlantAnimRig_Elaeocarpus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Elaeocarpus.h"

PlantAnimRig_Elaeocarpus::~PlantAnimRig_Elaeocarpus()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Elaeocarpus);

void PlantAnimRig_Elaeocarpus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Elaeocarpus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Elaeocarpus);
}

PlantAnimRig_Elaeocarpus::PlantAnimRig_Elaeocarpus()
{
	m_attackMode = 1;
}
