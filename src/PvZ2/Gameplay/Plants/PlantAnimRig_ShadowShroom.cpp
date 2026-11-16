//
//  PlantAnimRig_ShadowShroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ShadowShroom.h"

PlantAnimRig_ShadowShroom::PlantAnimRig_ShadowShroom()
{
}

PlantAnimRig_ShadowShroom::~PlantAnimRig_ShadowShroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_ShadowShroom);

void PlantAnimRig_ShadowShroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_ShadowShroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(AnimRigLayerSet, m_boostedLayerSet);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_ShadowShroom);
}
