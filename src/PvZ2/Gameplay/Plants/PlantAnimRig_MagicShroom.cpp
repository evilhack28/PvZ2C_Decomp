//
//  PlantAnimRig_MagicShroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_MagicShroom.h"

PlantAnimRig_MagicShroom::PlantAnimRig_MagicShroom()
{
}

PlantAnimRig_MagicShroom::~PlantAnimRig_MagicShroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_MagicShroom);

void PlantAnimRig_MagicShroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_MagicShroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_MagicShroom);
}
