//
//  Plant_Magicbeans.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Magicbeans.h"

PlantMagicbeans::PlantMagicbeans()
{
	m_killed = 0;
	m_invincible = 0;
	can_destroy = 0;
}

PlantMagicbeans::~PlantMagicbeans()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantMagicbeans);

void PlantMagicbeans::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantMagicbeans);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantMagicbeans);
}

void PlantMagicbeans::onSetDuplicate(bool i_duplicate)
{
}

float PlantMagicbeans::GetShadowScaling()
{
	return 1.0f;
}

bool PlantMagicbeans::CanApplyPlantfood()
{
	return false;
}

bool PlantMagicbeans::TryBlockPushOffBoard(Zombie* i_srcZombie, const int i_direction)
{
	return false;
}
