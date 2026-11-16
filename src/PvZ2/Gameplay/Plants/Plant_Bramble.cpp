//
//  Plant_Bramble.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Bramble.h"

PlantBramble::PlantBramble()
{
}

PlantBramble::~PlantBramble()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBramble);

void PlantBramble::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBramble);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantBramble);
}

#include "PlantFramework.h"
void PlantBramble::Initialize()
{
	 PlantFramework::Initialize();
}

bool PlantBramble::CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon)
{
	return false;
}

bool PlantBramble::CanApplyPlantfood()
{
	return false;
}

CollisionTypeFlags PlantBramble::GetCollisionFlags(PlantWeapon i_plantWeapon)
{
	return (CollisionTypeFlags)false;
}
