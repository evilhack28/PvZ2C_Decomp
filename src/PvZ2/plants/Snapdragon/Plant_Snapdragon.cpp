//
//  Plant_Snapdragon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Snapdragon.h"

PlantSnapdragon::PlantSnapdragon()
{
}

PlantSnapdragon::~PlantSnapdragon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSnapdragon);

void PlantSnapdragon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSnapdragon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(float, m_plantfoodDamageApplied);
		REFLECTION_CLASSBUILDER_FIELD(Rect, m_plantfoodAttackRange);
	REFLECTION_CLASSBUILDER_END(PlantSnapdragon);
}

bool PlantSnapdragon::CanApplyPlantfood()
{
	return true;
}
