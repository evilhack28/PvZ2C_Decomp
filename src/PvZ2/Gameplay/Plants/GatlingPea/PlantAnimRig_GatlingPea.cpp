//
//  PlantAnimRig_GatlingPea.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_GatlingPea.h"

PlantAnimRig_GatlingPea::PlantAnimRig_GatlingPea()
{
}

PlantAnimRig_GatlingPea::~PlantAnimRig_GatlingPea()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_GatlingPea);

void PlantAnimRig_GatlingPea::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_GatlingPea);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_GatlingPea);
}
