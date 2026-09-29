//
//  PlantAnimRig_Icelotus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Icelotus.h"

PlantAnimRig_Icelotus::PlantAnimRig_Icelotus()
{
	_shouldReload = 1;
}

PlantAnimRig_Icelotus::~PlantAnimRig_Icelotus()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Icelotus);

void PlantAnimRig_Icelotus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Icelotus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(AnimRigLayerSet, _layer);
		REFLECTION_CLASSBUILDER_FIELD(bool, _shouldReload);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Icelotus);
}
