//
//  PlantAnimRig_Magnetshroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_MagnetShroom.h"

PlantAnimRig_Magnetshroom::PlantAnimRig_Magnetshroom()
{
}

PlantAnimRig_Magnetshroom::~PlantAnimRig_Magnetshroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Magnetshroom);

void PlantAnimRig_Magnetshroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Magnetshroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Magnetshroom);
}
