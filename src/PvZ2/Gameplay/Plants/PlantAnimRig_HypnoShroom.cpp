//
//  PlantAnimRig_HypnoShroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HypnoShroom.h"

PlantAnimRig_HypnoShroom::PlantAnimRig_HypnoShroom()
{
}

PlantAnimRig_HypnoShroom::~PlantAnimRig_HypnoShroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_HypnoShroom);

void PlantAnimRig_HypnoShroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_HypnoShroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_HypnoShroom);
}
