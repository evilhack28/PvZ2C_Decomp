//
//  Plant_Sugarcane.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Sugarcane.h"

PlantSugarcane::PlantSugarcane()
{
}

PlantSugarcane::~PlantSugarcane()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSugarcane);

void PlantSugarcane::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSugarcane);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_killed);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextRecoverTime);
		REFLECTION_CLASSBUILDER_FIELD(ZombieRepulseSystem, m_repulseSystem);
		REFLECTION_CLASSBUILDER_FIELD(TransfromKeyFrameSystem, m_keyFrameSystem);
	REFLECTION_CLASSBUILDER_END(PlantSugarcane);
}
