//
//  Plant_Impatiensshooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Impatiensshooter.h"

PlantImpatiensshooter::PlantImpatiensshooter()
{
}

PlantImpatiensshooter::~PlantImpatiensshooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantImpatiensshooter);

void PlantImpatiensshooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantImpatiensshooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int32_t, m_growthLevel);
	REFLECTION_CLASSBUILDER_END(PlantImpatiensshooter);
}

bool PlantImpatiensshooter::CanApplyPlantfood()
{
	return true;
}
