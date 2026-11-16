//
//  Plant_SporeShroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_SporeShroom.h"

PlantSporeshroom::PlantSporeshroom()
{
}

PlantSporeshroom::~PlantSporeshroom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSporeshroom);

void PlantSporeshroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSporeshroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity>>, m_entitiesHitDuringPlantfood);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_nextPlantFoodTarget);
	REFLECTION_CLASSBUILDER_END(PlantSporeshroom);
}

void PlantSporeshroom::trySpawnPlantForZombie(Zombie * zombie)
{
}
