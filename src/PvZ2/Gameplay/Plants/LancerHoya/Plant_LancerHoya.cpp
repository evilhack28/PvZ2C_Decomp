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

Projectile* PlantLancerHoya::normalFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon)
{
	return NULL;
}

bool PlantLancerHoya::CanApplyPlantfood()
{
	return true;
}

Projectile* PlantLancerHoya::Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon)
{
	return NULL;
}

BoardEntityTypeFlag PlantLancerHoya::GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon)
{
	return ENTITYTYPE_ZOMBIE | ENTITYTYPE_GRIDITEM;
}

