//
//  PlantAnimRig_ZoybeanPod.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ZoybeanPod.h"

PlantAnimRig_ZoybeanPod::PlantAnimRig_ZoybeanPod()
{
}

PlantAnimRig_ZoybeanPod::~PlantAnimRig_ZoybeanPod()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_ZoybeanPod);

void PlantAnimRig_ZoybeanPod::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_ZoybeanPod);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(std::string, m_prevAnim);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Plant>, m_plant);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_ZoybeanPodSmoke>, m_smokeMachine);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_ZoybeanPod);
}
