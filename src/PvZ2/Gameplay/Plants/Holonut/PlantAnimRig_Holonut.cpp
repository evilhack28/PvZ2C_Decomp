//
//  PlantAnimRig_Holonut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Holonut.h"

PlantAnimRig_Holonut::PlantAnimRig_Holonut()
{
}

PlantAnimRig_Holonut::~PlantAnimRig_Holonut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Holonut);

void PlantAnimRig_Holonut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Holonut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_downed);
		REFLECTION_CLASSBUILDER_FIELD(AnimRigLayerSet, m_layerSet);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Holonut);
}
