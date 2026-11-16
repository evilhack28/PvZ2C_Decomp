//
//  PlantAnimRig_SnowPea.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_SnowPea.h"

PlantAnimRig_SnowPea::PlantAnimRig_SnowPea()
{
}

PlantAnimRig_SnowPea::~PlantAnimRig_SnowPea()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_SnowPea);

void PlantAnimRig_SnowPea::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_SnowPea);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_SnowPea);
}

#include "PlantAnimRig.h"
void PlantAnimRig_SnowPea::onPopAnimInitialized()
{
	 PlantAnimRig::onPopAnimInitialized();
}
