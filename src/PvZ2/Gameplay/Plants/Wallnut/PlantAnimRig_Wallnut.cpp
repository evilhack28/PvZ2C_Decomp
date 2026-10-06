//
//  PlantAnimRig_Wallnut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Wallnut.h"

PlantAnimRig_Wallnut::PlantAnimRig_Wallnut()
{
}

PlantAnimRig_Wallnut::~PlantAnimRig_Wallnut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Wallnut);

void PlantAnimRig_Wallnut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Wallnut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig_Shielded);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Wallnut);
}
