//
//  Plant_LancerHoya.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_LancerHoya.h"

PlantLancerHoya::PlantLancerHoya()
{
}

PlantLancerHoya::~PlantLancerHoya()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantLancerHoya);

void PlantLancerHoya::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantLancerHoya);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(Rect, m_collisionRect);
	REFLECTION_CLASSBUILDER_END(PlantLancerHoya);
}

Projectile* PlantLancerHoya::normalFire(ZombiePtr i_arg0, int i_arg1, PlantWeapon i_arg2)
{
	return NULL;
}

bool PlantLancerHoya::CanApplyPlantfood()
{
	return true;
}

Projectile* PlantLancerHoya::Fire(ZombiePtr i_arg0, int i_arg1, PlantWeapon i_arg2)
{
	return NULL;
}

BoardEntityTypeFlag PlantLancerHoya::GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon)
{
	return ENTITYTYPE_ZOMBIE | ENTITYTYPE_GRIDITEM;
}

