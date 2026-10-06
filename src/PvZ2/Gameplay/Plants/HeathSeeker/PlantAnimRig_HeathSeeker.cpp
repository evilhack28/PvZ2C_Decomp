//
//  PlantAnimRig_HeathSeeker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HeathSeeker.h"

PlantAnimRig_HeathSeeker::PlantAnimRig_HeathSeeker()
{
}

PlantAnimRig_HeathSeeker::~PlantAnimRig_HeathSeeker()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_HeathSeeker);

void PlantAnimRig_HeathSeeker::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_HeathSeeker);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_HeathSeeker);
}
