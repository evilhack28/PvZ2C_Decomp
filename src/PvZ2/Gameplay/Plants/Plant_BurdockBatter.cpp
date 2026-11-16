//
//  Plant_BurdockBatter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BurdockBatter.h"

PlantBurdockBatter::PlantBurdockBatter()
{
	m_isNextCriticalHit = 0;
	m_hasTriggerGene = 0;
}

PlantBurdockBatter::~PlantBurdockBatter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBurdockBatter);

void PlantBurdockBatter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBurdockBatter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ProjectilePropertySheet*>, m_validProjectileProps);
	REFLECTION_CLASSBUILDER_END(PlantBurdockBatter);
}

bool PlantBurdockBatter::CanApplyPlantfood()
{
	return true;
}
