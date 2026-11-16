//
//  Plant_Chilibean.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Chilibean.h"

PlantChilibean::PlantChilibean()
{
}

PlantChilibean::~PlantChilibean()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantChilibean);

#include "PlantFramework.h"
void PlantChilibean::Initialize()
{
	 PlantFramework::Initialize();
}

void PlantChilibean::onSetDuplicate(bool i_duplicate)
{
}

bool PlantChilibean::CanApplyPlantfood()
{
	return true;
}

CollisionTypeFlags PlantChilibean::GetCollisionFlags(PlantWeapon i_plantWeapon)
{
	return (CollisionTypeFlags)true;
}
