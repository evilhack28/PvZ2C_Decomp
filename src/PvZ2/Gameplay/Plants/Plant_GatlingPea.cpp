//
//  Plant_GatlingPea.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_GatlingPea.h"

PlantGatlingPea::~PlantGatlingPea()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantGatlingPea);

void PlantGatlingPea::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantGatlingPea);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_RemainProjTime);
		REFLECTION_CLASSBUILDER_FIELD(float, m_ArcPelletRand);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_launchArcPellet);
		REFLECTION_CLASSBUILDER_FIELD(GatlingPeaPlantfood, m_plantfood);
	REFLECTION_CLASSBUILDER_END(PlantGatlingPea);
}

bool PlantGatlingPea::CanApplyPlantfood()
{
	return true;
}
