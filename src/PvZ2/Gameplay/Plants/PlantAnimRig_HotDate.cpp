//
//  PlantAnimRig_HotDate.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HotDate.h"

PlantAnimRig_HotDate::PlantAnimRig_HotDate()
{
}

PlantAnimRig_HotDate::~PlantAnimRig_HotDate()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_HotDate);

void PlantAnimRig_HotDate::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_HotDate);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig_SweetPotato);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_HotDate);
}

int PlantAnimRig_HotDate::CalcDamageStateCount()
{
	return 3;
}
