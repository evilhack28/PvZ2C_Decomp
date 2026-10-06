//
//  PlantAnimRig_WasabiWhip.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_WasabiWhip.h"

PlantAnimRig_WasabiWhip::PlantAnimRig_WasabiWhip()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_WasabiWhip);

void PlantAnimRig_WasabiWhip::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_WasabiWhip);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantIdleAwareAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_WasabiWhip);
}
