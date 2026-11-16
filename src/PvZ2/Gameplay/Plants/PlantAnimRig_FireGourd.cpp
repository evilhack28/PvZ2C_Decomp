//
//  PlantAnimRig_FireGourd.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_FireGourd.h"

PlantAnimRig_FireGourd::PlantAnimRig_FireGourd()
{
}

PlantAnimRig_FireGourd::~PlantAnimRig_FireGourd()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_FireGourd);

void PlantAnimRig_FireGourd::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_FireGourd);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_FireGourd);
}

#include "PlantAnimRig.h"
void PlantAnimRig_FireGourd::onPopAnimInitialized()
{
	 PlantAnimRig::onPopAnimInitialized();
}
