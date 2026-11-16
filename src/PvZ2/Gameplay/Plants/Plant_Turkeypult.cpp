//
//  Plant_Turkeypult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Turkeypult.h"

PlantTurkeypult::PlantTurkeypult()
{
}

PlantTurkeypult::~PlantTurkeypult()
{
}

PlantTypeTurkeypult::PlantTypeTurkeypult()
{
}

PlantTypeTurkeypult::~PlantTypeTurkeypult()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTurkeypult);

void PlantTurkeypult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTurkeypult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantTurkeypult);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeTurkeypult);

void PlantTypeTurkeypult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantTypeTurkeypult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantType);

	REFLECTION_CLASSBUILDER_END(PlantTypeTurkeypult);
}

bool PlantTurkeypult::CanApplyPlantfood()
{
	return true;
}
