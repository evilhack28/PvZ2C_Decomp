//
//  Plant_Dandelion.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Dandelion.h"

PlantDandelion::PlantDandelion()
{
}

PlantDandelion::~PlantDandelion()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantDandelion);

void PlantDandelion::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantDandelion);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantDandelion);
}

#include "PlantFramework.h"
void PlantDandelion::Initialize()
{
	 PlantFramework::Initialize();
}

#include "PlantFramework.h"
void PlantDandelion::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

#include "PlantFramework.h"
void PlantDandelion::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

void PlantDandelion::UpdatePlantfood()
{
}

bool PlantDandelion::CanApplyPlantfood()
{
	return true;
}
