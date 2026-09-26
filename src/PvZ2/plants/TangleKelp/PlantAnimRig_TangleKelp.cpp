//
//  PlantAnimRig_TangleKelp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_TangleKelp.h"

PlantAnimRig_TangleKelp::PlantAnimRig_TangleKelp()
{
}

PlantAnimRig_TangleKelp::~PlantAnimRig_TangleKelp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_TangleKelp);

void PlantAnimRig_TangleKelp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_TangleKelp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_TangleKelp);
}
