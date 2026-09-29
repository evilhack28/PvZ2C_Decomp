//
//  Plant_Oakshooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Oakshooter.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantOakshooter);

void PlantOakshooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantOakshooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(OakshooterPlantfood, m_plantfood);
		REFLECTION_CLASSBUILDER_FIELD(Point, m_manualShootLocation);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bCanShoot);
	REFLECTION_CLASSBUILDER_END(PlantOakshooter);
}

#include "PlantFramework.h"
void PlantOakshooter::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

bool PlantOakshooter::CanApplyPlantfood()
{
	return true;
}
