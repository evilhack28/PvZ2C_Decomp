//
//  PlantAnimRig_WhiteMelon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_WhiteMelon.h"

PlantAnimRig_WhiteMelon::PlantAnimRig_WhiteMelon()
{
}

PlantAnimRig_WhiteMelon::~PlantAnimRig_WhiteMelon()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_WhiteMelon);

void PlantAnimRig_WhiteMelon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_WhiteMelon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_WhiteMelon);
}
