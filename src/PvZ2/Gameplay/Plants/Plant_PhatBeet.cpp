//
//  Plant_PhatBeet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PhatBeet.h"

PlantPhatBeet::PlantPhatBeet()
{
}

PlantPhatBeet::~PlantPhatBeet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPhatBeet);

void PlantPhatBeet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPhatBeet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_attacksUntilPowerful);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isLvl5Attack);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<PlantPhatBeetDotSystem>, m_dotSystem);
	REFLECTION_CLASSBUILDER_END(PlantPhatBeet);
}

bool PlantPhatBeet::CanApplyPlantfood()
{
	return true;
}
