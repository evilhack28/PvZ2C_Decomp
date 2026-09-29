//
//  Plant_Deodarcedar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Deodarcedar.h"

PlantDeodarcedar::PlantDeodarcedar()
{
	m_stage = 1;
}

PlantDeodarcedar::~PlantDeodarcedar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantDeodarcedar);

void PlantDeodarcedar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantDeodarcedar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantDeodarcedar);
}

bool PlantDeodarcedar::CanApplyPlantfood()
{
	return true;
}
