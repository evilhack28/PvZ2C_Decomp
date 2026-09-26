//
//  PlantAnimRig_StickybombRice.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_StickybombRice.h"

PlantAnimRig_StickybombRice::PlantAnimRig_StickybombRice()
{
}

PlantAnimRig_StickybombRice::~PlantAnimRig_StickybombRice()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_StickybombRice);

void PlantAnimRig_StickybombRice::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_StickybombRice);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_StickybombRice);
}
