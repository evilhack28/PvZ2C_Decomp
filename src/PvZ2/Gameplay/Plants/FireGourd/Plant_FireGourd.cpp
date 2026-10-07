//
//  Plant_FireGourd.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_FireGourd.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantFireGourd);

void PlantFireGourd::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantFireGourd);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasStartedPlantfoodAttack);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_hitEntities);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<GridItemGourdFire>, m_gridFireAnim);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PopAnim>, m_firingAnim);
	REFLECTION_CLASSBUILDER_END(PlantFireGourd);
}

bool PlantFireGourd::CanApplyPlantfood()
{
	return true;
}

void PlantFireGourd::OnUseActionAnimCommand(pvztime_t i_timeStamp)
{
}

#include "Plant_FireGourd.h"
void PlantFireGourd::OnUseSpecialAnimCommand(pvztime_t i_timeStamp)
{
	 PlantFireGourd::willStartFiringAnimation();
}
