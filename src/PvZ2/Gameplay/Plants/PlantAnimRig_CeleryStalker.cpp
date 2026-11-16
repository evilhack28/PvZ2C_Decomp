//
//  PlantAnimRig_CeleryStalker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_CeleryStalker.h"

PlantAnimRig_CeleryStalker::PlantAnimRig_CeleryStalker()
{
	m_submerged = 1;
}

PlantAnimRig_CeleryStalker::~PlantAnimRig_CeleryStalker()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_CeleryStalker);

void PlantAnimRig_CeleryStalker::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_CeleryStalker);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_submerged);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_CeleryStalker);
}
