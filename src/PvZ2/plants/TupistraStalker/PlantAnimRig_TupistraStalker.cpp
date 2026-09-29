//
//  PlantAnimRig_TupistraStalker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_TupistraStalker.h"

PlantAnimRig_TupistraStalker::PlantAnimRig_TupistraStalker()
{
	m_submerged = 1;
}

PlantAnimRig_TupistraStalker::~PlantAnimRig_TupistraStalker()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_TupistraStalker);

void PlantAnimRig_TupistraStalker::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_TupistraStalker);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_submerged);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig_TupistraStalker);
}
