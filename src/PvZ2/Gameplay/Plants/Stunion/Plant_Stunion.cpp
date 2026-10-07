//
//  Plant_Stunion.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Stunion.h"

PlantStunion::PlantStunion()
{
	m_hasShadow = 1;
}

PlantStunion::~PlantStunion()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantStunion);

void PlantStunion::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantStunion);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasShadow);
	REFLECTION_CLASSBUILDER_END(PlantStunion);
}

CollisionTypeFlags PlantStunion::GetCollisionFlags(PlantWeapon i_plantWeapon)
{
	return (CollisionTypeFlags)7;
}
