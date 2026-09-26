//
//  PlantAnimRig_HatMushroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HatMushroom.h"

PlantAnimRig_HatMushroom::PlantAnimRig_HatMushroom()
{
}

PlantAnimRig_HatMushroom::~PlantAnimRig_HatMushroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_HatMushroom);

void PlantAnimRig_HatMushroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_HatMushroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_HatMushroom);
}
