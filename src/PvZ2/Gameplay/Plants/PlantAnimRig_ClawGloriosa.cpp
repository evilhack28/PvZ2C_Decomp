//
//  PlantAnimRig_ClawGloriosa.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ClawGloriosa.h"

PlantAnimRig_ClawGloriosa::PlantAnimRig_ClawGloriosa()
{
}

PlantAnimRig_ClawGloriosa::~PlantAnimRig_ClawGloriosa()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_ClawGloriosa);

void PlantAnimRig_ClawGloriosa::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_ClawGloriosa);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_ClawGloriosa);
}
