//
//  PlantAnimRig_Flattenedshroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Flattenedshroom.h"

PlantAnimRig_Flattenedshroom::PlantAnimRig_Flattenedshroom()
{
}

PlantAnimRig_Flattenedshroom::~PlantAnimRig_Flattenedshroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Flattenedshroom);

void PlantAnimRig_Flattenedshroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Flattenedshroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_submerged);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Flattenedshroom);
}
