//
//  Plant_Agave.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Agave.h"

PlantAgave::PlantAgave()
{
}

PlantAgave::~PlantAgave()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAgave);

void PlantAgave::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAgave);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(float, m_chargeDamageRate);
	REFLECTION_CLASSBUILDER_END(PlantAgave);
}

#include "PlantFramework.h"
void PlantAgave::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

void PlantAgave::UpdatePlantfood()
{
}

bool PlantAgave::CanApplyPlantfood()
{
	return true;
}
