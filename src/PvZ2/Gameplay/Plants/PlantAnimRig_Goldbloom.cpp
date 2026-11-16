//
//  PlantAnimRig_Goldbloom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Goldbloom.h"

PlantAnimRig_Goldbloom::PlantAnimRig_Goldbloom()
{
}

PlantAnimRig_Goldbloom::~PlantAnimRig_Goldbloom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Goldbloom);

void PlantAnimRig_Goldbloom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Goldbloom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Goldbloom);
}
