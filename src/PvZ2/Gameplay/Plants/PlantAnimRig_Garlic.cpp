//
//  PlantAnimRig_Garlic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Garlic.h"

PlantAnimRig_Garlic::PlantAnimRig_Garlic()
{
}

PlantAnimRig_Garlic::~PlantAnimRig_Garlic()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Garlic);

void PlantAnimRig_Garlic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Garlic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Garlic);
}

int PlantAnimRig_Garlic::CalcDamageStateCount()
{
	return 2;
}
