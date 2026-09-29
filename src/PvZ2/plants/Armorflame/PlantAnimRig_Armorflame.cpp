//
//  PlantAnimRig_Armorflame.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Armorflame.h"

PlantAnimRig_Armorflame::PlantAnimRig_Armorflame()
{
}

PlantAnimRig_Armorflame::~PlantAnimRig_Armorflame()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Armorflame);

void PlantAnimRig_Armorflame::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Armorflame);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Armorflame);
}
