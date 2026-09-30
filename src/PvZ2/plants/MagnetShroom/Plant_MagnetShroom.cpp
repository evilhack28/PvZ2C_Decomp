//
//  Plant_MagnetShroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_MagnetShroom.h"

PlantMagnetShroom::PlantMagnetShroom()
{
}

PlantMagnetShroom::~PlantMagnetShroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantMagnetShroom);

bool PlantMagnetShroom::CanApplyPlantfood()
{
	return true;
}

#include "Plant_MagnetShroom.h"
void PlantMagnetShroom::onKilled(bool i_arg)
{
	 PlantMagnetShroom::DropAllPulledEntities();
}

bool PlantMagnetShroom::canPullZombie(Zombie* i_arg) const
{
	return false;
}
