//
//  Plant_Egretflower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Egretflower.h"

PlantEgretflower::~PlantEgretflower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantEgretflower);

void PlantEgretflower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantEgretflower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextMissile);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isUnion);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PopAnim>, m_linkingEffect);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<Sexy::Point>, m_targets);
	REFLECTION_CLASSBUILDER_END(PlantEgretflower);
}

#include "PlantFramework.h"
void PlantEgretflower::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}
