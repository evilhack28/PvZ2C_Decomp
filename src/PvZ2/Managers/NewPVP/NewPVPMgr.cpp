//
//  NewPVPMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "NewPVPGame.h"
#include "NewPVPUtils.h"

/////////////// Lifecycle ///////////////

void NewPVPMgr::Update()
{
	updateFrameCalc();
}

bool NewPVPMgr::canStartFrameCalc()
{
	return m_nextFramesCalcTime == PVZ_EOT();
}

bool NewPVPMgr::IsPreviousMatchingTimeout()
{
	return true;
}

void NewPVPMgr::StartFrameCalc()
{
	if (canStartFrameCalc())
	{
		ResetFrameInfo();
		m_nextFramesCalcTime = PVZ_RealT();
	}
}

void NewPVPMgr::ResetFrameInfo()
{
	m_frames = 0.0f;
	m_nextFramesCalcTime = PVZ_EOT();
	m_totalFramesFragment = 0.0f;
	m_framesCalcCount = 0;
	m_currentFrames = 0.0f;
	m_totalFrameFragmentCount = 0;
	for (int i = 0; i < MAX_FRAME_ARRAY_SIZE; i++)
		m_framesArray[i] = 0.0f;
}

void NewPVPMgr::updateFrameCalc()
{
	if (m_nextFramesCalcTime == PVZ_EOT())
		return;

	float aFPS = TimeMgr::GetInstancePtr()->GetCurrentFPS();
	if (m_frames != aFPS)
	{
		m_frames = aFPS;
		m_totalFrameFragmentCount++;
		m_totalFramesFragment += aFPS;
	}

	if (PVZ_RealT() - m_nextFramesCalcTime >= 1.0f)
	{
		float anAverage = m_totalFramesFragment / m_totalFrameFragmentCount;
		m_framesArray[m_framesCalcCount % MAX_FRAME_ARRAY_SIZE] = anAverage;
		m_framesCalcCount++;
		m_totalFrameFragmentCount = 0;
		m_frames = 0.0f;
		m_totalFramesFragment = 0.0f;
		m_currentFrames = anAverage;
		m_nextFramesCalcTime = PVZ_RealT();
	}
}

int NewPVPMgr::GetCurrentMaxPlantNum()
{
	return GetMaxPlantNum(m_currentSunLevel);
}

int NewPVPMgr::GetCurrentBattleIndex()
{
	return m_currentMainEntryData.m_zombiePlayerInfo.m_inBattleIndex;
}

int NewPVPMgr::GetEstimatedQueueingTime()
{
	return m_currentMainEntryData.m_estimatedQueueingTime;
}

float NewPVPMgr::GetSyncQueueInterval()
{
	return m_currentMainEntryData.m_syncQueueInterval;
}

float NewPVPMgr::GetSyncPlayerInterval()
{
	return m_currentMainEntryData.m_syncPlayerInterval;
}

float NewPVPMgr::GetSyncGameInterval()
{
	return m_currentMainEntryData.m_syncGameInterval;
}

bool NewPVPMgr::IsLastGameReachFPSLimit()
{
	return m_currentMainEntryData.m_lastGameLowFPS == 1;
}

bool NewPVPMgr::IsSeasonEnd()
{
	return m_currentMainEntryData.m_isSeasonEnd == 1;
}

bool NewPVPMgr::IsThirdSeason()
{
	return m_currentMainEntryData.m_seasonCount > 2;
}

int NewPVPMgr::GetCurrentTurn()
{
	if (!NewPVPUtils::IsPlayingNewPVP())
		return 0;
	return gLawnApp->m_board->GetGameSubSystem<NewPVPGameSubsystem>()->GetCurrentTurn();
}

int NewPVPMgr::GetMaxTurn()
{
	if (!NewPVPUtils::IsPlayingNewPVP())
		return 0;
	return gLawnApp->m_board->GetGameSubSystem<NewPVPGameSubsystem>()->GetMaxTurn();
}

int NewPVPMgr::GetSunAdd()
{
	if (!NewPVPUtils::IsPlayingNewPVP())
		return 0;
	return gLawnApp->m_board->GetGameSubSystem<NewPVPGameSubsystem>()->GetCurrentSunAdd();
}

int NewPVPMgr::GetMinEstimitedMatchingTime()
{
	return m_currentMainEntryData.m_estimitedMatchingTime[0];
}

int NewPVPMgr::GetMaxEstimitedMatchingTime()
{
	return m_currentMainEntryData.m_estimitedMatchingTime[1];
}
