//
//  Plant_Dracaena.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Dracaena.h"

PlantDracaena::PlantDracaena()
{
}

PlantDracaena::~PlantDracaena()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantDracaena);

void PlantDracaena::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DracaenaPlantgfood);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_backwardsProjectiles);
	REFLECTION_CLASSBUILDER_END(DracaenaPlantgfood);

	REFLECTION_CLASSBUILDER_BEGIN(PlantDracaena);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_attackTimeStamp);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_target);
		REFLECTION_CLASSBUILDER_FIELD(DracaenaState, m_state);
	REFLECTION_CLASSBUILDER_END(PlantDracaena);
}

bool PlantDracaena::CanApplyPlantfood()
{
	return true;
}

void PlantDracaena::PlayAttackAnimation()
{
}
