//
//  PVPManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "PVPManager.h"
#include "BoardDlg.h"
#include "TrainingCamp.h"
#include "PVP/PlaybackManager.h"
#include "LawnApp.h"

/////////////// Accessors ///////////////

bool PVPManager::IsInPVPMap()
{
	return m_mapType != 0;
}

/////////////// Lifecycle ///////////////

void PVPManager::Reset()
{
	m_bInitialised = false;
	if (m_pZombieCamp != nullptr)
	{
		delete m_pZombieCamp;
		m_pZombieCamp = nullptr;
	}
	m_ZombieDatas.clear();
	m_PVPCoin = 0;
	m_battlePingInterval = 30;
	m_defensePingInterval = 30;
	m_PVPMedal = 0;
	m_PVPCup = 0;
	m_gemToday = 0;
	m_PVPCupNeed = 0;
	m_PVPGoldCost = 0;
	m_pvpRequestStartTime = 0;
	m_isInGameEnding = false;
	m_currentPVPType = (ArenaType)0;
	m_leagueId = 0;
	m_nameChanged = false;
	m_isPreviewMode = false;
	m_rankCacheTime = 60.0f;
	m_pvpShopConfigData.clear();
	m_labData = PVPLabData();
	float eot = PVZ_EOT();
	m_upgradeConfig = nullptr;
	m_isPVPPrepare = false;
	m_startFromPVPPrepare = false;
	m_changePlayerCooldown = 0;
	m_defenderId = 0;
	m_mapType = (PVPMapType)0;
	m_bFirstLogin = true;
	m_revengeID = 0;
	m_endTimeTraining = eot;
	m_endTimeLab = eot;
	BoardDlg::s_NeedShow = true;
	m_doChangePlayer = false;
}

/////////////// Update ///////////////

void PVPManager::Update()
{
	if (IsInPVPMap())
	{
		if (m_doChangePlayer)
		{
			m_doChangePlayer = false;
			onDoChangePlayer();
		}
		else if (m_pZombieCamp != nullptr && gLawnApp->m_board == nullptr)
		{
			m_pZombieCamp->Update();
		}
	}
}

std::string PVPManager::GetProductVersion()
{
	return gLawnApp->mProductVersion.empty() ? std::string("9.9.9") : gLawnApp->mProductVersion;
}

void PVPManager::OnCloseDialog()
{
	gLawnApp->KillPVZ2Dialog();
}

void PVPManager::SetLeagueId(int iVal)
{
	m_leagueId = iVal;
}

void PVPManager::SetEvilDavidMaxChallengingTimes(int nCount)
{
	m_iEvilDavidMaxChallengingTimes = nCount;
}

int PVPManager::GetEvilDavidMaxChallengingTimes(void) const
{
	return m_iEvilDavidMaxChallengingTimes;
}

const std::vector<S2C_PVP_RankInfo>& PVPManager::GetRankList(int rankType)
{
	return rankType == 1 ? m_gardenRankInfoList : m_leagueRankInfoList;
}

int PVPManager::GetRankMaxCount(int rankType)
{
	if (rankType == 1)
		return m_gardenMaxCount;
	return m_leagueMaxCount;
}

void PVPManager::ClearRankList()
{
	m_gardenRankInfoList.clear();
	m_leagueRankInfoList.clear();
}

int PVPManager::TimeToGem(int seconds)
{
	return pow(seconds * 3.4722223e-05f, 0.7f) * 50.0 + 1.0;
}

bool PVPManager::IsInPlaybackMode()
{
	return gPlaybackMgr->IsPlaying();
}

TrainingCamp* PVPManager::GetZombieCamp()
{
	return m_pZombieCamp;
}
