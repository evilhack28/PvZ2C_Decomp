//
//  WorldCupMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldCupMgr.h"
#include "IntroWorldCup.h"
#include "OutroModule.h"
#include "SoccerGameModule.h"
#include "WorldCupConfig.h"
#include "GameEventMgr.h"
#include "LawnApp.h"
#include "Board.h"

WorldCupMgr::~WorldCupMgr()
{
}

WorldCupMgr::WorldCupMgr()
{
	m_currentSetStartingSun = 0;
	m_currentSetId = 0;
}

bool WorldCupMgr::IsTutorial()
{
	IntroWorldCup* intro = gLawnApp->m_board->GetLevelModuleManager()->GetModuleByClass<IntroWorldCup>();
	if (intro == nullptr)
		return false;
	return intro->IsTutorial();
}

pvztime_t WorldCupMgr::GetGameEndTime()
{
	SoccerGameModule* soccer = gLawnApp->m_board->GetLevelModuleManager()->GetModuleByClass<SoccerGameModule>();
	if (soccer == nullptr)
		return pvztime_t(0);
	return soccer->GetGameEndTime();
}

int WorldCupMgr::GetCurrentScore(bool i_zombie)
{
	SoccerGameModule* soccer = gLawnApp->m_board->GetLevelModuleManager()->GetModuleByClass<SoccerGameModule>();
	if (soccer == nullptr)
		return 0;
	if (i_zombie)
		return soccer->GetZombieScore();
	return soccer->GetPlantScore();
}

bool WorldCupMgr::ShouldDoTutorial(TutorialStateType i_type)
{
	IntroWorldCup* intro = gLawnApp->m_board->GetLevelModuleManager()->GetModuleByClass<IntroWorldCup>();
	if (intro == nullptr)
		return false;
	int stateByType = intro->GetTutorialStateByType(i_type);
	return intro->GetTutorialState() < stateByType;
}

void WorldCupMgr::NotifyTutorialState(TutorialStateType i_type)
{
	if (!IsTutorial())
		return;
	if (ShouldDoTutorial(i_type))
		gMessageRouter->Post(&Message::NotifyTutorialState, (int)i_type);
}

int WorldCupMgr::GetCurrentSetSize()
{
	return gLawnApp->GetWorldCupConfig().GetTargetSetLocations(m_currentSetId).size();
}

void WorldCupMgr::SetCarrierForTutorial(RtWeakPtr<Zombie> i_carrier)
{
	if (!IsTutorial())
		return;
	IntroWorldCup* intro = gLawnApp->m_board->GetLevelModuleManager()->GetModuleByClass<IntroWorldCup>();
	if (intro != nullptr)
		intro->SetCarrierForTutorial(i_carrier);
}

Point WorldCupMgr::GetRandomPlantSpotForTutorial()
{
	std::vector<ObstacleNonSpawnData> locations = gLawnApp->GetWorldCupConfig().GetTargetSetLocations(m_currentSetId);
	ObstacleNonSpawnData& spot = locations.at(Sexy::Rand((int)locations.size()));
	return Point(spot.GridX, spot.GridY);
}

bool WorldCupMgr::IsPlantDisabled(int i_x, int i_y)
{
	std::vector<ObstacleNonSpawnData> locations = gLawnApp->GetWorldCupConfig().GetTargetSetLocations(m_currentSetId);
	bool result = locations.empty();
	if (!result)
	{
		size_t n = locations.size();
		for (size_t i = 0; i != n; i++)
		{
			if (locations[i].GridX != i_x)
				continue;
			if (locations[i].GridY == i_y)
				goto done;
		}
		result = true;
	}
done:
	return result;
}

void WorldCupMgr::InitTestData()
{
	SetCurrentSetStartingSun(10000);
	m_currentSet.push_back("sunshroom");
	m_currentSet.push_back("wallnut");
	m_currentSet.push_back("homingthistle");
	m_currentSetId = 102;
}
