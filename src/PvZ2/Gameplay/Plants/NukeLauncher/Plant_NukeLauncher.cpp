//
//  Plant_NukeLauncher.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_NukeLauncher.h"

PlantNukeLauncher::PlantNukeLauncher()
{
}

PlantNukeLauncher::~PlantNukeLauncher()
{
}

PlantTypeNukeLauncher::PlantTypeNukeLauncher()
{
}

PlantTypeNukeLauncher::~PlantTypeNukeLauncher()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantNukeLauncher);

void PlantNukeLauncher::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantNukeLauncher);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantNukeLauncher);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeNukeLauncher);

#include "PlantFramework.h"
void PlantNukeLauncher::Initialize()
{
	 PlantFramework::Initialize();
}

void PlantNukeLauncher::UpdateActions()
{
}

#include "PlantFramework.h"
void PlantNukeLauncher::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

bool PlantNukeLauncher::CanApplyPlantfood()
{
	return true;
}

void PlantNukeLauncher::registerForEvents()
{
}
