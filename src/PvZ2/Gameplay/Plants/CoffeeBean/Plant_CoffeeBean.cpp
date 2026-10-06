//
//  Plant_CoffeeBean.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_CoffeeBean.h"

PlantCoffeeBean::PlantCoffeeBean()
{
}

PlantCoffeeBean::~PlantCoffeeBean()
{
}

PlantTypeCoffeeBean::PlantTypeCoffeeBean()
{
}

PlantTypeCoffeeBean::~PlantTypeCoffeeBean()
{
}

void PlantCoffeeBean::UpdateActions()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCoffeeBean);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeCoffeeBean);

CollisionTypeFlags PlantCoffeeBean::GetCollisionFlags(PlantWeapon i_arg)
{
	return (CollisionTypeFlags)240;
}

void PlantTypeCoffeeBean::GatherPlantingRestrictions(Board* i_arg0, const Sexy::Point& i_arg1, std::vector<PlantingReason>* i_arg2) const
{
}
