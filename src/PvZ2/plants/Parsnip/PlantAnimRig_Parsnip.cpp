//
//  PlantAnimRig_Parsnip.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Parsnip.h"

PlantAnimRig_Parsnip::PlantAnimRig_Parsnip()
{
}

PlantAnimRig_Parsnip::~PlantAnimRig_Parsnip()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Parsnip);

void PlantAnimRig_Parsnip::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Parsnip);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Parsnip);
}
