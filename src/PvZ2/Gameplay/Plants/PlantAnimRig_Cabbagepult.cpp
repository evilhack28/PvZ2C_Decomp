//
//  PlantAnimRig_Cabbagepult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Cabbagepult.h"

PlantAnimRig_Cabbagepult::PlantAnimRig_Cabbagepult()
{
}

PlantAnimRig_Cabbagepult::~PlantAnimRig_Cabbagepult()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Cabbagepult);

void PlantAnimRig_Cabbagepult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Cabbagepult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Cabbagepult);
}
