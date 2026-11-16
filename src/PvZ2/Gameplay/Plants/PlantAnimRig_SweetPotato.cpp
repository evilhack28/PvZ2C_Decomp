//
//  PlantAnimRig_SweetPotato.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_SweetPotato.h"

PlantAnimRig_SweetPotato::PlantAnimRig_SweetPotato()
{
}

PlantAnimRig_SweetPotato::~PlantAnimRig_SweetPotato()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_SweetPotato);

void PlantAnimRig_SweetPotato::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_SweetPotato);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_SweetPotato);
}

int PlantAnimRig_SweetPotato::CalcDamageStateCount()
{
	return 2;
}
