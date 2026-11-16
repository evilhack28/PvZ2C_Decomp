//
//  PlantAnimRig_BeanChemist.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BeanChemist.h"

PlantAnimRig_BeanChemist::PlantAnimRig_BeanChemist()
{
}

PlantAnimRig_BeanChemist::~PlantAnimRig_BeanChemist()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_BeanChemist);

void PlantAnimRig_BeanChemist::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_BeanChemist);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_BeanChemist);
}
