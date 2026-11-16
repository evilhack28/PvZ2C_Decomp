//
//  PlantAnimRig_Lotusshooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Lotusshooter.h"

PlantAnimRig_Lotusshooter::PlantAnimRig_Lotusshooter()
{
}

PlantAnimRig_Lotusshooter::~PlantAnimRig_Lotusshooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Lotusshooter);

void PlantAnimRig_Lotusshooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Lotusshooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Lotusshooter);
}
