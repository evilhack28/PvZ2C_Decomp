//
//  Plant_CeleryStalker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_CeleryStalker.h"

PlantCeleryStalker::PlantCeleryStalker()
{
}

PlantTypeCeleryStalker::PlantTypeCeleryStalker()
{
}

PlantTypeCeleryStalker::~PlantTypeCeleryStalker()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCeleryStalker);

void PlantCeleryStalker::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCeleryStalker);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_lastAttack);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_BounceZombieEnabled);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Plant>>, m_PFSpawnedStalkers);
	REFLECTION_CLASSBUILDER_END(PlantCeleryStalker);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantTypeCeleryStalker);

#include "Plant_CeleryStalker.h"
void PlantCeleryStalker::onHealed()
{
	 PlantCeleryStalker::updateDamageVisuals();
}
