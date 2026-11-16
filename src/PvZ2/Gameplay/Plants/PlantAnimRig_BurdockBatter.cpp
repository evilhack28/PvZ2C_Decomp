//
//  PlantAnimRig_BurdockBatter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BurdockBatter.h"

PlantAnimRig_BurdockBatter::PlantAnimRig_BurdockBatter()
{
}

PlantAnimRig_BurdockBatter::~PlantAnimRig_BurdockBatter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_BurdockBatter);

void PlantAnimRig_BurdockBatter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_BurdockBatter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_BurdockBatter);
}
