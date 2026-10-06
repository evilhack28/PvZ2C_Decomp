//
//  Plant_Citron.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Citron.h"

PlantCitron::~PlantCitron()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCitron);

void PlantCitron::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCitron);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_hitTargets);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_releaseChainTime);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<class Projectile>, m_plantfood_proj);
	REFLECTION_CLASSBUILDER_END(PlantCitron);
}

bool PlantCitron::CanApplyPlantfood()
{
	return true;
}
