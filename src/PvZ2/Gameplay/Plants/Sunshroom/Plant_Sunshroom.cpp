//
//  Plant_Sunshroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Sunshroom.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSunshroom);

void PlantSunshroom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSunshroom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantSunflower);

		REFLECTION_CLASSBUILDER_FIELD(uint8, m_currentGrowthStage);
	REFLECTION_CLASSBUILDER_END(PlantSunshroom);
}

#include "Plant_Sunflower.h"
void PlantSunshroom::onAnimStoppedCallback(const std::string& i_arg)
{
	 PlantSunflower::ApplyPlantfood();
}

void PlantSunshroom::onKilled(bool i_instantKill)
{
}
