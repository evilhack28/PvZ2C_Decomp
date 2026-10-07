//
//  Plant_BeanChemist.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BeanChemist.h"

PlantBeanChemist::PlantBeanChemist()
{
}

PlantBeanChemist::~PlantBeanChemist()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBeanChemist);

void PlantBeanChemist::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBeanChemist);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantBeanChemist);
}

bool PlantBeanChemist::CanApplyPlantfood()
{
	return true;
}

BoardEntityTypeFlag PlantBeanChemist::GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon)
{
	return (BoardEntityTypeFlag)2;
}
