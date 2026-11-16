//
//  Plant_Acorn.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Acorn.h"

PlantAcorn::PlantAcorn()
{
}

PlantAcorn::~PlantAcorn()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAcorn);

void PlantAcorn::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAcorn);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextLaserDamageTime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_hitEntities);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<AcornProjectile>, m_currentProjectile);
	REFLECTION_CLASSBUILDER_END(PlantAcorn);
}

bool PlantAcorn::CanApplyPlantfood()
{
	return true;
}
