//
//  Plant_SmallChestnut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_SmallChestnut.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSmallChestnut);

void PlantSmallChestnut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSmallChestnut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_left);
		REFLECTION_CLASSBUILDER_FIELD(int, m_distance);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_parent);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, m_offset);
	REFLECTION_CLASSBUILDER_END(PlantSmallChestnut);
}

bool PlantSmallChestnut::CanBeShoveled()
{
	return false;
}

CollisionTypeFlags PlantSmallChestnut::GetCollisionFlags(PlantWeapon i_plantWeapon)
{
	return (CollisionTypeFlags)true;
}

bool PlantSmallChestnut::CanBeRangeTargeted()
{
	return false;
}
