//
//  Plant_Draftodil.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Draftodil.h"

PlantDraftodil::~PlantDraftodil()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantDraftodil);

void PlantDraftodil::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantDraftodil);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_currPFLoopShotCount);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie>>, m_plantfoodAlreadyHitZombies);
	REFLECTION_CLASSBUILDER_END(PlantDraftodil);
}

bool PlantDraftodil::CanBeShoveled()
{
	return true;
}

bool PlantDraftodil::CanBeTargeted()
{
	return true;
}

bool PlantDraftodil::CanApplyPlantfood()
{
	return true;
}
