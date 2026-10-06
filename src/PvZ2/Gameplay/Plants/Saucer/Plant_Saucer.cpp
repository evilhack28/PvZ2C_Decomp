//
//  Plant_Saucer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Saucer.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSaucer);

void PlantSaucer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSaucer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, m_vStunedCache);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_iEndConditionTime);
	REFLECTION_CLASSBUILDER_END(PlantSaucer);
}

#include "PlantFramework.h"
void PlantSaucer::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

#include "PlantFramework.h"
bool PlantSaucer::CanEndPlantfood()
{
	return PlantFramework::CanEndPlantfood();
}
