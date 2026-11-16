//
//  PlantAnimRig_Pamegranate.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Pamegranate.h"

PlantAnimRig_Pamegranate::PlantAnimRig_Pamegranate()
{
}

PlantAnimRig_Pamegranate::~PlantAnimRig_Pamegranate()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Pamegranate);

void PlantAnimRig_Pamegranate::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Pamegranate);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Pamegranate);
}
