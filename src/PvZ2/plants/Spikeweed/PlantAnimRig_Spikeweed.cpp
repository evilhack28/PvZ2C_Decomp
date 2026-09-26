//
//  PlantAnimRig_Spikeweed.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Spikeweed.h"

PlantAnimRig_Spikeweed::PlantAnimRig_Spikeweed()
{
}

PlantAnimRig_Spikeweed::~PlantAnimRig_Spikeweed()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Spikeweed);

void PlantAnimRig_Spikeweed::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Spikeweed);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_isTransformed);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Spikeweed);
}
