//
//  PlantAnimRig_OrchidMage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_OrchidMage.h"

PlantAnimRig_OrchidMage::PlantAnimRig_OrchidMage()
{
}

PlantAnimRig_OrchidMage::~PlantAnimRig_OrchidMage()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_OrchidMage);

void PlantAnimRig_OrchidMage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_OrchidMage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_OrchidMage);
}
