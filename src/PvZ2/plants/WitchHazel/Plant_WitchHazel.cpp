//
//  Plant_WitchHazel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_WitchHazel.h"

PlantWitchHazel::PlantWitchHazel()
{
}

PlantWitchHazel::~PlantWitchHazel()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantWitchHazel);

void PlantWitchHazel::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantWitchHazel);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_magicState);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_magicChargeTime);
	REFLECTION_CLASSBUILDER_END(PlantWitchHazel);
}

bool PlantWitchHazel::CanApplyPlantfood()
{
	return true;
}
