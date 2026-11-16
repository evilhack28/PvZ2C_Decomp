//
//  Plant_OrchidMage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_OrchidMage.h"

PlantOrchidMage::PlantOrchidMage()
{
}

PlantOrchidMage::~PlantOrchidMage()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantOrchidMage);

void PlantOrchidMage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantOrchidMage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(Rect, passiveRange);
		REFLECTION_CLASSBUILDER_FIELD(int, passiveTimes);
	REFLECTION_CLASSBUILDER_END(PlantOrchidMage);
}

bool PlantOrchidMage::CanApplyPlantfood()
{
	return true;
}

void PlantOrchidMage::onDestroy()
{
}
