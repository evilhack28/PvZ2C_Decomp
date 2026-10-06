//
//  PlantAnimRig_EggplantNinja.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_EggplantNinja.h"

PlantAnimRig_EggplantNinja::PlantAnimRig_EggplantNinja()
{
}

PlantAnimRig_EggplantNinja::~PlantAnimRig_EggplantNinja()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_EggplantNinja);

void PlantAnimRig_EggplantNinja::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_EggplantNinja);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_EggplantNinja);
}
