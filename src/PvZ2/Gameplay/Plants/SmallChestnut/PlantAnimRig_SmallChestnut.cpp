//
//  PlantAnimRig_SmallChestnut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_SmallChestnut.h"

PlantAnimRig_SmallChestnut::PlantAnimRig_SmallChestnut()
{
}

PlantAnimRig_SmallChestnut::~PlantAnimRig_SmallChestnut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_SmallChestnut);

void PlantAnimRig_SmallChestnut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_SmallChestnut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_SmallChestnut);
}
