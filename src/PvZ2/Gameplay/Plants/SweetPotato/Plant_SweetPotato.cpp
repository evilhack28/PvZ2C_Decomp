//
//  Plant_SweetPotato.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_SweetPotato.h"

PlantSweetPotato::PlantSweetPotato()
{
}

PlantSweetPotato::~PlantSweetPotato()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSweetPotato);

void PlantSweetPotato::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSweetPotato);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantSweetPotato);
}

bool PlantSweetPotato::CanApplyPlantfood()
{
	return true;
}
