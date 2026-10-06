//
//  Plant_WasabiWhip.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_WasabiWhip.h"

PlantWasabiWhip::PlantWasabiWhip()
{
}

PlantWasabiWhip::~PlantWasabiWhip()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantWasabiWhip);

void PlantWasabiWhip::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantWasabiWhip);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_attackDirection);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentWarmingRadius>, m_warmingRadius);
	REFLECTION_CLASSBUILDER_END(PlantWasabiWhip);
}

bool PlantWasabiWhip::CanApplyPlantfood()
{
	return true;
}
