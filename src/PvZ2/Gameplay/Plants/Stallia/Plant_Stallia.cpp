//
//  Plant_Stallia.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Stallia.h"

PlantStallia::~PlantStallia()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantStallia);

void PlantStallia::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantStallia);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_exploded);
	REFLECTION_CLASSBUILDER_END(PlantStallia);
}

CollisionTypeFlags PlantStallia::GetCollisionFlags(PlantWeapon i_plantWeapon)
{
	return (CollisionTypeFlags)7;
}

bool PlantStallia::TryBlockZombossRush(Zombie* i_zomboss)
{
	return false;
}

bool PlantStallia::HasShadow()
{
	return !m_exploded;
}

