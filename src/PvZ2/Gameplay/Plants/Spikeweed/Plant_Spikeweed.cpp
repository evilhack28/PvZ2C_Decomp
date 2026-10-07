//
//  Plant_Spikeweed.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Spikeweed.h"

PlantSpikeweed::PlantSpikeweed()
{
	m_plantfoodSpikesActive = 0;
	m_killedZombieCount = 0;
	m_isTransformed = 0;
}

PlantSpikeweed::~PlantSpikeweed()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSpikeweed);

void PlantSpikeweed::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSpikeweed);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<PopAnimRig> >, m_plantfoodSpikes);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_killedZombieCount);
	REFLECTION_CLASSBUILDER_END(PlantSpikeweed);
}

#include "Plant_Spikeweed.h"
void PlantSpikeweed::OnKillZombie(Zombie* i_zombie)
{
	 PlantSpikeweed::NotifyZombieKilled();
}

bool PlantSpikeweed::CanApplyPlantfood()
{
	return true;
}
