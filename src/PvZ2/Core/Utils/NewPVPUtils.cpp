//
//  NewPVPUtils.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "NewPVPUtils.h"
#include "NewPVPGame.h"
#include "LawnApp.h"
#include "GameStateMgr.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "PlayerInfoLocalSaveData.h"

/////////////// Accessors ///////////////

bool NewPVPUtils::IsPlayingNewPVP()
{
	return gGameStateMgr && gGameStateMgr->GetLevelSource() == LEVELSOURCE_NewPVP;
}

bool NewPVPUtils::IsPlayingNewPVPTutorial()
{
	return ProfileMgr::GetInstance().GetCurrentProfile()->GetActiveTutorial() == TUTORIAL_NEWPVP;
}

bool NewPVPUtils::IsPlayingWithCPU()
{
	if (NewPVPMgr::GetInstancePtr()->GetMainEntryData().m_playerInfo.m_fightCount != 0)
		return false;
	if (GetCurrentCPULevel() >= NewPVPMgr::GetInstancePtr()->GetCPUInfoSize())
		return false;
	return !IsPlayingNewPVPTutorial();
}

bool NewPVPUtils::IsPlayingFakeMatch()
{
	return IsPlayingWithCPU() || IsPlayingNewPVPTutorial();
}

int NewPVPUtils::GetTutorialStep()
{
	if (IsPlayingNewPVPTutorial())
		return NewPVPMgr::GetInstancePtr()->GetTutorialStep();
	return -1;
}

int NewPVPUtils::GetCurrentCPULevel()
{
	return LocalProfileSaveData::GetCurrentNewPVPCPULevel(ProfileMgr::GetInstance().GetCurrentProfile());
}
