//
//  PlantAnimRig_Shielded.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Shielded.h"
#include "ReflectionBuilder.h"

PlantAnimRig_Shielded::PlantAnimRig_Shielded()
{
}

PlantAnimRig_Shielded::~PlantAnimRig_Shielded()
{
}

RT_CLASS_IMPLEMENT_ABSTRACT(PlantAnimRig_Shielded);

void PlantAnimRig_Shielded::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Shielded);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Shielded);
}
