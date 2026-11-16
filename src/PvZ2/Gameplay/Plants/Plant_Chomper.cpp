//
//  Plant_Chomper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Chomper.h"

PlantChomper::PlantChomper()
{
}

PlantChomper::~PlantChomper()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantChomper);

void PlantChomper::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantChomper);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie> >, m_suctionZombies);
		REFLECTION_CLASSBUILDER_FIELD(int, m_gulpZombieCount);
	REFLECTION_CLASSBUILDER_END(PlantChomper);
}

#include "PlantFramework.h"
void PlantChomper::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

bool PlantChomper::CanApplyPlantfood()
{
	return true;
}
