//
//  GameStateMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GameStateMgr.h"
#include "GameStateTransitionController.h"
#include "LawnApp.h"
#include "PVP/PVPLab.h"
#include "GemOfferMgr.h"
#include "ProfileUtils.h"
#include "PlantTrialConfig.h"
#include "TransitionOverlayWidget.h"
#include "PVZGameState.h"
#include "FestivalEventUI.h"
#include "ActivityManager.h"
#include "PVZ2UIDialog.h"
#include "PrimeText_Game.h"
#include "TodLib/TodCommon.h"
#include "ScaledApp.h"
#include "Board.h"
#include "SaveGameMgr.h"
#include "JoustDashboardLoadingState.h"
#include "JoustLandingScreenState.h"
#include "JoustOrAdventureScreenState.h"
#include "JoustTournamentEndScreenState.h"
#include "NewPlantUI.h"
#include "NewPVPGame.h"
#include "PVZ1DashboardLoadingState.h"
#include "RichManScreenState.h"
#include "RiftDashboardLoadingState.h"
#include "RiftTournamentEndScreenState.h"
#include "IdentifierMgr.h"
#include "PlantFamilyMgr.h"
#include "PVP/PVPManager.h"
#include "PVP/PVPEntryDlg.h"
#include "DangerRoomManager.h"
#include "UIDangerRoomSkipLevel.h"
#include "BusyAnimationManager.h"
#include "PVZ1ModeUtils.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "RiftDataPacket.h"
#include "Cheats.h"
#include "gameNetWork/NetworkMgr.h"
#include "gameNetWork/NetworkMsgProcess.h"
#include "IdentityMessages.h"
#include "WorldMap.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

#include "ReflectionBuilder.h"

namespace Message { void GameLoad(int); void LevelLoadComplete(); void WorldMapLoadComplete(); void RiftNetworkResponseReceived(int, int); void PVZ1ModeNetworkResponseReceived(int, int); }

namespace RiftUtils { void ShowRiftNetworkIssuePopup(RiftAPINetworkIssue i_error, RiftAPIContext i_context); }

static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

RT_CLASS_IMPLEMENT(GameStateMgr);

void GameStateMgr::ShowDangerRoom(GameTransitionType i_out, GameTransitionType i_in)
{
}

GameStateMgr& GameStateMgr::operator=(const GameStateMgr&) = default;

/////////////// Show ///////////////

void GameStateMgr::ShowLevelUp(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_LevelUp, i_out, i_in);
}

void GameStateMgr::ShowLottery(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_Lottery, i_out, i_in);
}

void GameStateMgr::Show5thCenter(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_5thCenter, i_out, i_in);
}

void GameStateMgr::ShowPlantTrial(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_PlantTrial, i_out, i_in);
}

void GameStateMgr::ShowConsumption(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_Consumption, i_out, i_in);
}

void GameStateMgr::ShowCustomLevel(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_CustomLevel, i_out, i_in);
}

void GameStateMgr::ShowPlantAvatar(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_PlantAvatar, i_out, i_in);
}

void GameStateMgr::ShowPlantFamily(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_PlantFamily, i_out, i_in);
}

void GameStateMgr::ShowActiveCenter(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_ActiveCenter, i_out, i_in);
}

void GameStateMgr::ShowNostalgiaPVZ(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_NostalgiaPVZ, i_out, i_in);
}

void GameStateMgr::ShowRichManScreen(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_RichManScreen, i_out, i_in);
}

void GameStateMgr::ShowFestivalCenter(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_FestivalCenter, i_out, i_in);
}

void GameStateMgr::ShowPlantAdventure(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_PlantAdventure, i_out, i_in);
}

void GameStateMgr::ShowRechargeWelfare(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_RechargeWelfare, i_out, i_in);
}

void GameStateMgr::ShowDailyAchievement(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_DailyAchievement, i_out, i_in);
}

void GameStateMgr::ShowArtifactCultivation(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_ArtifactCultivation, i_out, i_in);
}

void GameStateMgr::ShowPlantGeneEnhancement(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_PlantGeneEnhancement, i_out, i_in);
}

void GameStateMgr::ShowNewPVPMainEntryScreen(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_NewPVPMainEntryScreen, i_out, i_in);
}

void GameStateMgr::ShowRiftTournamentEndScreen(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_RiftTournamentEndScreen, i_out, i_in);
}

void GameStateMgr::ShowJoustTournamentEndScreen(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_JoustTournamentEndScreen, i_out, i_in);
}

void GameStateMgr::ShowJoustOrAdventureLandingScreen(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_JoustOrAdventureSelector, i_out, i_in);
}

void GameStateMgr::ShowJoustDashboardScreenAfterDashboardFetch(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_JoustDashboardScreen, i_out, i_in);
}

void GameStateMgr::showMainMenuWithoutLoadingData(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_MainMenu, i_out, i_in);
}

void GameStateMgr::TranslateTo(GameState i_targetState, GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(i_targetState, i_out, i_in);
}

void GameStateMgr::ShowRiftMap()
{
	transitionToState(GAME_RiftLoadDashboard, GAMETRANSITION_None, GAMETRANSITION_None);
}

void GameStateMgr::ShowPVZ1Map()
{
	transitionToState(GAME_PVZ1LoadDashboard, GAMETRANSITION_None, GAMETRANSITION_None);
}

void GameStateMgr::ShowJoustDashboardScreen()
{
	transitionToState(GAME_JoustLoadDashboard, GAMETRANSITION_None, GAMETRANSITION_None);
}

void GameStateMgr::ShowDangerRoomSkipLevel()
{
	transitionToState(GAME_DangerRoomSkipLevel, GAMETRANSITION_QuickSpiral, GAMETRANSITION_QuickSpiral);
}

void GameStateMgr::ShowRedPack(FestivalEventType i_type, GameTransitionType i_out, GameTransitionType i_in)
{
	m_eventType = i_type;
	transitionToState(GAME_RedPack, i_out, i_in);
}

void GameStateMgr::ShowLanternRiddles(const bool& i_canRiddle, GameTransitionType i_out, GameTransitionType i_in)
{
	m_queuedBool = i_canRiddle;
	transitionToState(GAME_Lantern, i_out, i_in);
}

void GameStateMgr::ShowWorldMapWithDestination(const MapEventItem* i_destination, GameTransitionType i_out, GameTransitionType i_in)
{
	m_queuedWorldMapDestination = i_destination;
	ShowWorldMap(i_out, i_in);
}

void GameStateMgr::ShowLogoScreen()
{
	setState(GAME_LogoScreen);
}

void GameStateMgr::ShowDirtyAccountScreen()
{
	setState(GAME_DirtyAccount);
}

void GameStateMgr::ShutDown()
{
	setState(GAME_Unloaded);
}

/////////////// Transitions ///////////////

void GameStateMgr::ShowMainMenu(GameTransitionType i_out, GameTransitionType i_in)
{
	gMessageRouter->Post(Message::ForceReloadData);
	showMainMenuWithoutLoadingData(i_out, i_in);
}

void GameStateMgr::ShowWorldMap(GameTransitionType i_out, GameTransitionType i_in)
{
	GemOfferMgr::GetInstance().ResetHintTimes();
	transitionToState(GAME_WorldMap, i_out, i_in);
}

void GameStateMgr::ShowStore(const std::string& i_focusPanel, GameTransitionType i_out, GameTransitionType i_in)
{
	m_queuedStorePanel = i_focusPanel;
	transitionToState(GAME_Store, i_out, i_in);
}

void GameStateMgr::DoStateChange(GameState i_newState)
{
	if (m_stateMachine.GetState() != i_newState)
		setState(i_newState);
	else
		m_stateMachine.ReenterState();
}

void GameStateMgr::QueueWarpTunnel()
{
	m_transitionController->SetFullScreenTransitionType(PVZ1ModeUtils::IsPlayingPVZ1Tutorial() ? FS_TRANSITION_TimewarpPVZ1 : FS_TRANSITION_Timewarp);
}

void GameStateMgr::transitionToState(GameState i_targetState, GameTransitionType i_out, GameTransitionType i_in)
{
	m_transitioningFromState = m_stateMachine.GetState();
	m_transitionController->TransitionToState(i_targetState, i_out, i_in);
}

void GameStateMgr::setState(GameState i_state)
{
	m_stateMachine.SetState(m_stateTable[i_state]);
}

void GameStateMgr::Update()
{
	if (m_transitionController)
		m_transitionController->Update();
	m_stateMachine.UpdateState();
}

void GameStateMgr::onGetLoginReward()
{
	gLawnApp->KillPVZ2Dialog();
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	profile->setQihooLoginReward(true);
	profile->AddGems(35, true);
}

void GameStateMgr::onSuccessResponse()
{
	ProfileMgr::GetInstance().GetCurrentProfile();
	gGameStateMgr->ShowRiftMap();
}

void GameStateMgr::onRiftNetworkResponse(int i_context, int i_status)
{
	if (i_context == 1)
	{
		if (i_status == 2)
			onSuccessResponse();
		else if (i_status == 4)
			RiftUtils::ShowRiftNetworkIssuePopup(RiftAPINetworkIssue::InvalidMatch, RiftAPIContext::Get_MainEntry);
	}
}

void GameStateMgr::onPVZ1NetworkResponse(int i_context, int i_status)
{
	if (i_context == 1)
	{
		switch (i_status)
		{
		case 2:
			gGameStateMgr->ShowPVZ1Map();
			break;
		}
	}
}

void GameStateMgr::onWWANDialogCancel()
{
	gLawnApp->KillPVZ2Dialog();
	Android::Device::ExitApp();
}

void GameStateMgr::onEnterState_DirtyAccount(GameState i_fromState)
{
	gLawnApp->RemoveAllCaches();
	NetworkMgr::Instance()->GetNewNetWorkProcess()->ICloudRequestClearNotifyThirdPartPlatforms();
}

void GameStateMgr::onEnterState_PlantAdventure(GameState i_fromState)
{
	gLawnApp->ShowPlantAdventureUI();
	CheatManager::GetInstancePtr()->SetCurrentContext(CHEATCONTEXT_Adventure);
}

void GameStateMgr::onExitState_PlantTrial(GameState i_toState)
{
	gLawnApp->KillPlantTrialView();
	gMessageRouter->Post(Message::PlantTrialDialogClosed);
}

void GameStateMgr::ShowAlmanac(ObjectTypeDescriptorPtr i_objectType, GameTransitionType i_out, GameTransitionType i_in)
{
	m_queuedObjectForAlmanac = i_objectType;
	transitionToState(GAME_Almanac, i_out, i_in);
}

void GameStateMgr::ShowNewPlantUIEntryScreen(GameTransitionType i_out, GameTransitionType i_in)
{
	transitionToState(GAME_NewPlantUIEntryScreen, i_out, i_in);
}

void GameStateMgr::ShowPVPMap(GameTransitionType i_out, GameTransitionType i_in)
{
	if (m_transitionController->GetQueuedStateChange() == -1)
		transitionToState(GAME_PVPMap, i_out, i_in);
}

void GameStateMgr::StartLevelFromSave(const std::string& i_newLevel, GameTransitionType i_out, GameTransitionType i_in)
{
	gLawnApp->m_busyManager->StartBusyIcon();
	m_queuedLevel = i_newLevel;
	m_queuedLevelFromSave = true;
	transitionToState(GAME_Game, i_out, i_in);
}

void GameStateMgr::WaitForNetworkLoad()
{
	if (gLawnApp->HasPlayerUnlockedFeature(FEATURE_WORLDMAP))
	{
		TodHesitationTrace("GameStateMgr::WaitForNetworkLoad() load rsb");
		transitionToState(GAME_WaitForNetworkLoad, GAMETRANSITION_None, GAMETRANSITION_None);
	}
	else
	{
		TodHesitationTrace("GameStateMgr::WaitForNetworkLoad() load rsb grass");
		transitionToState(GAME_WaitForNetworkLoad, GAMETRANSITION_QuickGrass, GAMETRANSITION_None);
	}
}

void GameStateMgr::onWWANDialogOK()
{
	gLawnApp->KillPVZ2Dialog();
}

void GameStateMgr::onNotConnectedDialogOK()
{
	gLawnApp->KillPVZ2Dialog();
	Android::Device::ExitApp();
}

void GameStateMgr::updateState_WaitForNetworkLoad()
{
	if (m_transitionController->GetQueuedStateChange() == -1)
	{
		gLawnApp->GetTransitionOverlay()->StopTransition();
		if (!ProfileUtils::Profile()->GetHasBeenConvertedToNewMap())
			ProfileUtils::ConvertOldProfileToNewMap(ProfileUtils::Profile());
		Sexy::OutputDebugStrF("WorldMapTransitionDecider::PickTutorialOrWorldMap() load rsb");
		WorldMapTransitionDecider::PickTutorialOrWorldMap();
	}
}

void GameStateMgr::updateState_GenericGameState()
{
	if (m_activeGameState->IsFullyLoadedAndVisible())
		m_transitionController->SetCoveringLoad(false);
	m_activeGameState->Update();
}

void GameStateMgr::onEnterState_PlantTrial(GameState i_fromState)
{
	gLawnApp->ShowPlantTrialView(gLawnApp->GetPlantTrialConfig().GetTrialDataCache().strPlant);
}

/////////////// Resource groups ///////////////

void GameStateMgr::onEnterState_5thCenter(GameState i_fromState)
{
	gLawnApp->LoadGroup("UI_Consumption_Reward");
	gLawnApp->LoadGroup("UI_Fragment_Pieces");
	gLawnApp->LoadGroup("UI_Fragment_Avatar");
	gLawnApp->LoadGroup("UI_Accessory_Dev2");
	gLawnApp->LoadGroup("UI_Store");
	gLawnApp->LoadGroup("UI_LevelUp");
	gLawnApp->LoadGroup("Gacha");
	gLawnApp->LoadGroup("Effects_LevelUp");
	gLawnApp->LoadGroup("UI_PlantAdventure");
	gLawnApp->LoadGroup("UI_Activity");
	gLawnApp->LoadGroup("UI_GLLottery");
	gLawnApp->LoadGroup("UI_ActivityCommon");
	gLawnApp->LoadGroup("UI_HeadShot_Plant");
}

void GameStateMgr::onExitState_5thCenter(GameState i_toState)
{
	gLawnApp->DeleteGroup("UI_Consumption_Reward");
	gLawnApp->DeleteGroup("UI_Fragment_Pieces");
	gLawnApp->DeleteGroup("UI_Fragment_Avatar");
	gLawnApp->DeleteGroup("UI_Accessory_Dev2");
	gLawnApp->DeleteGroup("UI_Store");
	gLawnApp->DeleteGroup("UI_LevelUp");
	gLawnApp->DeleteGroup("Gacha");
	gLawnApp->DeleteGroup("Effects_LevelUp");
	gLawnApp->DeleteGroup("UI_Activity");
	gLawnApp->DeleteGroup("UI_GLLottery");
	gLawnApp->DeleteGroup("UI_ActivityCommon");
	gLawnApp->DeleteGroup("UI_PlantAdventure");
	gLawnApp->DeleteGroup("UI_HeadShot_Plant");
}

void GameStateMgr::onEnterState_FestivalCenter(GameState i_fromState)
{
	gLawnApp->LoadGroup("UI_Consumption_Reward");
	gLawnApp->LoadGroup("UI_Fragment_Pieces");
	gLawnApp->LoadGroup("UI_Fragment_Avatar");
	gLawnApp->LoadGroup("UI_Accessory_Dev2");
	gLawnApp->LoadGroup("UI_Store");
	gLawnApp->LoadGroup("UI_LevelUp");
	gLawnApp->LoadGroup("Gacha");
	gLawnApp->LoadGroup("Effects_LevelUp");
	gLawnApp->LoadGroup("UI_PlantAdventure");
	gLawnApp->LoadGroup("UI_Activity");
	gLawnApp->LoadGroup("UI_GLLottery");
	gLawnApp->LoadGroup("UI_ActivityCommon");
	FestivalEventUI::ShowDialog();
}

void GameStateMgr::onExitState_FestivalCenter(GameState i_toState)
{
	FestivalEventUI::CloseDialog();
	gLawnApp->DeleteGroup("UI_Consumption_Reward");
	gLawnApp->DeleteGroup("UI_Fragment_Pieces");
	gLawnApp->DeleteGroup("UI_Fragment_Avatar");
	gLawnApp->DeleteGroup("UI_Accessory_Dev2");
	gLawnApp->DeleteGroup("UI_Store");
	gLawnApp->DeleteGroup("UI_LevelUp");
	gLawnApp->DeleteGroup("Gacha");
	gLawnApp->DeleteGroup("Effects_LevelUp");
	gLawnApp->DeleteGroup("UI_Activity");
	gLawnApp->DeleteGroup("UI_GLLottery");
	gLawnApp->DeleteGroup("UI_ActivityCommon");
	gLawnApp->DeleteGroup("UI_PlantAdventure");
}

void GameStateMgr::onEnterState_RechargeWelfare(GameState i_fromState)
{
	gLawnApp->LoadGroup("UI_Consumption_Reward");
	gLawnApp->LoadGroup("UI_Fragment_Pieces");
	gLawnApp->LoadGroup("UI_Fragment_Avatar");
	gLawnApp->LoadGroup("UI_Accessory_Dev2");
	gLawnApp->LoadGroup("UI_Store");
	gLawnApp->LoadGroup("UI_LevelUp");
	gLawnApp->LoadGroup("Gacha");
	gLawnApp->LoadGroup("Effects_LevelUp");
	gLawnApp->LoadGroup("UI_PlantAdventure");
	gLawnApp->LoadGroup("UI_Activity");
	gLawnApp->LoadGroup("UI_GLLottery");
	gLawnApp->LoadGroup("UI_ActivityCommon");
	RechargeWelfareUI::ShowDialog();
}

void GameStateMgr::onExitState_RechargeWelfare(GameState i_toState)
{
	RechargeWelfareUI::CloseDialog();
	gLawnApp->DeleteGroup("UI_Consumption_Reward");
	gLawnApp->DeleteGroup("UI_Fragment_Pieces");
	gLawnApp->DeleteGroup("UI_Fragment_Avatar");
	gLawnApp->DeleteGroup("UI_Accessory_Dev2");
	gLawnApp->DeleteGroup("UI_Store");
	gLawnApp->DeleteGroup("UI_LevelUp");
	gLawnApp->DeleteGroup("Gacha");
	gLawnApp->DeleteGroup("Effects_LevelUp");
	gLawnApp->DeleteGroup("UI_Activity");
	gLawnApp->DeleteGroup("UI_GLLottery");
	gLawnApp->DeleteGroup("UI_ActivityCommon");
	gLawnApp->DeleteGroup("UI_PlantAdventure");
}

void GameStateMgr::onEnterState_ActiveCenter(GameState i_fromState)
{
	gLawnApp->LoadGroup("UI_Consumption_Reward");
	gLawnApp->LoadGroup("UI_Fragment_Pieces");
	gLawnApp->LoadGroup("UI_Fragment_Avatar");
	gLawnApp->LoadGroup("UI_Accessory_Dev2");
	gLawnApp->LoadGroup("UI_Store");
	gLawnApp->LoadGroup("UI_LevelUp");
	gLawnApp->LoadGroup("Gacha");
	gLawnApp->LoadGroup("Effects_LevelUp");
	gLawnApp->LoadGroup("UI_PlantAdventure");
	gLawnApp->LoadGroup("UI_Activity");
	gLawnApp->LoadGroup("UI_GLLottery");
	gLawnApp->LoadGroup("UI_ActivityCommon");
}

void GameStateMgr::onExitState_ActiveCenter(GameState i_toState)
{
	gLawnApp->DeleteGroup("UI_Consumption_Reward");
	gLawnApp->DeleteGroup("UI_Fragment_Pieces");
	gLawnApp->DeleteGroup("UI_Fragment_Avatar");
	gLawnApp->DeleteGroup("UI_Accessory_Dev2");
	gLawnApp->DeleteGroup("UI_Store");
	gLawnApp->DeleteGroup("UI_LevelUp");
	gLawnApp->DeleteGroup("Gacha");
	gLawnApp->DeleteGroup("Effects_LevelUp");
	gLawnApp->DeleteGroup("UI_Activity");
	gLawnApp->DeleteGroup("UI_GLLottery");
	gLawnApp->DeleteGroup("UI_ActivityCommon");
	gLawnApp->DeleteGroup("UI_PlantAdventure");
}

void GameStateMgr::onEnterState_RedPack(GameState i_fromState)
{
	gLawnApp->LoadGroup("UI_RedPack");
	gLawnApp->LoadGroup("UI_Lantern");
	gLawnApp->LoadGroup("UI_Store");
	gLawnApp->LoadGroup("UI_Fragment_Pieces");
	gLawnApp->LoadGroup("UI_Fragment_Avatar");
	gLawnApp->LoadGroup("UI_Accessory_Dev2");
	gLawnApp->LoadGroup("UI_HeadShot_BigPlant");
	gLawnApp->LoadGroup("UI_HeadShot_Plant");
	gLawnApp->LoadGroup("UI_GachaDetail");
	gLawnApp->ShowRedPackUI(m_eventType);
}

void GameStateMgr::onExitState_RedPack(GameState i_toState)
{
	gLawnApp->KillRedPackUI();
	gLawnApp->DeleteGroup("UI_RedPack");
	gLawnApp->DeleteGroup("UI_Lantern");
	gLawnApp->DeleteGroup("UI_Store");
	gLawnApp->DeleteGroup("UI_Fragment_Pieces");
	gLawnApp->DeleteGroup("UI_Fragment_Avatar");
	gLawnApp->DeleteGroup("UI_Accessory_Dev2");
	gLawnApp->DeleteGroup("UI_HeadShot_BigPlant");
	gLawnApp->DeleteGroup("UI_HeadShot_Plant");
	gLawnApp->DeleteGroup("UI_GachaDetail");
}

void GameStateMgr::onEnterState_Lantern(GameState i_fromState)
{
	gLawnApp->LoadGroup("Effects_SignReward");
	gLawnApp->LoadGroup("UI_Lantern");
	gLawnApp->LoadGroup("UI_Store");
	gLawnApp->LoadGroup("GoldCan");
	gLawnApp->LoadGroup("UI_Fragment_Pieces");
	gLawnApp->LoadGroup("UI_HeadShot_Plant");
	gLawnApp->LoadGroup("Plantback");
	gLawnApp->ShowLanternRiddlesUI(m_queuedBool);
}

void GameStateMgr::onExitState_Lantern(GameState i_toState)
{
	gLawnApp->KillLanternRiddlesUI();
	gLawnApp->DeleteGroup("Effects_SignReward");
	gLawnApp->DeleteGroup("UI_Lantern");
	gLawnApp->DeleteGroup("UI_Store");
	gLawnApp->DeleteGroup("GoldCan");
	gLawnApp->DeleteGroup("UI_Fragment_Pieces");
	gLawnApp->DeleteGroup("UI_HeadShot_Plant");
	gLawnApp->DeleteGroup("Plantback");
}

void GameStateMgr::onEnterState_Consumption(GameState i_fromState)
{
	gLawnApp->LoadGroup("UI_Consumption_Reward");
	gLawnApp->LoadGroup("UI_Fragment_Pieces");
	gLawnApp->LoadGroup("UI_Fragment_Avatar");
	gLawnApp->LoadGroup("UI_Accessory_Dev2");
	gLawnApp->LoadGroup("UI_Store");
	gLawnApp->LoadGroup("UI_LevelUp");
	gLawnApp->LoadGroup("Gacha");
	gLawnApp->ShowConsumptionRewardDialog();
}

void GameStateMgr::onExitState_Consumption(GameState i_toState)
{
	gLawnApp->KillConsumptionRewardDialog();
	gLawnApp->DeleteGroup("UI_Consumption_Reward");
	gLawnApp->DeleteGroup("UI_Fragment_Pieces");
	gLawnApp->DeleteGroup("UI_Fragment_Avatar");
	gLawnApp->DeleteGroup("UI_Accessory_Dev2");
	gLawnApp->DeleteGroup("UI_Store");
	gLawnApp->DeleteGroup("UI_LevelUp");
	gLawnApp->DeleteGroup("Gacha");
}

void GameStateMgr::onExitState_Almanac(GameState i_toState)
{
	gLawnApp->KillAlmanac();
	gLawnApp->DeleteGroup("UI_Almanac");
	gLawnApp->DeleteGroup("UI_ZombieAlmanac");
	gLawnApp->DeleteGroup("UI_ZombieAlmanac_Dynamic");
	gLawnApp->DeleteGroup("PowerUpIcons");
	gLawnApp->DeleteGroup("GameUpgrades");
}

void GameStateMgr::onExitState_Store(GameState i_toState)
{
	gLawnApp->KillStoreUI();
	gLawnApp->DeleteGroup("UI_Store");
	gLawnApp->DeleteGroup("GameUpgrades");
	gLawnApp->DeleteGroup("UI_LevelUp");
	gLawnApp->DeleteGroup("UI_SkillDisplay");
	gLawnApp->DeleteGroup("Effects_LevelUp");
}

void GameStateMgr::onEnterState_DailyAchievement(GameState i_fromState)
{
	gLawnApp->LoadGroup("UI_DailyAchievement");
	gLawnApp->LoadGroup("UI_Fragment_Pieces");
	gLawnApp->LoadGroup("UI_Fragment_Avatar");
	gLawnApp->LoadGroup("UI_Accessory_Dev2");
	gLawnApp->LoadGroup("UI_Store");
	gLawnApp->ShowDailyAchievement();
}

void GameStateMgr::onExitState_DailyAchievement(GameState i_toState)
{
	gLawnApp->KillDailyAchievement();
	gLawnApp->DeleteGroup("UI_DailyAchievement");
	gLawnApp->DeleteGroup("UI_Fragment_Pieces");
	gLawnApp->DeleteGroup("UI_Fragment_Avatar");
	gLawnApp->DeleteGroup("UI_Accessory_Dev2");
	gLawnApp->DeleteGroup("UI_Store");
}

void GameStateMgr::onEnterState_Almanac(GameState i_fromState)
{
	gLawnApp->LoadGroup("UI_Almanac");
	gLawnApp->LoadGroup("UI_ZombieAlmanac");
	gLawnApp->LoadGroup("UI_ZombieAlmanac_Dynamic");
	gLawnApp->LoadGroup("PowerUpIcons");
	gLawnApp->LoadGroup("GameUpgrades");
	gLawnApp->ShowAlmanac(m_queuedObjectForAlmanac);
	CheatManager::GetInstancePtr()->SetCurrentContext(CHEATCONTEXT_Almanac);
}

void GameStateMgr::onEnterState_Store(GameState i_fromState)
{
	gLawnApp->LoadGroup("UI_Store");
	gLawnApp->LoadGroup("GameUpgrades");
	gLawnApp->LoadGroup("UI_LevelUp");
	gLawnApp->LoadGroup("UI_SkillDisplay");
	gLawnApp->LoadGroup("Effects_LevelUp");
	gLawnApp->ApplyNetworkContentChanges();
	gLawnApp->ShowStoreUI(m_queuedStorePanel);
	CheatManager::GetInstancePtr()->SetCurrentContext(CHEATCONTEXT_Store);
}

void GameStateMgr::onExitState_PVPMap(GameState i_toState)
{
	gLawnApp->KillPVPMapUI();
	gLawnApp->KillPVZ2Dialog();
	if (i_toState != GAME_PVPEntry && i_toState != GAME_PVPLab)
	{
		gLawnApp->StopMusic("Stop_Music_PVP_Street");
		gLawnApp->DeleteGroup("PVPGlobalAudio");
	}
}

void GameStateMgr::onEnterState_DangerRoomSkipLevel(GameState i_fromState)
{
	if (DangerRoomManager::GetInstancePtr()->GetDangerRoomType() == DangerRoom_Training)
	{
		UIDangerRoomTrainingSkipLevel::ShowDialog();
		return;
	}
	UIDangerRoomSkipLevel* dialog = UIDangerRoomSkipLevel::ShowDialog();
	if (i_fromState == GAME_Game)
	{
		int currentLevel = DangerRoomManager::GetInstancePtr()->GetCurrentLevel();
		int sunNum = DangerRoomManager::GetInstancePtr()->GetSunNum();
		int levelSunAdd = DangerRoomManager::GetInstancePtr()->GetLevelSunAdd();
		dialog->SkipToLevel(currentLevel, currentLevel + 1);
		dialog->SetSun(sunNum - levelSunAdd);
	}
}

void GameStateMgr::onExitState_WorldMap(GameState i_toState)
{
	if (i_toState != GAME_Almanac && i_toState != GAME_Store && i_toState != GAME_LevelUp && i_toState != GAME_PlantAvatar && i_toState != GAME_PVPMap && i_toState != GAME_ArtifactCultivation && i_toState != GAME_PlantGeneEnhancement)
		gLawnApp->StopMusic("Stop_Amb_WorldMap_Space_BG_LP");
	gLawnApp->KillCoinStore();
	gLawnApp->KillChooseActivityLevelsDialog();
	gLawnApp->KillChoosePlantsDialog();
	gLawnApp->KillActivityHome();
	gLawnApp->KillActivityHomeExtra();
	gLawnApp->GetWorldMap()->UnloadResources();
	gLawnApp->KillWorldMap();
	gLawnApp->KillGameMaskUI();
}

void GameStateMgr::onEnterState_MainMenu(GameState i_fromState)
{
	Sexy::PrimeText::Instance()->ClearGlyphCache();
	if (i_fromState != GAME_LogoScreen)
	{
		gLawnApp->LoadGroup("UI_MainMenu");
		gLawnApp->LoadGroup("MainMenu_Background");
		gLawnApp->LoadGroup("MainMenu_Background_Effect");
	}
	gLawnApp->LoadGroup("UI_Help");
	gLawnApp->ShowMainMenu();
	CheatManager::GetInstancePtr()->SetCurrentContext(CHEATCONTEXT_MainMenu);
}

void GameStateMgr::onEnterState_GenericGameState(GameState i_fromState)
{
	GameState state = m_stateMachine.GetState();
	m_activeGameState = m_genericStateTable[state]->New()->CastChecked<PVZGameState>();
	m_activeGameState->Enter();
	std::string musicEvent = m_activeGameState->GetMusicStartEvent();
	if (!musicEvent.empty())
		gLawnApp->PlayMusic(musicEvent.c_str());
	m_transitionController->SetCoveringLoad(true);
}

void GameStateMgr::onExitState_GenericGameState(GameState i_toState)
{
	std::string musicEvent = m_activeGameState->GetMusicStopEvent();
	if (!musicEvent.empty())
		gLawnApp->StopMusic(musicEvent.c_str());
	m_activeGameState->Exit();
	delete m_activeGameState;
	m_activeGameState = NULL;
}

void GameStateMgr::onEnterState_LogoScreen(GameState i_fromState)
{
	gLawnApp->PrepareLoadGroup("UI_MainMenu");
	gLawnApp->PrepareLoadGroup("MainMenu_Background");
	gLawnApp->PrepareLoadGroup("MainMenu_Background_Effect");
	gLawnApp->LoadGroup("StartupMusic");
	gLawnApp->ShowTitleScreen();
	gLawnApp->StartInitialLoad();
	gLawnApp->mLoadingThreadCompleted = true;
	m_loadedForFrameCount = 0;
	if (IdentifierMgr::GetInstance().EnableBind())
		IdentifierMgr::GetInstance().TryIdentifierCheck();
}

void GameStateMgr::onExitState_LogoScreen(GameState i_toState)
{
	gLawnApp->KillTitleScreen();
	if (i_toState != GAME_MainMenu)
	{
		if (m_playingOpeningMusic)
		{
			if (!m_openingMusicStopped)
			{
				gLawnApp->StopMusic("Stop_Music_Opening_Splash");
				m_openingMusicStopped = true;
			}
			gLawnApp->DeleteGroup("StartupMusic");
			m_playingOpeningMusic = false;
		}
		gLawnApp->DeleteGroup("UI_MainMenu");
		gLawnApp->DeleteGroup("MainMenu_Background");
		gLawnApp->DeleteGroup("MainMenu_Background_Effect");
	}
}

void GameStateMgr::onExitState_MainMenu(GameState i_toState)
{
	if (m_playingOpeningMusic)
	{
		if (!m_openingMusicStopped)
		{
			gLawnApp->StopMusic("Stop_Music_Opening_Splash");
			m_openingMusicStopped = true;
		}
		gLawnApp->DeleteGroup("StartupMusic");
		m_playingOpeningMusic = false;
	}
	gLawnApp->KillMainMenu();
	gLawnApp->DeleteGroup("UI_MainMenu");
	gLawnApp->DeleteGroup("UI_Help");
	gLawnApp->DeleteGroup("MainMenu_Background");
	gLawnApp->DeleteGroup("MainMenu_Background_Effect");
	PlantFamilyMgr::GetInstance().PlantFamilyReset();
}

void GameStateMgr::buildGenericStateTable()
{
	m_genericStateTable[GAME_JoustLoadDashboard] = JoustDashboardLoadingState::StaticGetClass();
	m_genericStateTable[GAME_JoustDashboardScreen] = JoustLandingScreenState::StaticGetClass();
	m_genericStateTable[GAME_JoustOrAdventureSelector] = JoustOrAdventureScreenState::StaticGetClass();
	m_genericStateTable[GAME_JoustTournamentEndScreen] = JoustTournamentEndScreenState::StaticGetClass();
	m_genericStateTable[GAME_RiftTournamentEndScreen] = RiftTournamentEndScreenState::StaticGetClass();
	m_genericStateTable[GAME_RichManScreen] = RichManScreenState::StaticGetClass();
	m_genericStateTable[GAME_RiftLoadDashboard] = RiftDashboardLoadingState::StaticGetClass();
	m_genericStateTable[GAME_PVZ1LoadDashboard] = PVZ1DashboardLoadingState::StaticGetClass();
	m_genericStateTable[GAME_NewPVPMainEntryScreen] = NewPVPMainEntryScreenState::StaticGetClass();
	m_genericStateTable[GAME_NewPlantUIEntryScreen] = NewPlantUIEntryScreenState::StaticGetClass();
}

void GameStateMgr::Initialize(GameState i_initialState)
{
	m_loadedForFrameCount = 0;
	m_playingOpeningMusic = false;
	m_openingMusicStopped = false;
	m_bHasCheckedUpdates = false;
	m_queuedWorldMapDestination = NULL;
	m_transitionController = new GameStateTransitionController;
	m_transitionController->SetGameStateMgr(this);
	m_queueWorldName = "";
	m_activeGameState = NULL;
	m_queuedActiveStarIndex = -1;
	gMessageRouter->Subscribe(Message::LevelLoadComplete, Sexy::MakeDelegate(*this, &GameStateMgr::onLevelLoaded));
	gMessageRouter->Subscribe(Message::WorldMapLoadComplete, Sexy::MakeDelegate(*this, &GameStateMgr::onWorldMapLoaded));
	gMessageRouter->Subscribe(Message::RiftNetworkResponseReceived, Sexy::MakeDelegate(*this, &GameStateMgr::onRiftNetworkResponse));
	gMessageRouter->Subscribe(Message::PVZ1ModeNetworkResponseReceived, Sexy::MakeDelegate(*this, &GameStateMgr::onPVZ1NetworkResponse));
	buildStateTable();
	buildGenericStateTable();
	setState(i_initialState);
}

void GameStateMgr::onEnterState_Game(GameState i_fromState)
{
	Sexy::PrimeText::Instance()->ClearGlyphCache();
	m_transitionController->SetCoveringLoad(true);
	gLawnApp->LoadGroup("LevelCommon");
	gLawnApp->LoadGroup("LevelCommon2");
	gLawnApp->LoadGroup("LevelImage");
	gLawnApp->LoadGroup("AudioCommon");
	gLawnApp->LoadGroup("Keys");
	gLawnApp->LoadGroup("PowerUpIcons");
	gLawnApp->ApplyNetworkContentChanges();
	if (m_queuedLevelFromSave)
	{
		m_saveStateResourceGroups.clear();
		SaveGameMgr::GetInstance().GetResourceGroupsRequiredForLoad(m_saveStateResourceGroups, false);
		SaveGameMgr::GetInstance().ClearSaveGame(false);
		gLawnApp->PrepareLoadGroups(m_saveStateResourceGroups);
	}
	else
	{
		gLawnApp->ShowBoard();
		gLawnApp->m_board->InitLevel(m_queuedLevel, getCurrentLevelIsHardMode());
		m_queuedLevel = "";
		m_queuedActiveStarIndex = -1;
		CheatManager::GetInstancePtr()->SetCurrentContext(CHEATCONTEXT_Board);
	}
}

void GameStateMgr::onExitState_Game(GameState i_toState)
{
	if (gLawnApp->m_board != NULL)
		gLawnApp->m_board->EndLevel();
	gLawnApp->KillBoard();
	gLawnApp->DeleteGroup("PowerUpIcons");
	gLawnApp->DeleteGroup("Keys");
	gLawnApp->DeleteGroup("AudioCommon");
	gLawnApp->DeleteGroup("LevelCommon");
	gLawnApp->DeleteGroup("LevelCommon2");
	gLawnApp->DeleteGroup("LevelImage");
}

void GameStateMgr::ReturnFromBoard()
{
	if (PVPManager::GetInstancePtr()->GetPVPMapType() == Map_PVPEntry)
	{
		TranslateTo(GAME_PVPEntry, GAMETRANSITION_QuickSpiral, GAMETRANSITION_QuickSpiral);
		gNetworkMgr->GetNewNetWorkProcess()->RequestPVPLogin();
	}
	else if (PVPManager::GetInstancePtr()->GetPVPMapType() == Map_PVPMap)
	{
		ShowPVPMap(GAMETRANSITION_None, GAMETRANSITION_None);
		if (!PVPManager::GetInstancePtr()->IsEvilDavidBattle())
			NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestPVPMapInfo();
	}
	else if (m_levelSource == LEVELSOURCE_Joust)
	{
		ShowJoustDashboardScreen();
	}
	else
	{
		if (m_returnFromBoardType == ReturnFromBoard_Default)
		{
			bool canShowMap = gLawnApp->HasPlayerUnlockedFeature(FEATURE_WORLDMAP);
			if (canShowMap && ProfileUtils::UnlockedWorldCount() > 0)
			{
				ShowWorldMap(GAMETRANSITION_QuickSpiral, GAMETRANSITION_QuickSpiral);
				return;
			}
			ShowMainMenu(GAMETRANSITION_QuickWhite, GAMETRANSITION_QuickWhite);
		}
		else
		{
			switch (m_returnFromBoardType)
			{
			case ReturnFromBoard_ShowTreasure:
				ShowStore("Gacha", GAMETRANSITION_QuickSpiral, GAMETRANSITION_QuickSpiral);
				break;
			case ReturnFromBoard_ShowPlantAdventure:
				ShowPlantAdventure(GAMETRANSITION_None, GAMETRANSITION_None);
				break;
			case ReturnFromBoard_ShowPlantUp:
				if (NewPlantUIMgr::GetInstancePtr()->IsNewUI())
					ShowNewPlantUIEntryScreen(GAMETRANSITION_QuickSpiral, GAMETRANSITION_QuickSpiral);
				else
					ShowLevelUp(GAMETRANSITION_QuickSpiral, GAMETRANSITION_QuickSpiral);
				break;
			}
			m_returnFromBoardType = ReturnFromBoard_Default;
		}
	}
}
/////////////// Accessors ///////////////

const MapEventItem* GameStateMgr::GetQueuedWorldMapDestination()
{
	return m_queuedWorldMapDestination;
}

const MapEventItem* GameStateMgr::GetAndClearQueuedWorldMapDestination()
{
	const MapEventItem* destination = m_queuedWorldMapDestination;
	m_queuedWorldMapDestination = NULL;
	return destination;
}

bool GameStateMgr::IsTransitioning() const
{
	return m_transitionController->IsTransitioning();
}

GameState GameStateMgr::GetState()
{
	return m_stateMachine.GetState();
}

void GameStateMgr::Draw(Graphics* i_g)
{
	m_transitionController->Draw(i_g);
}

void GameStateMgr::onLevelLoaded()
{
	m_transitionController->SetCoveringLoad(false);
}

void GameStateMgr::onWorldMapLoaded()
{
	m_transitionController->SetCoveringLoad(false);
}

/////////////// States ///////////////

void GameStateMgr::onEnterState_LevelUp(GameState i_fromState)
{
	gLawnApp->ShowPlantLevelUpListView();
}

void GameStateMgr::onEnterState_Lottery(GameState i_fromState)
{
	gLawnApp->ShowLotteryUI(true);
}

void GameStateMgr::onEnterState_CustomLevel(GameState i_fromState)
{
	gLawnApp->ShowCustomLevelView();
}

void GameStateMgr::onEnterState_PlantAvatar(GameState i_fromState)
{
	gLawnApp->ShowPlantAvatarListView();
}

void GameStateMgr::onEnterState_PlantFamily(GameState i_fromState)
{
	gLawnApp->ShowPlantFamilyUI(1);
}

void GameStateMgr::onEnterState_NostalgiaPVZ(GameState i_fromState)
{
	gLawnApp->ShowNostalgiaPVZGameView();
}

void GameStateMgr::onEnterState_ArtifactCultivation(GameState i_fromState)
{
	gLawnApp->ShowArtifactCultivationListView();
}

void GameStateMgr::onEnterState_PlantGeneEnhancement(GameState i_fromState)
{
	gLawnApp->ShowPlantGeneEnhancementView();
}

void GameStateMgr::onExitState_LevelUp(GameState i_toState)
{
	gLawnApp->KillPlantLevelUpListView();
}

void GameStateMgr::onExitState_Lottery(GameState i_toState)
{
	gLawnApp->KillLotteryUI();
}

void GameStateMgr::onExitState_CustomLevel(GameState i_toState)
{
	gLawnApp->KillCustomLevelView();
}

void GameStateMgr::onExitState_PlantAvatar(GameState i_toState)
{
	gLawnApp->KillPlantAvatarListView();
}

void GameStateMgr::onExitState_PlantFamily(GameState i_toState)
{
	gLawnApp->KillPlantFamilyUI();
}

void GameStateMgr::onExitState_NostalgiaPVZ(GameState i_toState)
{
	gLawnApp->KillNostalgiaPVZGameView();
}

void GameStateMgr::onExitState_PlantAdventure(GameState i_toState)
{
	gLawnApp->KillPlantAdventureUI();
}

void GameStateMgr::onExitState_ArtifactCultivation(GameState i_toState)
{
	gLawnApp->KillArtifactCultivationListView();
}

void GameStateMgr::onExitState_PlantGeneEnhancement(GameState i_toState)
{
	gLawnApp->KillPlantGeneEnhancementView();
}

void GameStateMgr::onEnterState_PVPLab(GameState i_fromState)
{
	PVPLabDlg::ShowDialog();
}

void GameStateMgr::onExitState_PVPLab(GameState i_toState)
{
	PVPLabDlg::CloseDialog();
}

/////////////// Empty states ///////////////

void GameStateMgr::onEnterState_DangerRoom(GameState i_fromState)
{
}

void GameStateMgr::onEnterState_Initializing(GameState i_fromState)
{
}

void GameStateMgr::onEnterState_WaitForNetworkLoad(GameState i_fromState)
{
}

void GameStateMgr::onExitState_DangerRoom(GameState i_toState)
{
}

void GameStateMgr::onExitState_DangerRoomSkipLevel(GameState i_toState)
{
}

void GameStateMgr::onExitState_DirtyAccount(GameState i_toState)
{
}

void GameStateMgr::onExitState_Initializing(GameState i_toState)
{
}

void GameStateMgr::onExitState_WaitForNetworkLoad(GameState i_toState)
{
}

void GameStateMgr::updateState_5thCenter()
{
}

void GameStateMgr::updateState_ActiveCenter()
{
}

void GameStateMgr::updateState_Almanac()
{
}

void GameStateMgr::updateState_ArtifactCultivation()
{
}

void GameStateMgr::updateState_Consumption()
{
}

void GameStateMgr::updateState_CustomLevel()
{
}

void GameStateMgr::updateState_DailyAchievement()
{
}

void GameStateMgr::updateState_DangerRoom()
{
}

void GameStateMgr::updateState_DangerRoomSkipLevel()
{
}

void GameStateMgr::updateState_DirtyAccount()
{
}

void GameStateMgr::updateState_FestivalCenter()
{
}

void GameStateMgr::updateState_Lantern()
{
}

void GameStateMgr::updateState_LevelUp()
{
}

void GameStateMgr::updateState_Lottery()
{
}

void GameStateMgr::updateState_NostalgiaPVZ()
{
}

void GameStateMgr::updateState_PVPEntry()
{
}

void GameStateMgr::updateState_PVPLab()
{
}

void GameStateMgr::updateState_PVPMap()
{
}

void GameStateMgr::updateState_PlantAdventure()
{
}

void GameStateMgr::updateState_PlantAvatar()
{
}

void GameStateMgr::updateState_PlantFamily()
{
}

void GameStateMgr::updateState_PlantGeneEnhancement()
{
}

void GameStateMgr::updateState_PlantTrial()
{
}

void GameStateMgr::updateState_RechargeWelfare()
{
}

void GameStateMgr::updateState_RedPack()
{
}

void GameStateMgr::updateState_Store()
{
}

void GameStateMgr::updateState_WorldMap()
{
}
