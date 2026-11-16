//
//  PlantAnimRig_HomingThistle.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_HomingThistle.h"

PlantAnimRig_HomingThistle::PlantAnimRig_HomingThistle()
{
}

PlantAnimRig_HomingThistle::~PlantAnimRig_HomingThistle()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_HomingThistle);

void PlantAnimRig_HomingThistle::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_HomingThistle);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_HomingThistle);
}
