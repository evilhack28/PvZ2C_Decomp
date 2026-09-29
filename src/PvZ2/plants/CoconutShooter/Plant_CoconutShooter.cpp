//
//  Plant_CoconutShooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_CoconutShooter.h"

PlantCoconutShooter::PlantCoconutShooter()
{
}

PlantCoconutShooter::~PlantCoconutShooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCoconutShooter);

void PlantCoconutShooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCoconutShooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantCoconutShooter);
}

void PlantCoconutShooter::UpdateActions()
{
}

#include "PlantFramework.h"
void PlantCoconutShooter::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

#include "PlantFramework.h"
void PlantCoconutShooter::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

bool PlantCoconutShooter::CanApplyPlantfood()
{
	return true;
}
