//
//  Plant_Reincarnation.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Reincarnation.h"

PlantReincarnation::PlantReincarnation()
{
}

PlantReincarnation::~PlantReincarnation()
{
}

PlantReincarnationProps::PlantReincarnationProps()
{
}

PlantReincarnationProps::~PlantReincarnationProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantReincarnation);

void PlantReincarnation::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantReincarnation);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_petals);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasPlayedPlantFoodAnimation);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<class Projectile>, m_plantfood_proj);
	REFLECTION_CLASSBUILDER_END(PlantReincarnation);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantReincarnationProps);

void PlantReincarnationProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantReincarnationProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, PetalAmount);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, RecoveryTime);
	REFLECTION_CLASSBUILDER_END(PlantReincarnationProps);
}
