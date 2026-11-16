//
//  Plant_HoyaCordata.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HoyaCordata.h"

PlantHoyaCordataProps::~PlantHoyaCordataProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHoyaCordata);

void PlantHoyaCordata::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHoyaCordata);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantHoyaCordata);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantHoyaCordataProps);

void PlantHoyaCordataProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantHoyaCordataProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantPropertySheet);

	REFLECTION_CLASSBUILDER_END(PlantHoyaCordataProps);
}

bool PlantHoyaCordata::CanApplyPlantfood()
{
	return true;
}
