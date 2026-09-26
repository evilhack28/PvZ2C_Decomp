//
//  PlantAnimRig_Sapfling.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Sapfling.h"

PlantAnimRig_Sapfling::PlantAnimRig_Sapfling()
{
}

PlantAnimRig_Sapfling::~PlantAnimRig_Sapfling()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Sapfling);

void PlantAnimRig_Sapfling::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Sapfling);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Sapfling);
}
