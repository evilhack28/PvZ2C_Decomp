//
//  PlantAnimRig_Anthurium.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Anthurium.h"

PlantAnimRig_Anthurium::PlantAnimRig_Anthurium()
{
}

PlantAnimRig_Anthurium::~PlantAnimRig_Anthurium()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Anthurium);

void PlantAnimRig_Anthurium::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Anthurium);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Anthurium);
}
