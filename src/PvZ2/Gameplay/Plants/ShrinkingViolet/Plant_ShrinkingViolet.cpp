//
//  Plant_ShrinkingViolet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ShrinkingViolet.h"

PlantShrinkingViolet::PlantShrinkingViolet()
{
	m_exploded = 0;
}

PlantShrinkingViolet::~PlantShrinkingViolet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantShrinkingViolet);

void PlantShrinkingViolet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantShrinkingViolet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_exploded);
	REFLECTION_CLASSBUILDER_END(PlantShrinkingViolet);
}

CollisionTypeFlags PlantShrinkingViolet::GetCollisionFlags(PlantWeapon i_arg)
{
	return (CollisionTypeFlags)7;
}

bool PlantShrinkingViolet::TryBlockZombossRush(Zombie* i_arg)
{
	return false;
}

bool PlantShrinkingViolet::HasShadow()
{
	return !m_exploded;
}

