//
//  PlantAnimRig_BoophoneGeisha.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BoophoneGeisha.h"

PlantAnimRig_BoophoneGeisha::PlantAnimRig_BoophoneGeisha()
{
}

PlantAnimRig_BoophoneGeisha::~PlantAnimRig_BoophoneGeisha()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_BoophoneGeisha);

void PlantAnimRig_BoophoneGeisha::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_BoophoneGeisha);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_BoophoneGeisha);
}
