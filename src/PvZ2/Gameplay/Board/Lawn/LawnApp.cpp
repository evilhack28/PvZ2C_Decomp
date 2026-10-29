//
//  LawnApp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/IDiagDriver.h"
#include "LawnApp.h"
#include "LuaCUIDialog.h"
#include "PVZLiveConfig.h"
#include "AutoTest.h"
#include "PlantDefenceEntrance.h"
#include "Social/Widgets/DailySignReward.h"
#include "Social/Widgets/LoginReward.h"
#include "AudioMgr.h"
#include "Board.h"
#include "LostNetActivityUI.h"
#include "Plant_Cobcannon.h"
#include "ChildrenDayUI.h"
#include "LogCollector.h"
#include "PVZ2UIDialog.h"
#include "ProbabilityDLG.h"
#include "AdventureTeamEditorUI.h"
#include "AlmanacWidget.h"
#include "ArenaAwakenWidget.h"
#include "ArenaEndingUI.h"
#include "ArtifactCultivationListView.h"
#include "BattleStatementUI.h"
#include "BirthdayRewardDialog.h"
#include "BoardZombieAlmanacUI.h"
#include "BoxOpenUI.h"
#include "BuyItemUI.h"
#include "PlantHeadshot.h"
#include "ChristmasGoldenEgg.h"
#include "ChristmasLotteryReward.h"
#include "ConsumptionRewardDialog.h"
#include "CustomLevelMainMenu.h"
#include "DailyAchievement.h"
#include "DaveClubUI.h"
#include "EndLevelUI.h"
#include "FestivalEntranceUI.h"
#include "GachaItemDisplayer.h"
#include "GachaUI.h"
#include "GameMaskUI.h"
#include "GetGemsRestoreUI.h"
#include "GetNewerBagUI.h"
#include "GetPlantBagUI.h"
#include "LanternRiddlesUI.h"
#include "LevelOfDayEntrance.h"
#include "LevelOfTheDayRewardDialog.h"
#include "LevelOfTheDay_ProgressiveAwardDialog.h"
#include "LotteryUI.h"
#include "MainMenu.h"
#include "NetConnectingUI.h"
#include "NewerPresentUI.h"
#include "NostalgiaPVZGameView.h"
#include "PVP/PVpCoinStore.h"
#include "PVP/PVPBaseUpgrade.h"
#include "TransitionOverlayWidget.h"
#include "ServerConfig.h"
#include "PVP/PVPSkillUpgrade.h"
#include "PVPMapUI.h"
#include "PVPZombieLevelUpDlg.h"
#include "PVZ2UIBuyAvatarDialog.h"
#include "PVZ2UIBuyGachaDialog.h"
#include "PVZ2UIBuyGiftDialog.h"
#include "PVZ2UIBuyPlantDialog.h"
#include "PVZ2UILotteryResult.h"
#include "PVZ2UIStarLevelUp.h"
#include "PVZ2UIUnlockPreview.h"
#include "PlantAccessoryUI.h"
#include "PlantAdventureUI.h"
#include "PlantAvatarListView.h"
#include "PlantGeneEnhancementView.h"
#include "PlantLevelUpListView.h"
#include "PlantTrialViewUI.h"
#include "PowerPKWidget.h"
#include "RechargeGiftUI.h"
#include "RedPackOpenUI.h"
#include "RedPackUI.h"
#include "RedeemRewardUI.h"
#include "RewardUI.h"
#include "SkycityBossWarningInfo.h"
#include "Social/Widgets/BoxOpenUI.h"
#include "Social/Widgets/LotteryUI.h"
#include "StarConvert.h"
#include "StarLevelChallengeUI.h"
#include "StoreUI.h"
#include "TitleScreen.h"
#include "TransGenosisUI.h"
#include "CrazyNPCManager.h"
#include "PostProcessOverlayWidget.h"
#include "BusyAnimationManager.h"
#include "UIActivityCollection.h"
#include "UINewPlayerCollection.h"
#include "UniverseWorldInfo.h"
#include "Widget.h"
#include "WorldMap.h"
#include "WorldMapActivityHome.h"
#include "WorldMapActivityHomeExtra.h"
#include "WorldMapChallengeChooseDialog.h"
#include "WorldMapChooseDialog.h"
#include "WorldMapDailyActivityChooseDialog.h"
#include "WorldMapShopChooseDialog.h"
#include "WorldMapWelfareChooseDialog.h"
#include "WorldMap_MarqueeView.h"
#include "WorldMap_ScrollBannerButton.h"
#include "ActiveEntranceUI.h"
#include "CollectableAdUI.h"
#include "DailySignActivity.h"
#include "DangerRoomSpecialOffer.h"
#include "GeilivableLottery.h"
#include "GemOfferMgr.h"
#include "NDDailyAwardUI.h"
#include "NewOptionsDialog.h"
#include "OppoNewerEventUI.h"
#include "PlantBundleUI.h"
#include "PlantSpecialOffer.h"
#include "RecallOfferUI.h"
#include "RechargeRewardUI.h"
#include "ReviveUI.h"
#include "SalesUI.h"
#include "StoneLottery.h"
#include "TwoYearBirthday.h"
#include "UISpringFestivalActivity.h"
#include "ActivityManager.h"
#include "CheatUI.h"
#include "iosExtras.h"
#include "DangerRoomManager.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"
#include "gameNetWork/androidNetworkMsgProcess.h"
#include "FakeHttpDriver.h"
#include "UIPlantFamily.h"
#include "Social/Widgets/DailySignRewardWithTW.h"
#include "CodeRewardUI.h"
#include "SaveGameMgr.h"
#include "gameNetWork/ServerTime.h"
#include "gameNetWork/ServerTimeHandler.h"
#include "HintUI.h"
#include "PVP/PVPManager.h"
#include "WorldMapActionManager.h"
#include "WorldMapActivityBtnTurnChangeManager.h"
#include "GameCenterProxy.h"
#include "MetricsCollector.h"
#include "Social/SocialMgr.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "TutorialEffectMgr.h"
#include "PVZ1ModeUtils.h"
#include "iCloud/ProfileSummaryComparer.h"
#include "AdaptorJoustLeagueInfoScreen.h"
#include "SummerEventEntranceUI.h"
#include "TimeTravelEntranceUI.h"
#include "CollectableAdBoxMgr.h"
#include "AbtestMgr.h"
#include "IdentifierMgr.h"
#include "AuthMgr.h"
#include "SocialShareMgr.h"
#include "NewPVPGame.h"
#include "AdsRewardUI.h"

namespace RiftUtils { bool IsPlayingRiftLevel(); bool IsRiftTimedLevel(); }

namespace Lua
{
class CLuaEngine : public Sexy::LazySingleton<CLuaEngine>
{
public:
	char m_pad[0xe51];
	bool m_disabled;
	bool IsDisabled() { return m_disabled; }
	void ExecuteTableFunction(const char* i_table, const char* i_function);
	void Update();
};
}

namespace Sexy
{
template<> Lua::CLuaEngine& LazySingleton<Lua::CLuaEngine>::GetInstance();
}

static std::vector<CheckRsbInfo> sExtraRsbs = {
	{"plant2.rsb", "properties\resourcesPlant2.rton"},
	{"plant3.rsb", "properties\resourcesPlant3.rton"},
	{"zombie2.rsb", "properties\resourcesZombie2.rton"},
	{"zombie3.rsb", "properties\resourcesZombie3.rton"},
	{"pirate.rsb", "properties\resourcesPirate.rton"},
	{"cowboy.rsb", "properties\resourcesCowboy.rton"},
	{"kongfu.rsb", "properties\resourcesKongfu.rton"},
	{"future.rsb", "properties\resourcesFuture.rton"},
	{"dark.rsb", "properties\resourcesDark.rton"},
	{"beach.rsb", "properties\resourcesBeach.rton"},
	{"iceage.rsb", "properties\resourcesIceage.rton"},
	{"skycity.rsb", "properties\resourcesSkycity.rton"},
	{"lostcity.rsb", "properties\resourcesLostcity.rton"},
	{"eighties.rsb", "properties\resourcesEighties.rton"},
	{"dino.rsb", "properties\resourcesDino.rton"},
	{"modern.rsb", "properties\resourcesModern.rton"},
	{"steam.rsb", "properties\resourcesSteam.rton"},
	{"renai.rsb", "properties\resourcesRenai.rton"},
	{"heian.rsb", "properties\resourcesHeian.rton"}
};

static std::string sMapNames[16] = {"egypt", "pirate", "cowboy", "kongfu", "future", "eighties", "dark", "beach", "dino", "iceage", "lostcity", "skycity", "modern", "steam", "renai", "heian"};
static std::string sForbiddenPackages[85] = {
	"com.popcap.pvz2cukd",
	"com.popcap.pvz2qq",
	"com.popcap.pvz2bdyx",
	"com.popcap.pvz2bdaqy",
	"com.popcap.pvz2xl",
	"com.popcap.pvz2mmy",
	"com.popcap.pvz2js",
	"com.popcap.pvz2mt",
	"com.popcap.pvz2zx",
	"com.popcap.pvz2cw",
	"com.popcap.pvz2HWCM",
	"com.popcap.pvz27k",
	"com.popcap.pvz2sn",
	"com.popcap.pvz2bk",
	"com.popcap.pvz2lwy",
	"com.popcap.pvz2kpct",
	"com.popcap.pvz2lxct",
	"com.popcap.pvz2hwct",
	"com.popcap.pvz2zxct",
	"com.popcap.pvz2zxyxct",
	"com.popcap.pvz2sh",
	"com.popcap.pvz2pps",
	"com.popcap.pvz2aqypc",
	"com.popcap.pvz2nd",
	"com.popcap.pvz2ttdt",
	"com.popcap.pvz2tyd",
	"com.popcap.pvz2hzmp",
	"com.popcap.pvz2xchdmp",
	"com.popcap.pvz2kpsj",
	"com.popcap.pvz2cthdyyt",
	"com.popcap.pvz2cukdhd",
	"com.popcap.pvz2mmschd",
	"com.popcap.pvz2qqhd",
	"com.popcap.pvz2cthdbdyx",
	"com.popcap.pvz2cthdbdaqy",
	"com.popcap.pvz2cthdxl",
	"com.popcap.pvz2cthdmpt",
	"com.popcap.pvz2cthdjs",
	"com.popcap.pvz2cthdmt",
	"com.popcap.pvz2cthdzx",
	"com.popcap.pvz2cthdcw",
	"com.popcap.pvz2cthdsn",
	"com.popcap.pvz2cthdlwy",
	"com.popcap.pvz2cthdayyct",
	"com.popcap.pvz2cthdahytct",
	"com.popcap.pvz2cthdkpct",
	"com.popcap.pvz2cthdlxct",
	"com.popcap.pvz2cthdzxct",
	"com.popcap.pvz2cthdzxyxct",
	"com.popcap.pvz2cthdszryct",
	"com.popcap.pvz2cthdgdgx",
	"com.popcap.pvz2cthdscsf",
	"com.popcap.pvz2cthdwhcw",
	"com.popcap.pvz2cthdgzdx",
	"com.popcap.pvz2cthdwdsy",
	"com.popcap.pvz2cthdszkyct",
	"com.popcap.pvz2cthdsh",
	"com.popcap.pvz2cthdpps",
	"com.popcap.pvz2cthdaqypc",
	"com.popcap.pvz2cthdnd",
	"com.popcap.pvz2cthdttdt",
	"com.popcap.pvz2cthdhzmp",
	"com.popcap.pvz2cthdhlg",
	"com.popcap.pvz2cthdzm",
	"com.popcap.pvz2cthdxchdmp",
	"com.popcap.pvz2cthdPVZ2Prototype",
	"com.popcap.pvz2cthdjj",
	"com.popcap.pvz2cthdppzs",
	"com.popcap.pvz2cthdqxz",
	"com.popcap.pvz2cthdshumazy",
	"com.popcap.pvz2cthdwanka",
	"com.popcap.pvz2cthdwrsj",
	"com.popcap.pvz2cthddev",
	"com.popcap.pvz2cthdxyaz",
	"com.popcap.pvz2cthddianyou",
	"com.popcap.pvz2cthdxly",
	"com.popcap.pvz2cthdxiaoqi",
	"com.popcap.pvz2cthdylehihi",
	"com.popcap.pvz2cthdhaoyoukb",
	"com.popcap.pvz2cthdtw",
	"com.popcap.pvz2cthdhbili",
	"com.popcap.pvz2cthd.bytedance.gamecenter",
	"com.popcap.pvz2cugd",
	"com.popcap.pvz2cthdcugd",
	"com.popcap.pvz2cugd"
};


bool LawnApp::IsAppTopLevel()
{
	return true;
}

__attribute__((noclone, noinline)) static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

bool LawnApp::NeedDelayLoadRSB()
{
	std::vector<CheckRsbInfo>::iterator it = sExtraRsbs.begin();
	std::vector<CheckRsbInfo>::iterator end = sExtraRsbs.end();
	for (; it != end; ++it)
	{
		CheckRsbInfo& info = *it;
		if (!gLawnApp->mResStreamsManager->NeedDecompressRsb(info.RsbName, std::string(""), std::string("")))
			return false;
	}
	return true;
}

bool LawnApp::NeedDecompressRsbsExtra()
{
	std::vector<CheckRsbInfo>::iterator it = sExtraRsbs.begin();
	std::vector<CheckRsbInfo>::iterator end = sExtraRsbs.end();
	for (; it != end; ++it)
	{
		CheckRsbInfo& info = *it;
		if (gLawnApp->mResStreamsManager->NeedDecompressRsb(info.RsbName, std::string(""), std::string("")))
			return true;
	}
	return false;
}

bool LawnApp::DeviceNeeds50MBResolutionChange()
{
	std::string model = gSexyAppBase->mDiagDriver->GetInfoStringSafe(IDiagDriver::INFO_HardwareModel);
	return model.find("iPod4") != std::string::npos || IsDeviceIOS();
}

void LawnApp::LoadRsbsExtraProc()
{
	for (std::vector<CheckRsbInfo>::const_iterator it = sExtraRsbs.begin(); it != sExtraRsbs.end(); ++it)
	{
		CheckRsbInfo& info = const_cast<CheckRsbInfo&>(*it);
		Sexy::OutputDebugStrF("LawnApp::LoadRsbsExtraProc() start load rsb %s", info.RsbName.c_str());
		gSexyAppBase->mResourceManager->Init(1200, (int)gLawnApp->m_contentResolutionHeight, info.RsbName, info.RsbConfigName, true);
		Sexy::OutputDebugStrF("LawnApp::LoadRsbsExtraProc() end load rsb %s", info.RsbName.c_str());
	}
}

void LawnApp::ShowPvpCoinStore()
{
	UIMessageBox* box = UISingletonDialog<UIMessageBox>::ShowDialog();
	if (box)
	{
		box->SetShowType(UIMessageBox::Type_ShowCancel);
		SexyString title = TodStringTranslate(L"[REVIVE_TIP]");
		SexyString message = TodStringTranslate(L"[PVP_STORE_CLOSE]");
		SexyString ok = TodStringTranslate(L"[BUTTON_OK]");
		box->SetMessage(message, title);
		box->SetBackground(StringHelper::ToImage("IMAGE_UI_DIALOG_ASSET_BG_LIGHT_GREEN", false));
		box->GetButtonCancel()->mLabel = ok;
	}
}

void LawnApp::ShowPvpCoinBuyConfirm()
{
	UIMessageBox* box = UISingletonDialog<UIMessageBox>::ShowDialog();
	if (box)
	{
		box->SetMessage(TodStringTranslate(L"[PVP_COIN_LACK_TIP]"), TodStringTranslate(L"[PVP_COIN_LACK_TITLE]"));
		box->SetShowType(UIMessageBox::Type_ShowOK | UIMessageBox::Type_ShowCancel);
		box->SetBackground("IMAGE_UI_DIALOG_ASSET_BG_LIGHT_PURPLE");
		box->SetBackgroundDarken(true, 0.5f);
		box->SetCallback(Sexy::MakeDelegate(*this, &LawnApp::OnPvpCoinBuyButtonUp));
	}
}

void LawnApp::ShowPlantAvatarPackageView(MagentoProductPropsPtr i_props)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	if (!m_plantAvatarPackageView)
		m_plantAvatarPackageView = new PlantAvatarPackageView(i_props);
	mWidgetManager->AddWidget(m_plantAvatarPackageView);
	mWidgetManager->BringToFront(m_plantAvatarPackageView);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_plantAvatarPackageView);
	mWidgetManager->SetFocus(m_plantAvatarPackageView);
	m_plantAvatarPackageView->ShowGachaIntro2Mask();
}

void LawnApp::ShowPlantRewardDialog(PlantTypePtr i_awardedPlant, bool i_starReward, int i_starNum, bool i_isToPiece, bool i_view)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(::UIScaleNum(572), ::UIScaleNum(373));
	PVZ2UIRewardObjectDisplayer* displayer = new PVZ2UIRewardObjectDisplayer(i_awardedPlant, i_starReward, i_starNum, E_AVATAR_NONE, i_isToPiece, i_view);
	dialog->SetContents(displayer);
	if (!i_view)
		dialog->AddButton(L"[CONTINUE_BUTTON]", Sexy::Delegate0(Sexy::MakeDelegate(*this, &LawnApp::KillPlantRewardDialog)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
	dialog->SetBackgroundDarken(true, 0.7f);
}

void LawnApp::ShowAccessoryAwardDialog(Image* i_qualityImg, Image* i_displayImg, SexyString i_name, SexyString i_description, SexyString i_boostDescription)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(::UIScaleNum(572), ::UIScaleNum(373));
	PVZ2UIAccessoryObjectDisplayer* displayer = new PVZ2UIAccessoryObjectDisplayer(i_qualityImg, i_displayImg, i_name, i_description, i_boostDescription);
	dialog->SetContents(displayer);
	dialog->AddButton(L"[CONTINUE_BUTTON]", Sexy::Delegate0(Sexy::MakeDelegate(*this, &LawnApp::KillAccessoryAwardDialog)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
	dialog->SetBackgroundDarken(true, 0.7f);
}

void LawnApp::ShowAvatarRewardDialog(PlantTypePtr i_awardedPlant, const std::string& title, const std::string& desc, bool i_starReward, int i_starNum, PlantAvatarType eAvatar, int avatarIndex)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(::UIScaleNum(572), ::UIScaleNum(373));
	PVZ2UIRewardAvatarObjectDisplayer* displayer = new PVZ2UIRewardAvatarObjectDisplayer(i_awardedPlant, title, desc, i_starReward, i_starNum, eAvatar);
	if (avatarIndex >= 0)
		displayer->SetAvatarIndex(avatarIndex);
	dialog->SetContents(displayer);
	dialog->AddButton(L"[CONTINUE_BUTTON]", Sexy::Delegate0(Sexy::MakeDelegate(*this, &LawnApp::KillPlantRewardDialog)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
	dialog->SetBackgroundDarken(true, 0.5f);
}

void LawnApp::ShowStarConvert()
{
	if (!m_starConvert)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_starConvert = new StarConvert();
		m_isStarConvertOpened = true;
		mWidgetManager->AddWidget(m_starConvert);
	}
	mWidgetManager->BringToFront(m_starConvert);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_starConvert);
	mWidgetManager->SetFocus(m_starConvert);
	gMessageRouter->Post(&Message::OpenUI, "StarConvert");
	m_starConvert->NormalInit(PT_FromLeft | PT_FromDown | PT_Fade);
	m_starConvert->StartPop();
}

void LawnApp::ShowCBTutorialUI()
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if (profile)
	{
		if (profile->GetActiveTutorial() == TUTORIAL_COBCANNON)
			profile->CompleteTutorial(TUTORIAL_COBCANNON);
		if (!m_cbTutorialUI)
		{
			AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
			m_cbTutorialUI = new CBTutorialUI();
			mWidgetManager->AddWidget(m_cbTutorialUI);
		}
		mWidgetManager->BringToFront(m_cbTutorialUI);
		PushOverlaysToTop();
		mWidgetManager->AddBaseModal(m_cbTutorialUI);
		mWidgetManager->SetFocus(m_cbTutorialUI);
		if (m_cbTutorialUI)
		{
			m_cbTutorialUI->InitView();
			m_cbTutorialUI->NormalInit(PT_FromCenter | PT_FromMiddle | PT_Scaled | PT_Fade, 0.2f);
			m_cbTutorialUI->StartPop();
		}
	}
}

void LawnApp::ShowBuyPlantDialog(MagentoProductPropsPtr i_props, bool i_quick)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	if (!m_buyPlantDialog)
		m_buyPlantDialog = new PVZ2UIBuyPlantDialog(i_props, i_quick);
	mWidgetManager->AddWidget(m_buyPlantDialog);
	mWidgetManager->BringToFront(m_buyPlantDialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_buyPlantDialog);
	mWidgetManager->SetFocus(m_buyPlantDialog);
}

void LawnApp::ShowBuyAvatarDialog(MagentoProductPropsPtr i_props, bool i_quick)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	if (!m_buyAvatarDialog)
		m_buyAvatarDialog = new PVZ2UIBuyAvatarDialog(i_props, i_quick);
	mWidgetManager->AddWidget(m_buyAvatarDialog);
	mWidgetManager->BringToFront(m_buyAvatarDialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_buyAvatarDialog);
	mWidgetManager->SetFocus(m_buyAvatarDialog);
}

void LawnApp::ShowBuyGachaDialog(MagentoProductPropsPtr i_props, bool i_quick)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	if (!m_buyGachaDialog)
		m_buyGachaDialog = new PVZ2UIBuyGachaDialog(i_props, i_quick);
	mWidgetManager->AddWidget(m_buyGachaDialog);
	mWidgetManager->BringToFront(m_buyGachaDialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_buyGachaDialog);
	mWidgetManager->SetFocus(m_buyGachaDialog);
}

void LawnApp::ShowBuyGiftDialog(MagentoProductPropsPtr i_props, bool i_quick)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	if (!m_buyGiftDialog)
		m_buyGiftDialog = new PVZ2UIBuyGiftDialog(i_props, i_quick);
	mWidgetManager->AddWidget(m_buyGiftDialog);
	mWidgetManager->BringToFront(m_buyGiftDialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_buyGiftDialog);
	mWidgetManager->SetFocus(m_buyGiftDialog);
}

void LawnApp::ShowPlantAvatarInfoDialog(MagentoProductPropsPtr i_props, bool i_showNotice)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	if (!m_plantAvatarInfoDialog)
		m_plantAvatarInfoDialog = new PlantAvatarInfoDialog(i_props, i_showNotice);
	mWidgetManager->AddWidget(m_plantAvatarInfoDialog);
	mWidgetManager->BringToFront(m_plantAvatarInfoDialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_plantAvatarInfoDialog);
	mWidgetManager->SetFocus(m_plantAvatarInfoDialog);
}

PVZ2UIDialog* LawnApp::ShowPVZ2Dialog(float i_dialogWidth, float i_dialogHeight, PVZ2UIDialog* i_dialogToUse)
{
	if (m_dialog && !m_dialog->GetAlwaysExist())
		KillPVZ2Dialog();
	if (!i_dialogToUse)
	{
		i_dialogToUse = new PVZ2UIDialog();
		m_dialog = i_dialogToUse;
	}
	else
		m_dialog = i_dialogToUse;
	m_dialog->Resize((int)((mScreenBounds.mWidth - i_dialogWidth) * 0.5f), (int)((mScreenBounds.mHeight - i_dialogHeight) * 0.5f), (int)i_dialogWidth, (int)i_dialogHeight);
	if (m_dataErrorDialog)
		return m_dialog;
	mWidgetManager->AddWidget(m_dialog);
	mWidgetManager->BringToFront(m_dialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_dialog);
	mWidgetManager->SetFocus(m_dialog);
	return m_dialog;
}

PVZ2WaitingDialog* LawnApp::ShowWaitingDialog(const SexyString& i_headLabel, int i_waitTime)
{
	if (m_waitingdialog)
		KillWaitingDialog();
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	int height = ::UIScaleNum(400);
	int width = ::UIScaleNum(500);
	m_waitingdialog = new PVZ2WaitingDialog(i_headLabel, i_waitTime);
	m_waitingdialog->Resize((mScreenBounds.mWidth - width) / 2, (mScreenBounds.mHeight - height) / 2, width, height);
	mWidgetManager->AddWidget(m_waitingdialog);
	mWidgetManager->BringToFront(m_waitingdialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_waitingdialog);
	mWidgetManager->SetFocus(m_waitingdialog);
	return m_waitingdialog;
}

PVZ2WaitingDialog* LawnApp::ShowWaitingDialog(const SexyString& i_headLabel, int i_waitTime, int i_height, int i_width)
{
	if (m_waitingdialog)
		KillWaitingDialog();
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	int height = ::UIScaleNum(i_height);
	int width = ::UIScaleNum(i_width);
	m_waitingdialog = new PVZ2WaitingDialog(i_headLabel, i_waitTime);
	m_waitingdialog->Resize((mScreenBounds.mWidth - width) / 2, (mScreenBounds.mHeight - height) / 2, width, height);
	mWidgetManager->AddWidget(m_waitingdialog);
	mWidgetManager->BringToFront(m_waitingdialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_waitingdialog);
	mWidgetManager->SetFocus(m_waitingdialog);
	return m_waitingdialog;
}

void LawnApp::ShareWeChatNewWorld()
{
	ShowShareDialog(L"WORLD");
	Sexy::LazySingleton<SocialMgr>::GetInstance().m_cacheShareInfo.shareTitle = Sexy::WStringToUTF8String(TodStringTranslate(L"[SHARE_UNLOCK_NEW_WORLD]"));
	Sexy::LazySingleton<SocialMgr>::GetInstance().m_cacheShareInfo.shareDesc = Sexy::WStringToUTF8String(TodStringTranslate(L"[SHARE_UNLOCK_NEW_WORLD]"));
	Sexy::LazySingleton<SocialMgr>::GetInstance().m_cacheShareInfo.shareUrl = "http://www.qq.com";
	Sexy::LazySingleton<SocialMgr>::GetInstance().m_cacheShareInfo.shareImageUrl = "http://mat1.gtimg.com/www/images/qq2012/qqlogo_1x.png";
}

void LawnApp::ShowPlantLevelUpListView()
{
	if (!m_plantLevelUpListView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_plantLevelUpListView = new PlantLevelUpListView("", false);
		mWidgetManager->AddWidget(m_plantLevelUpListView);
	}
	mWidgetManager->BringToFront(m_plantLevelUpListView);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_plantLevelUpListView);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	gMessageRouter->Post(&Message::AutoTestPlantUIShow);
}

void LawnApp::ShowPlantStarLevelUpAnimUI(PVZ2UIStarLevelUp::AnimaType eType, std::string i_name, int i_level)
{
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	if (!m_plantStarLevelUpAnimUI)
	{
		m_plantStarLevelUpAnimUI = new PVZ2UIStarLevelUp(mWidth, mHeight);
		m_plantStarLevelUpAnimUI->InitUIView(eType, i_name, i_level);
	}
	mWidgetManager->AddWidget(m_plantStarLevelUpAnimUI);
	mWidgetManager->BringToFront(m_plantStarLevelUpAnimUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_plantStarLevelUpAnimUI);
	mWidgetManager->SetFocus(m_plantStarLevelUpAnimUI);
}

void LawnApp::ShowAdventureTeamEditorUI(WorldDungeonInfo i_dungeonInfo)
{
	if (!m_TeamEditorUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_TeamEditorUI = new AdventureTeamEditorUI(i_dungeonInfo);
		mWidgetManager->AddWidget(m_TeamEditorUI);
	}
	mWidgetManager->BringToFront(m_TeamEditorUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_TeamEditorUI);
	mWidgetManager->SetFocus(m_TeamEditorUI);
	m_TeamEditorUI->TriggerTutorial();
	gMessageRouter->Post(&Message::OpenUI, "AdventureTeamEditorUI");
}

bool LawnApp::SetWidthHeight(int inNewHeight)
{
	int oldWidth = mWidth;
	int oldHeight = mHeight;
	Sexy::Point size = GetNativeScreenSize();
	mHeight = inNewHeight;
	m_contentResolutionHeight = (float)inNewHeight;
	m_contentResolutionWidth = (float)inNewHeight * (4.0f / 3.0f);
	mWidth = (int)((float)inNewHeight / (float)size.mY * (float)size.mX);
	Sexy::OutputDebugStrF(" LawnApp::SetWidthHeight mOrigScreenWidth = %d mOrigScreenHeight = %d", mOrigScreenWidth, mOrigScreenHeight);
	Sexy::OutputDebugStrF(" LawnApp::SetWidthHeight mWidth = %d mHeight = %d", mWidth, mHeight);
	Sexy::OutputDebugStrF(" LawnApp::SetWidthHeight m_contentResolutionWidth = %f m_contentResolutionHeight = %f", m_contentResolutionWidth, m_contentResolutionHeight);
	if (mWidth == oldWidth && mHeight == oldHeight)
		return false;
	SetResolution((int)m_contentResolutionHeight);
	SetUIResolution(mHeight);
	extern int gAppHeight;
	gAppHeight = mHeight;
	return true;
}

bool LawnApp::OpenURL(const std::string& theURL, bool shutdownOnOpen)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_PopUp_General");
	DoDialog(0, true, L"[OPENING_BROWSER]", L"[OPENING_BROWSER]", L"", 0);
	return SexyAppBase::OpenURL(theURL, shutdownOnOpen);
}

void LawnApp::ChooseProfile(bool i_cloudOlder)
{
	if (gLawnApp->canDealProfile())
	{
		setProfileOpened(false);
		if (i_cloudOlder)
		{
			Sexy::LazySingleton<ProfileMgr>::GetInstance().Save(true, true);
			setSyncProfileSuccess(true);
		}
		else
		{
			if (!Sexy::LazySingleton<ProfileMgr>::GetInstance().SyncProfileFromServer())
				gLawnApp->CheckNetWork(L"[NETWORK_NOT_CONNECTED_TITLE]", L"[NETWORK_NOT_CONNECTED_TEXT_FOR_SYNC_PLAYERINFO]");
			else
				setSyncProfileSuccess(true);
		}
		m_selfSync = true;
	}
}

void LawnApp::URLOpenFailed(const std::string& theURL)
{
	SexyAppBase::URLOpenFailed(theURL);
	KillDialog(0);
	CopyToClipboard(theURL);
	SexyString message = Sexy::StrFormat(L"[OPEN_URL %ls]", Sexy::UTF8StringToWString(theURL).c_str());
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_PopUp_General");
	DoDialog(0, true, L"[OPEN_BROWSER]", message, L"[DIALOG_STRING_OK]", 3);
}

void LawnApp::ShowMessageDialog(const std::string& title, const std::string& detail, const Delegate0& delegate)
{
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(::UIScaleNum(400), ::UIScaleNum(250));
	dialog->SetHeaderLabel(Sexy::StringToWString(title));
	dialog->SetFooterLabel(Sexy::StringToWString(detail));
	dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
	dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
	dialog->AddButton(SexyString(L"[BUTTON_OK]"), delegate, PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
}

void LawnApp::ShowMessageDialogWithOKButton(const std::string& title, const std::string& detail, const Delegate0& delegate)
{
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(::UIScaleNum(400), ::UIScaleNum(250));
	dialog->SetHeaderLabel(Sexy::StringToWString(title));
	dialog->SetFooterLabel(Sexy::StringToWString(detail));
	dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
	dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
	dialog->AddButton(SexyString(L"[BUTTON_OK]"), delegate, PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
	dialog->AddButton(SexyString(L"[BUTTON_CANCEL]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &LawnApp::KillPVZ2Dialog)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
}

void LawnApp::ShowMessageDialogNoCallback(const std::string& title, const std::string& detail)
{
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(::UIScaleNum(400), ::UIScaleNum(250));
	dialog->SetHeaderLabel(Sexy::StringToWString(title));
	dialog->SetFooterLabel(Sexy::StringToWString(detail));
	dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
	dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
	dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &LawnApp::KillPVZ2Dialog)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
}

void LawnApp::OnFinishedInitDangerRoom(bool i_success)
{
	if (i_success)
		gGameStateMgr->ShowWorldMap(GAMETRANSITION_QuickSpiral, GAMETRANSITION_QuickSpiral);
	else
	{
		PVZ2UIDialog* dialog = ShowPVZ2Dialog(L"[NOT_IN_ACTIVITY_TITLE]", L"[NOT_IN_ACTIVITY_TEXT]");
		dialog->AddButton(L"[BUTTON_OK]", Sexy::Delegate0(Sexy::MakeDelegate(*this, &LawnApp::KillPVZ2Dialog)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
	}
}

void LawnApp::ShowPlantLevelUpInfoDialog(MagentoProductPropsPtr i_props, bool ShowNotice, bool ShowSpecialPiece, int SpecialPieceId)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	if (!m_plantLevelUpInfoDialog)
		m_plantLevelUpInfoDialog = new PlantLevelUpInfoDialog(i_props, ShowNotice, ShowSpecialPiece, SpecialPieceId);
	mWidgetManager->AddWidget(m_plantLevelUpInfoDialog);
	mWidgetManager->BringToFront(m_plantLevelUpInfoDialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_plantLevelUpInfoDialog);
	mWidgetManager->SetFocus(m_plantLevelUpInfoDialog);
}

SexyString LawnApp::GetMoneyString(int i_amount)
{
	SexyString result = TodReplaceString(TodStringTranslate(L"[CURRENCY_STRING]"), L"{CURRENCY_SYMBOL}", TodStringTranslate(L"[CURRENCY_SYMBOL]").c_str());
	result = TodReplaceString(result, L"{AMOUNT}", Sexy::CommaSeparate(i_amount).c_str());
	return result;
}

std::string LawnApp::GetPlatformName()
{
	if (IsDeviceIPad())
	{
		if (mOrigScreenHeight == 1536 || mOrigScreenHeight == 2048)
			return "ipad3";
		return "ipad2";
	}
	std::string model = gSexyAppBase->mDiagDriver->GetInfoStringSafe(IDiagDriver::INFO_HardwareModel);
	if (model.find("iPod4") == std::string::npos)
		return "iphone";
	return "ipod4";
}

void LawnApp::onSyncProfileSummaryFinish(bool i_success)
{
	if (i_success)
	{
		setProfileConnected(true);
		if (gLawnApp->canDealProfile())
		{
			PlayerInfo* profile = ProfileUtils::Profile();
			if (profile)
			{
				if (profile->GetDeltaOnlineDataSign().empty())
					Sexy::LazySingleton<ProfileMgr>::GetInstance().Save(true, true);
				else
				{
					profile->UpdateDeltaDataForServer();
					if (profile->IsOlderThanServerData())
					{
						if (!isProfileOpened())
						{
							if (gLawnApp->GetWorldMap()->IsUserInputEnabled())
							{
								if (CheckProfileOpen())
									gLawnApp->ChooseProfile(false);
								else
									showDiffProfileSummary();
								setProfileOpened(true);
							}
						}
					}
					else
						Sexy::LazySingleton<ProfileMgr>::GetInstance().Save();
				}
			}
		}
	}
}

void LawnApp::onProfileSummarySelectResult(int i_result)
{
	if (gLawnApp->canDealProfile())
	{
		setProfileOpened(false);
		if (i_result == 0)
		{
			Sexy::LazySingleton<ProfileMgr>::GetInstance().Save(true, true);
			setSyncProfileSuccess(true);
			m_selfSync = true;
			closeDiffProfileSummary();
		}
		else
		{
			if (i_result == 1)
			{
				if (!Sexy::LazySingleton<ProfileMgr>::GetInstance().SyncProfileFromServer())
					gLawnApp->CheckNetWork(L"[NETWORK_NOT_CONNECTED_TITLE]", L"[NETWORK_NOT_CONNECTED_TEXT_FOR_SYNC_PLAYERINFO]");
				else
					setSyncProfileSuccess(true);
			}
			m_selfSync = true;
			closeDiffProfileSummary();
		}
	}
}

void LawnApp::ShowWorldMap()
{
	m_worldMap = new WorldMap();
	BehaviorLog::funnelEnd("WorldMap Shown", true);
	m_worldMap->Resize(0, 0, (int)std::max(m_contentResolutionWidth, (float)mWidth), (int)m_contentResolutionHeight);
	Sexy::Point offset = GetScreenContentOffset();
	m_worldMap->SetBaseOffset(offset);
	m_worldMap->Resize(offset.mX, offset.mY, m_worldMap->mWidth, m_worldMap->mHeight);
	mWidgetManager->AddWidget(m_worldMap);
	mWidgetManager->BringToBack(m_worldMap);
	mWidgetManager->SetFocus(m_worldMap);
}

bool LawnApp::IsAutoSmoking()
{
	return false;
}

int LawnApp::GetAllMapCount()
{
	return 16;
}

bool LawnApp::GetCheatsEnabled()
{
	return false;
}

void LawnApp::KillRatingDialog()
{
}

void LawnApp::ShowRatingDialog()
{
}

void LawnApp::KillIwatchRewardUI()
{
}

void LawnApp::KillPennyFuelStore()
{
}

void LawnApp::ShowIwatchRewardUI()
{
}

void LawnApp::RemapWorldMapEvents()
{
}

void LawnApp::PopulateWorldMapData()
{
}

int LawnApp::getCurrentWorldIndex()
{
	return true;
}

void LawnApp::KillNationalHolidayUI()
{
}

void LawnApp::RefreshTGPieceTableUI()
{
}

void LawnApp::ShowNationalHolidayUI()
{
}

int LawnApp::GetDragThresholdPixels()
{
	return 6;
}

void LawnApp::KillDangerRoomRewardUI()
{
}

void LawnApp::ShowDangerRoomRewardUI()
{
}

void LawnApp::ShowConsumptionRewardUI()
{
}

void LawnApp::RefreshTGAvatarPieceTableUI()
{
}

int LawnApp::GetButtonReleaseExpansionPixels()
{
	return 15;
}

void LawnApp::ButtonPress(int i_id)
{
}

bool LawnApp::DebugKeyDown(int i_key)
{
	return false;
}

void LawnApp::OnCloseDialog()
{
	 LawnApp::KillPVZ2Dialog();
}

void LawnApp::OnGestureFlick(Sexy::GestureFlickDirection i_direction, Sexy::Point i_startingLocation)
{
}

void LawnApp::SetCheatsEnabled(bool i_enabled)
{
}

void LawnApp::LaunchMerchWebpage(bool i_fromMainMenu)
{
}

bool LawnApp::IsWorldRSBFileLoaded(const std::string& i_world_name)
{
	return true;
}

void LawnApp::onEASquaredFlowEnded(const std::string& i_placementOrigin, int i_coinsEarned, int i_videosWatched)
{
	 LawnApp::KillNetConnectingUI();
}

void LawnApp::AppBecomingForeground()
{
	 BehaviorLog::resume();
}

void LawnApp::onItemPurchasedFromStore(MagentoProductProps* i_props)
{
}

bool LawnApp::NeedShowLoginRewardDialog(bool i_canUseLocalTime)
{
	return false;
}

void LawnApp::onPurchaseRefreshComplete(Sexy::IPurchaseDriver* purchase_driver)
{
}

void LawnApp::onEASquaredAdvertisementsClosed()
{
	 LawnApp::ResumeMusic();
}

time_t LawnApp::GetTimeStamp(const std::string& strDate, const std::string& strDateFormat)
{
	struct tm tmDate = {};
	strptime(strDate.c_str(), strDateFormat.c_str(), &tmDate);
	return GetTimegm(&tmDate);
}


void LawnApp::KillAccessorySwitchDialog()
{
	gLawnApp->KillPVZ2Dialog();
}






class BoxOpenUI* LawnApp::getBoxOpenUI()
{
	return m_boxOpenUI;
}

class RedPackUI* LawnApp::getRedPackUI()
{
	return m_redPackUI;
}

void LawnApp::AddModuleInfo(ModuleInfo i_module)
{
	m_moduleInfo |= i_module;
}

class EndLevelUI* LawnApp::GetEndLevelUI()
{
	return m_endLevelUI;
}

class GameMaskUI* LawnApp::GetGameMaskUI()
{
	return m_pGameMaskUI;
}

class UniverseWorldInfo* LawnApp::GetWorldInfoUI()
{
	return m_universeWorldInfo;
}

bool LawnApp::IsSalesUIValid()
{
	return m_salesUI != NULL;
}

void LawnApp::SetGoldenEggUI(class GoldenEggUI* i_goldenEggUI)
{
	m_goldenEggUI = i_goldenEggUI;
}


class WorldMap_ScrollBannerButton* LawnApp::GetScrollBanner()
{
	return m_scrollBanner;
}

class PVZ2UIWorldPreview* LawnApp::GetWorldPreview()
{
	return m_worldPreview;
}

bool LawnApp::IsPauseMenuOpen()
{
	return (m_pauseMenu != NULL);
}


class ArenaEndingUI* LawnApp::GetArenaEndingUI()
{
	return m_arenaEndingUI;
}

bool LawnApp::IsGachaUIShowing()
{
	return m_gachaUI != NULL;
}

void LawnApp::RemoveModuleInfo(ModuleInfo i_module)
{
	m_moduleInfo &= ~i_module;
}

class RedPackOpenUI* LawnApp::getRedPackOpenUI()
{
	return m_redPackOpenUI;
}



class PlantTrialViewUI* LawnApp::GetPlantTrialView()
{
	return m_pPlantTrialView;
}

class PostProcessOverlayWidget* LawnApp::GetPostProcessing()
{
	return m_postProcessWidget;
}

bool LawnApp::IsReviveUIShowing()
{
	return m_reviveUI != NULL;
}

void LawnApp::setCanDealProfile(bool i_canDealProfile)
{
	m_canDealProfile = i_canDealProfile;
}


class PVZ2UILotteryResult* LawnApp::GetLotteryResultUI()
{
	return m_lotteryResultUI;
}

uint32 LawnApp::GetMusicCallbackID()
{
	return m_callbackEventID;
}


bool LawnApp::IsCoinStoreShowing()
{
	return m_coinStore != NULL;
}

bool LawnApp::IsGoldenEggUIValid()
{
	return m_goldenEggUI != NULL;
}

class MetricsCollector* LawnApp::GetMetricsCollector()
{
	return m_metricsCollector;
}

bool LawnApp::IsActivityHomeValid()
{
	return m_activityHome != NULL;
}

bool LawnApp::IsGLDeliveryUIValid()
{
	return m_GLDeliveryUI != NULL;
}

bool LawnApp::IsStarConvertIValid()
{
	return m_starConvert != NULL;
}

bool LawnApp::IsStarConvertOpened()
{
	return m_isStarConvertOpened;
}

bool LawnApp::IsStoneLotteryValid()
{
	return m_pStoneLottery;
}

void LawnApp::SetAccessoryBonusUI(class DailyAccessoryBonusUI* i_accessoryBonusUI)
{
	m_dailyAccessoryBonusUI = i_accessoryBonusUI;
}

class LanternRiddlesUI* LawnApp::getLanternRiddlesUI()
{
	return m_lanternRiddlesUI;
}


void LawnApp::setProfileConnected(bool i_connected)
{
	m_connectedProfile = i_connected;
}

void LawnApp::ClearMusicCallbackID()
{
	m_callbackEventID = 0;
}

class TransitionOverlayWidget* LawnApp::GetTransitionOverlay()
{
	return m_transitionOverlay;
}

bool LawnApp::IsWorldUnlockShowing()
{
	return m_worldUnlock != NULL;
}

bool LawnApp::NeedRefreshLoginDays()
{
	return m_bRefreshLoginDays;
}

class OpenSurpriseUI* LawnApp::getSurpriseBoxOpenUI()
{
	return m_surpriseBoxOpenUI;
}


class WorldMapChooseDialog* LawnApp::GetChoosePlantsDialog()
{
	return m_ChoosePlantsDialog;
}

bool LawnApp::IsRechargeGiftUIValid()
{
	return m_RechargeGiftUI != NULL;
}

bool LawnApp::IsTGPieceTableUIValid()
{
	return m_tgPieceTableUI != NULL;
}

bool LawnApp::IsTransGenosisUIValid()
{
	return m_transGenosisUI != NULL;
}

bool LawnApp::IsWorldPreviewShowing()
{
	return m_worldPreview != NULL;
}

void LawnApp::setSyncProfileSuccess(bool i_success)
{
	m_syncProfileSuccess = i_success;
}

bool LawnApp::GetDoneLoadingProfiles()
{
	return m_doneLoadingProfiles;
}

class PlantAvatarListView* LawnApp::GetPlantAvatarListView()
{
	return m_plantAvatarListView;
}

bool LawnApp::IsGLStoneLotInfoWidget()
{
	return m_GLGLStoneLotUI != NULL;
}

bool LawnApp::IsGoldenEggOpenUIValid()
{
	return m_goldenEggOpenUI != NULL;
}

void LawnApp::IsNeedRefreshLoginDays(bool bRefresh)
{
	m_bRefreshLoginDays = bRefresh;
}

class PlantSpecialOfferUI* LawnApp::getPlantSpecialOfferUI()
{
	return m_PlantSpecialOfferUI;
}

class BoardZombieAlmanacUI* LawnApp::GetBoardZombieAlmanacUI()
{
	return m_boardZombieAlmanacUI;
}

class GachaDisplayerDialog* LawnApp::GetGachaDisplayerDialog()
{
	return m_gachaDisplayerDialog;
}

class PlantLevelUpListView* LawnApp::GetPlantLevelUpListView()
{
	return m_plantLevelUpListView;
}

bool LawnApp::IsAccessoryBonusUIValid()
{
	return m_dailyAccessoryBonusUI != NULL;
}

bool LawnApp::IsAdventureBonusUIValid()
{
	return m_AdventureBonusUI != NULL;
}

bool LawnApp::IsBattleStatementUIShow()
{
	return m_battleStatementUI != NULL;
}

bool LawnApp::IsNewerPresentUIShowing()
{
	return m_newerPresentUI != NULL;
}

bool LawnApp::IsPlantAdventureUIValid()
{
	return m_PlantAdventureUI != NULL;
}

bool LawnApp::IsShopChooseDialogValid()
{
	return m_shopChooseDialog != NULL;
}

bool LawnApp::IsActivityHomeExtraValid()
{
	return m_activityHomeExtra != NULL;
}

bool LawnApp::IsAdventureOpenedUIValid()
{
	return m_AdventureOpenedUI != NULL;
}

bool LawnApp::IsDailySignRewardShowing()
{
	return m_dailySignReward != NULL;
}

bool LawnApp::IsGeilivableLotteryValid()
{
	return m_geilivableLottery != NULL;
}

bool LawnApp::IsActivityCollectionValid()
{
	return m_activityCollection != NULL;
}

bool LawnApp::IsChoosePlantsDialogValid()
{
	return m_ChoosePlantsDialog != NULL;
}

bool LawnApp::IsLevelofDayEntranceValid()
{
	return m_levelofDayEntrance != NULL;
}

bool LawnApp::IsAdventureSurpriseUIValid()
{
	return m_AdventureSurpriseUI != NULL;
}

bool LawnApp::IsChooseRiddlesDialogValid()
{
	return m_ChooseRiddlesDialog != NULL;
}

bool LawnApp::IsChooseWelfareDialogValid()
{
	return m_ChooseWelfaleDialog != NULL;
}

bool LawnApp::IsWelfareChooseDialogValid()
{
	return m_welfareChooseDialog != NULL;
}

class PlantGeneEnhancementView* LawnApp::GetPlantGeneEnhancementView()
{
	return m_plantGeneEnhancementView;
}

bool LawnApp::IsFestivalEntranceUIShowing()
{
	return m_festivalEntranceUI != NULL;
}

bool LawnApp::IsTGAvatarPieceTableUIValid()
{
	return m_tgAvatarPieceTableUI != NULL;
}

class LevelOfTheDayRewardDialog* LawnApp::GetLevelOfTheDayRewardDialog()
{
	return m_pLevelOfTheDayRewardDialog;
}

bool LawnApp::IsAdventureTeamEditorUIValid()
{
	return m_TeamEditorUI != NULL;
}

bool LawnApp::IsChallengeChooseDialogValid()
{
	return m_challengeChooseDialog != NULL;
}

class ArtifactCultivationListView* LawnApp::GetArtifactCultivationListView()
{
	return m_artifactCultivationListView;
}

bool LawnApp::IsDailyActivityChooseDialogValid()
{
	return m_dailyActivityChooseDialog != NULL;
}

bool LawnApp::IsChooseActivityLevelsDialogValid()
{
	return m_ChooseActivityLevelsDialog != NULL;
}

class LevelOfTheDay_ProgressiveAwardDialog* LawnApp::GetLevelOfTheDayProgressiveAwardDialog()
{
	return m_pLevelOfTheDay_ProgressiveAwardDialog;
}

class SalesUI* LawnApp::GetSalesUI() const
{
	return m_salesUI;
}


class GoldenEggUI* LawnApp::GetGoldenEggUI() const
{
	return m_goldenEggUI;
}

class StarConvert* LawnApp::GetStarConvert() const
{
	return m_starConvert;
}

class StoneLottery* LawnApp::GetStoneLottery() const
{
	return m_pStoneLottery;
}

class PlantBundleUI* LawnApp::GetPlantBundleUI() const
{
	return m_PlantBundleUI;
}

class RechargeGiftUI* LawnApp::GetRechargeGiftUI() const
{
	return m_RechargeGiftUI;
}

class TGPieceTableUI* LawnApp::GetTGPieceTableUI() const
{
	return m_tgPieceTableUI;
}

class TransGenosisUI* LawnApp::GetTransGenosisUI() const
{
	return m_transGenosisUI;
}

const class GameCenterProxy* LawnApp::GetGameCenterProxy() const
{
	return m_gcp;
}

class GoldenEggOpenUI* LawnApp::GetGoldenEggOpenUI() const
{
	return m_goldenEggOpenUI;
}

class TwoYearBirthday* LawnApp::GetTwoYearBirthday() const
{
	return m_TwoYearBirthday;
}

class DailyAccessoryBonusUI* LawnApp::GetAccessoryBonusUI() const
{
	return m_dailyAccessoryBonusUI;
}

class AdventureBonusUI* LawnApp::GetAdventureBonusUI() const
{
	return m_AdventureBonusUI;
}

class PlantAdventureUI* LawnApp::GetPlantAdventureUI() const
{
	return m_PlantAdventureUI;
}

class AdventureOpenedUI* LawnApp::GetAdventureOpenedUI() const
{
	return m_AdventureOpenedUI;
}

class GeilivableLottery* LawnApp::GetGeilivableLottery() const
{
	return m_geilivableLottery;
}

class LevelOfDayEntrance* LawnApp::GetLevelofDayEntrance() const
{
	return m_levelofDayEntrance;
}

class AdventureSurpriseUI* LawnApp::GetAdventureSurpriseUI() const
{
	return m_AdventureSurpriseUI;
}

class TGAvatarPieceTableUI* LawnApp::GetTGAvatarPieceTableUI() const
{
	return m_tgAvatarPieceTableUI;
}

class AdventureTeamEditorUI* LawnApp::GetAdventureTeamEditorUI() const
{
	return m_TeamEditorUI;
}

void LawnApp::SetIsInited(bool i_inited)
{
	m_initDone = i_inited;
}

bool LawnApp::GetIsNewUser()
{
	return m_isNewUser;
}

const std::string LawnApp::GetSessionId()
{
	return m_sessionId;
}

void LawnApp::SetIsNewUser(bool i_new)
{
	m_isNewUser = i_new;
}

int LawnApp::GetAdsMapRate()
{
	return m_adsMapRate;
}

bool LawnApp::GetQiHooLogin()
{
	return m_hasQihooLogin;
}

void LawnApp::SetAdsMapRate(int rate)
{
	m_adsMapRate = rate;
}

void LawnApp::SetQiHooLogin(bool i_login)
{
	m_hasQihooLogin = i_login;
}

std::string LawnApp::GetAdsMapLimit()
{
	return m_adsMapLimit;
}

bool LawnApp::IsLoginSuccess()
{
	return m_bIsLoginSuccess;
}

void LawnApp::SetADBlackList(const std::vector<std::string>& i_list)
{
	m_adBlackList = i_list;
}

void LawnApp::SetAdsMapLimit(int level)
{
	m_adsMapLimit = "egypt";
	m_adsMapLimit += std::to_string(level);
}

int LawnApp::GetMaxAdsPerDay()
{
	return m_maxAdsPerDay;
}

void LawnApp::SetLoginSuccess(bool i_success)
{
	m_bIsLoginSuccess = i_success;
}

void LawnApp::SetMaxAdsPerDay(int rate)
{
	m_maxAdsPerDay = rate;
}

WorldCupConfig& LawnApp::GetWorldCupConfig()
{
	return m_stWorldCupConfig;
}

std::string LawnApp::GetAdsMissionLimit()
{
	return m_adsMissionLimit;
}

int LawnApp::GetDaveShopAdsRate()
{
	return m_daveShopAdsRate;
}

double LawnApp::GetLoadingDuration()
{
	return m_loadingTime;
}

bool LawnApp::HasSpecialGemOffer()
{
	return m_sGemOffer;
}

bool LawnApp::IsCanSetWaitingGem()
{
	return mWaitingServerGemCallBack == NULL;
}

void LawnApp::SetAdsMissionLimit(int level)
{
	m_adsMissionLimit = "egypt";
	m_adsMissionLimit += std::to_string(level);
}

void LawnApp::SetAdsTotalRateMax(int rate)
{
	m_maxAdsTotalRate = rate;
}

void LawnApp::SetAdsTotalRateMin(int rate)
{
	m_minAdsTotalRate = rate;
}

void LawnApp::SetLoadingDuration(double i_duration)
{
	m_loadingTime = i_duration;
}

void LawnApp::SetSpecialGemOffer(bool i_offer)
{
	m_sGemOffer = i_offer;
}

time_t LawnApp::GetLoadingBeginTime()
{
	return m_loadingBeginTime;
}

class PlantTrialConfig& LawnApp::GetPlantTrialConfig()
{
	return m_stPlantTrialConfig;
}

time_t LawnApp::GetStartLoadingTime()
{
	return m_startLoadingTime;
}

void LawnApp::SetAutoSmokingStart()
{
	m_bIsAutosmoking = true;
}

void LawnApp::SetWatchADBlackList(const std::vector<std::string>& i_list)
{
	m_watchADBlackList = i_list;
}

int LawnApp::GetCurrentAdsMapRate()
{
	return m_currentAdsMapRate;
}

OfferBundleConfig& LawnApp::GetOfferBundleConfig()
{
	return m_offerBundleConfig;
}


StarConvertConfig& LawnApp::GetStarConvertConfig()
{
	return m_stStarConvertConfig;
}

void LawnApp::SetCurrentAdsMapRate(int rate)
{
	m_currentAdsMapRate = rate;
}

void LawnApp::SetPaymentResultInfo(PaymentResultInfo& i_info)
{
	m_paymentResultInfo = i_info;
}

double LawnApp::GetDecompressDuration()
{
	return m_decompressTime;
}

const std::string& LawnApp::GetLastCompletedLevel()
{
	return m_lastClearedLevel;
}

const std::string& LawnApp::GetProfileCreatedTime()
{
	return m_profileCreatedTime;
}

RebateRewardConfig& LawnApp::GetRebateRewardConfig()
{
	return m_stRebateRewardConfig;
}

void LawnApp::SetLastCompletedLevel(const std::string& i_clearedLevel)
{
	m_lastClearedLevel = i_clearedLevel;
}

void LawnApp::SetOpenActivityGameUI(FestivalGameMode eGameMode)
{
	m_eGameMode = eGameMode;
}

void LawnApp::SetProfileCreatedTime(const std::string& i_time)
{
	m_profileCreatedTime = i_time;
}

RedPacketRewardInfo& LawnApp::GetRedPacketRewardInfo()
{
	return m_stRedPacketRewardInfo;
}

DailyAchievementInfo& LawnApp::GetDailyAchievementInfo()
{
	return m_stDailyAchievementInfo;
}

PlantAdventureConfig& LawnApp::GetPlantAdventureConfig()
{
	return m_stPlantAdventureConfig;
}

ConsumptionRewardInfo& LawnApp::GetConsumptionRewardInfo()
{
	return m_stConsumptionRewardInfo;
}

JoustPlantPowerConfig& LawnApp::GetJoustPlantPowerConfig()
{
	return m_stJoustPlantPowerConfig;
}

LostNetActivityConfig& LawnApp::GetLostNetActivityConfig()
{
	return m_stLostNetActivityConfig;
}

bool LawnApp::IsUsingSpecialBackground()
{
	return m_usingSpecialBackground;
}

void LawnApp::RefreshStarConvertConfig()
{
	m_stStarConvertConfig.Refresh();
}

int LawnApp::GetPlantAdventureTabIndex()
{
	return m_PlantAdventureTabIndex;
}

void LawnApp::SetPlantAdventureTabIndex(int i_index)
{
	m_PlantAdventureTabIndex = i_index;
}

void LawnApp::SetUsingSpecialBackground(bool i_special)
{
	m_usingSpecialBackground = i_special;
}

LevelOfTheDayConfigInfo& LawnApp::GetLevelOfTheDayConfigInfo()
{
	return m_stLevelOfTheDayConfigInfo;
}

RechargeRewardConfig& LawnApp::GetRechargeRewardConfigInfo()
{
	return m_stRechargeRewardConfig;
}

void LawnApp::QueueUnlocksFromArcadeLevel(const std::string& i_levelName)
{
	m_queuedArcadeUnlockSource = i_levelName;
}

void LawnApp::RefreshPlantAdventureConfig()
{
	m_stPlantAdventureConfig.Refresh();
}

void LawnApp::RefreshConsumptionRewardInfo()
{
	m_stConsumptionRewardInfo.InitDate();
}

float LawnApp::GetCustomLevelEvaluationParam()
{
	return m_customLevelEvaluationParam;
}

void LawnApp::SetCustomLevelEvaluationParam(float value)
{
	m_customLevelEvaluationParam = value;
}

NationalDayRewardConfigInfo& LawnApp::GetNationalDayRewardConfigInfo()
{
	return m_stNationalDayRewardConfigInfo;
}

bool LawnApp::GetShouldBackToMapAtDangerRoom()
{
	return m_bBacktoMapAtDangerRoom;
}

void LawnApp::SetShouldBackToMapAtDangerRoom(bool bYes)
{
	m_bBacktoMapAtDangerRoom = bYes;
}

std::string LawnApp::GetAndClearQueuedArcadeUnlockSource()
{
	std::string source = m_queuedArcadeUnlockSource;
	m_queuedArcadeUnlockSource.clear();
	return source;
}

class QiHooPlatform* LawnApp::GetQiHooPlatform() const
{
	return m_qihoo;
}

MagentoLanguage LawnApp::GetMagentoLanguage() const
{
	return m_magentoLanguage;
}

pvztime_t LawnApp::GetLastTouchEndTime()
{
	return m_lastTouchEndTimne;
}

int LawnApp::GetCurrentVersion() const
{
	return Android::Info::SysGetProductVersionCode();
}

int LawnApp::GetDeviceCardType()
{
	return Android::Diag::GetMobileCardType();
}

void LawnApp::KillProbabilityDialog()
{
	ProbabilityDLG::CloseDialog();
}

void LawnApp::ShowChildrenDayUI()
{
	ChildrenDayUI::ShowDialog();
}

void LawnApp::SetMasterVolume(double i_volume)
{
	Sexy::SexyAppBase::SetMasterVolume(i_volume);
}

void LawnApp::SetMusicVolume(double i_volume)
{
	Sexy::SexyAppBase::SetMusicVolume(i_volume);
}

void LawnApp::SetSfxVolume(double i_volume)
{
	Sexy::SexyAppBase::SetSfxVolume(i_volume);
}

void LawnApp::onFaiicck()
{
	Android::Device::ExitApp();
}

void LawnApp::onMatikck()
{
	Android::Device::ExitApp();
}

void LawnApp::Start()
{
	if (!mLoadingFailed)
		Sexy::SexyAppBase::Start();
}

void LawnApp::onCancelExitGame()
{
	gLawnApp->KillPVZ2Dialog();
}

bool LawnApp::IsHighFPSMode()
{
	return m_isHighFPSMode;
}

void LawnApp::GotSpringGift()
{
	m_gettingSpringGift = false;
}

bool LawnApp::HasShownSpringGiftUI()
{
	return m_hasShownSpringGiftUI;
}

bool LawnApp::IsGettingSpringGift()
{
	return m_gettingSpringGift;
}

bool LawnApp::IsTimeNeedFix()
{
	return m_needFixingTime;
}

void LawnApp::SetUserHasDisabledUsageSharing(bool i_disabled)
{
	if (m_hasDisabledUsageSharing != i_disabled)
	{
		m_hasDisabledUsageSharing = i_disabled;
		gSexyAppBase->RegistryWriteBoolean("HasDisabledUsageSharing", m_hasDisabledUsageSharing);
		WriteToRegistry();
		SetUsageSharingSystemStates();
	}
}

bool LawnApp::UserHasDisabledUsageSharing()
{
	return m_hasDisabledUsageSharing;
}

bool LawnApp::NetworkContentCheckComplete()
{
	return m_networkTableManager.NetworkRequestsCompleted();
}

PVZVersionNetworkManager& LawnApp::GetVersionNetworkManager()
{
	return m_versionNetworkManager;
}

PVZRechargeCheckServer& LawnApp::GetRechargeCheckServer()
{
	return m_rechargeCheckServer;
}

DailyRewardConfig* LawnApp::GetDailyRewardConfig()
{
	return m_dailyRewardConfig;
}

GetGemsRestoreUI* LawnApp::GetGemsRestoreUI()
{
	return m_GetGemsRestoreUI;
}

PVZ2UIStarLevelUp* LawnApp::GetPVZ2UIStarLevelUp()
{
	return m_plantStarLevelUpAnimUI;
}

PlantAccessoryUI* LawnApp::getPlantAccessoryUI()
{
	return m_plantAccessoryUI;
}

int LawnApp::getCurrentChallengeIndex()
{
	return -1;
}

void LawnApp::SetAndroidSDKInitStatus(int isEnd, int status)
{
	m_androidSDKInitEnd = isEnd;
	m_androidSDKInitStatus = status;
}

void LawnApp::SetServiceAvailable(ServiceFlags i_flag, bool i_available)
{
	SetFlag(m_serviceFlags, i_flag, i_available);
}

void LawnApp::SetWaitingGemCallBack(Sexy::Delegate1<bool> i_callBack)
{
	mWaitingServerGemCallBack = i_callBack;
}

void LawnApp::SetGMInfoExtraType(std::string i_type)
{
	m_gmInfoExtraType = i_type;
}

ResourceInfoTypes::ImageRes* LawnApp::GetUIImageInfoFromStringId(const std::string& i_imageName)
{
	return GetImageInfoFromStringId(i_imageName, mHeight);
}

void LawnApp::KillPVZ2Dialog()
{
	if (m_dialog)
	{
		mWidgetManager->RemoveWidget(m_dialog);
		mWidgetManager->RemoveBaseModal(m_dialog);
		SafeDeleteWidget(m_dialog);
		m_dialog = NULL;
	}
}

void LawnApp::KillReviveUI()
{
	if (m_reviveUI)
	{
		if (m_board)
		{
			ResumeMusic();
			m_board->Pause(false);
		}
		mWidgetManager->RemoveWidget(m_reviveUI);
		mWidgetManager->RemoveBaseModal(m_reviveUI);
		SafeDeleteWidget(m_reviveUI);
		m_reviveUI = NULL;
	}
}




void LawnApp::KillBuyItemUI()
{
	if (m_BuyItemUI)
	{
		if (m_board)
		{
			ResumeMusic();
			m_board->Pause(false);
		}
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_BuyItemUI);
		mWidgetManager->RemoveBaseModal(m_BuyItemUI);
		SafeDeleteWidget(m_BuyItemUI);
		m_BuyItemUI = NULL;
	}
}

void LawnApp::KillCoinStore()
{
	if (m_coinStore)
	{
		if (m_board)
		{
			ResumeMusic();
			m_board->Pause(false);
		}
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_coinStore);
		mWidgetManager->RemoveBaseModal(m_coinStore);
		SafeDeleteWidget(m_coinStore);
		m_coinStore = NULL;
	}
}

void LawnApp::KillDaveClubUI()
{
	if (m_pDaveClubUI)
	{
		if (m_board)
		{
			ResumeMusic();
			m_board->Pause(false);
		}
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_pDaveClubUI);
		mWidgetManager->RemoveBaseModal(m_pDaveClubUI);
		SafeDeleteWidget(m_pDaveClubUI);
		m_pDaveClubUI = NULL;
	}
}

void LawnApp::KillFestivalEntranceUI()
{
	if (m_festivalEntranceUI)
	{
		if (m_board)
		{
			ResumeMusic();
			m_board->Pause(false);
		}
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_festivalEntranceUI);
		mWidgetManager->RemoveBaseModal(m_festivalEntranceUI);
		SafeDeleteWidget(m_festivalEntranceUI);
		m_festivalEntranceUI = NULL;
	}
}

void LawnApp::KillNewerPresentUI()
{
	if (m_newerPresentUI)
	{
		if (m_board)
		{
			ResumeMusic();
			m_board->Pause(false);
		}
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_newerPresentUI);
		mWidgetManager->RemoveBaseModal(m_newerPresentUI);
		SafeDeleteWidget(m_newerPresentUI);
		m_newerPresentUI = NULL;
	}
}


void LawnApp::KillBattleStatementUI()
{
	if (m_battleStatementUI)
	{
		if (m_board)
		{
			ResumeMusic();
			m_board->Pause(false);
		}
		mWidgetManager->RemoveWidget(m_battleStatementUI);
		mWidgetManager->RemoveBaseModal(m_battleStatementUI);
		SafeDeleteWidget(m_battleStatementUI);
		m_battleStatementUI = NULL;
	}
}

void LawnApp::KillStarLevelChallengeUI()
{
	if (m_starLevelChallengeUI)
	{
		if (m_board)
		{
			ResumeMusic();
			m_board->Pause(false);
		}
		mWidgetManager->RemoveWidget(m_starLevelChallengeUI);
		mWidgetManager->RemoveBaseModal(m_starLevelChallengeUI);
		SafeDeleteWidget(m_starLevelChallengeUI);
		m_starLevelChallengeUI = NULL;
	}
}


void LawnApp::ShowBirthdayRewardDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_pBirthdayRewardDialog)
		KillBirthdayRewardDialog();
	m_pBirthdayRewardDialog = new BirthdayRewardDialog();
	mWidgetManager->AddWidget(m_pBirthdayRewardDialog);
	mWidgetManager->BringToFront(m_pBirthdayRewardDialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_pBirthdayRewardDialog);
	mWidgetManager->SetFocus(m_pBirthdayRewardDialog);
}

void LawnApp::ShowOppoNewerEventUI()
{
	if (m_OppoNewerEventUI)
		return;
	UISingletonDialog<OppoNewerEventUI>::ShowDialog();
	m_OppoNewerEventUI = UISingletonDialog<OppoNewerEventUI>::GetSingletonPtr();
	m_OppoNewerEventUI->InitView();
	mWidgetManager->AddWidget(m_OppoNewerEventUI);
	mWidgetManager->BringToFront(m_OppoNewerEventUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_OppoNewerEventUI);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_OppoNewerEventUI);
}

void LawnApp::KillBirthdayRewardDialog()
{
	if (m_pBirthdayRewardDialog)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_pBirthdayRewardDialog);
		mWidgetManager->RemoveBaseModal(m_pBirthdayRewardDialog);
		SafeDeleteWidget(m_pBirthdayRewardDialog);
		m_pBirthdayRewardDialog = NULL;
	}
}

void LawnApp::KillBuyAvatarDialog()
{
	if (m_board)
		m_board->Pause(false);
	if (m_buyAvatarDialog)
	{
		mWidgetManager->RemoveWidget(m_buyAvatarDialog);
		mWidgetManager->RemoveBaseModal(m_buyAvatarDialog);
		SafeDeleteWidget(m_buyAvatarDialog);
		m_buyAvatarDialog = NULL;
	}
}

void LawnApp::KillBuyGachaDialog()
{
	if (m_board)
		m_board->Pause(false);
	if (m_buyGachaDialog)
	{
		mWidgetManager->RemoveWidget(m_buyGachaDialog);
		mWidgetManager->RemoveBaseModal(m_buyGachaDialog);
		SafeDeleteWidget(m_buyGachaDialog);
		m_buyGachaDialog = NULL;
	}
}

void LawnApp::KillBuyGiftDialog()
{
	if (m_board)
		m_board->Pause(false);
	if (m_buyGiftDialog)
	{
		mWidgetManager->RemoveWidget(m_buyGiftDialog);
		mWidgetManager->RemoveBaseModal(m_buyGiftDialog);
		SafeDeleteWidget(m_buyGiftDialog);
		m_buyGiftDialog = NULL;
	}
}

void LawnApp::KillBuyPlantDialog()
{
	if (m_board)
		m_board->Pause(false);
	if (m_buyPlantDialog)
	{
		mWidgetManager->RemoveWidget(m_buyPlantDialog);
		mWidgetManager->RemoveBaseModal(m_buyPlantDialog);
		SafeDeleteWidget(m_buyPlantDialog);
		m_buyPlantDialog = NULL;
	}
}

void LawnApp::KillConsumptionRewardDialog()
{
	if (m_pConsumptionRewardDialog)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_pConsumptionRewardDialog);
		mWidgetManager->RemoveBaseModal(m_pConsumptionRewardDialog);
		SafeDeleteWidget(m_pConsumptionRewardDialog);
		m_pConsumptionRewardDialog = NULL;
	}
}

void LawnApp::KillDailyAchievement()
{
	if (m_dailyAchievement)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_dailyAchievement);
		mWidgetManager->RemoveBaseModal(m_dailyAchievement);
		SafeDeleteWidget(m_dailyAchievement);
		m_dailyAchievement = NULL;
	}
}


void LawnApp::KillLanternRiddlesUI()
{
	if (m_lanternRiddlesUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_lanternRiddlesUI);
		mWidgetManager->RemoveBaseModal(m_lanternRiddlesUI);
		SafeDeleteWidget(m_lanternRiddlesUI);
		m_lanternRiddlesUI = NULL;
	}
}

void LawnApp::KillLevelOfTheDayProgressiveAwardDialog()
{
	if (m_pLevelOfTheDay_ProgressiveAwardDialog)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_pLevelOfTheDay_ProgressiveAwardDialog);
		mWidgetManager->RemoveBaseModal(m_pLevelOfTheDay_ProgressiveAwardDialog);
		SafeDeleteWidget(m_pLevelOfTheDay_ProgressiveAwardDialog);
		m_pLevelOfTheDay_ProgressiveAwardDialog = NULL;
	}
}

void LawnApp::KillLevelOfTheDayRewardDialog()
{
	if (m_pLevelOfTheDayRewardDialog)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_pLevelOfTheDayRewardDialog);
		mWidgetManager->RemoveBaseModal(m_pLevelOfTheDayRewardDialog);
		SafeDeleteWidget(m_pLevelOfTheDayRewardDialog);
		m_pLevelOfTheDayRewardDialog = NULL;
	}
}

void LawnApp::KillLotteryResultUI()
{
	if (m_board)
		m_board->Pause(false);
	if (m_lotteryResultUI)
	{
		mWidgetManager->RemoveWidget(m_lotteryResultUI);
		mWidgetManager->RemoveBaseModal(m_lotteryResultUI);
		SafeDeleteWidget(m_lotteryResultUI);
		m_lotteryResultUI = NULL;
	}
}

void LawnApp::KillLotteryUI()
{
	if (m_LotteryUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_LotteryUI);
		mWidgetManager->RemoveBaseModal(m_LotteryUI);
		SafeDeleteWidget(m_LotteryUI);
		m_LotteryUI = NULL;
	}
}

void LawnApp::KillPVPZombieLevelUpDialog()
{
	if (m_pPVPZombieLevelUpDialog)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_pPVPZombieLevelUpDialog);
		mWidgetManager->RemoveBaseModal(m_pPVPZombieLevelUpDialog);
		SafeDeleteWidget(m_pPVPZombieLevelUpDialog);
		m_pPVPZombieLevelUpDialog = NULL;
	}
}

void LawnApp::KillPlantAccessoryUI()
{
	if (m_plantAccessoryUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_plantAccessoryUI);
		mWidgetManager->RemoveBaseModal(m_plantAccessoryUI);
		SafeDeleteWidget(m_plantAccessoryUI);
		m_plantAccessoryUI = NULL;
	}
}

void LawnApp::KillPlantAvatarInfoDialog()
{
	if (m_board)
		m_board->Pause(false);
	if (m_plantAvatarInfoDialog)
	{
		mWidgetManager->RemoveWidget(m_plantAvatarInfoDialog);
		mWidgetManager->RemoveBaseModal(m_plantAvatarInfoDialog);
		SafeDeleteWidget(m_plantAvatarInfoDialog);
		m_plantAvatarInfoDialog = NULL;
	}
}

void LawnApp::KillPlantAvatarPackageView()
{
	if (m_board)
		m_board->Pause(false);
	if (m_plantAvatarPackageView)
	{
		mWidgetManager->RemoveWidget(m_plantAvatarPackageView);
		mWidgetManager->RemoveBaseModal(m_plantAvatarPackageView);
		SafeDeleteWidget(m_plantAvatarPackageView);
		m_plantAvatarPackageView = NULL;
	}
}

void LawnApp::KillPlantLevelUpCheckDialog()
{
	if (m_board)
		m_board->Pause(false);
	if (m_plantLevelUpCheckDialog)
	{
		mWidgetManager->RemoveWidget(m_plantLevelUpCheckDialog);
		mWidgetManager->RemoveBaseModal(m_plantLevelUpCheckDialog);
		SafeDeleteWidget(m_plantLevelUpCheckDialog);
		m_plantLevelUpCheckDialog = NULL;
	}
}

void LawnApp::KillPlantLevelUpInfoDialog()
{
	if (m_board)
		m_board->Pause(false);
	if (m_plantLevelUpInfoDialog)
	{
		mWidgetManager->RemoveWidget(m_plantLevelUpInfoDialog);
		mWidgetManager->RemoveBaseModal(m_plantLevelUpInfoDialog);
		SafeDeleteWidget(m_plantLevelUpInfoDialog);
		m_plantLevelUpInfoDialog = NULL;
	}
}

void LawnApp::KillPlantStarLevelUpAnimUI()
{
	if (m_board)
		m_board->Pause(false);
	if (m_plantStarLevelUpAnimUI)
	{
		mWidgetManager->RemoveWidget(m_plantStarLevelUpAnimUI);
		mWidgetManager->RemoveBaseModal(m_plantStarLevelUpAnimUI);
		SafeDeleteWidget(m_plantStarLevelUpAnimUI);
		m_plantStarLevelUpAnimUI = NULL;
	}
}

void LawnApp::KillRedPackUI()
{
	if (m_redPackUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_redPackUI);
		mWidgetManager->RemoveBaseModal(m_redPackUI);
		SafeDeleteWidget(m_redPackUI);
		m_redPackUI = NULL;
	}
}





void LawnApp::KillAdventureBonusUI()
{
	if (m_AdventureBonusUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_AdventureBonusUI);
		SafeDeleteWidget(m_AdventureBonusUI);
		m_AdventureBonusUI = NULL;
	}
}

void LawnApp::KillAdventureOpenedUI()
{
	if (m_AdventureOpenedUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_AdventureOpenedUI);
		SafeDeleteWidget(m_AdventureOpenedUI);
		m_AdventureOpenedUI = NULL;
	}
}

void LawnApp::KillAdventureSurpriseUI()
{
	if (m_AdventureSurpriseUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_AdventureSurpriseUI);
		SafeDeleteWidget(m_AdventureSurpriseUI);
		m_AdventureSurpriseUI = NULL;
	}
}

void LawnApp::KillAdventureTeamEditorUI()
{
	if (m_TeamEditorUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_TeamEditorUI);
		SafeDeleteWidget(m_TeamEditorUI);
		m_TeamEditorUI = NULL;
	}
}

void LawnApp::KillArtifactCultivationListView()
{
	if (m_artifactCultivationListView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_artifactCultivationListView);
		SafeDeleteWidget(m_artifactCultivationListView);
		m_artifactCultivationListView = NULL;
	}
}

void LawnApp::KillGoldenEggOpenUI()
{
	if (m_goldenEggOpenUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_goldenEggOpenUI);
		SafeDeleteWidget(m_goldenEggOpenUI);
		m_goldenEggOpenUI = NULL;
	}
}


void LawnApp::KillLevelofDayEntrance()
{
	if (m_levelofDayEntrance)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_levelofDayEntrance);
		SafeDeleteWidget(m_levelofDayEntrance);
		m_levelofDayEntrance = NULL;
	}
}

void LawnApp::KillNostalgiaPVZGameView()
{
	if (m_nostalgiaPVZGameView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Stop_Music_Anniversary");
		mWidgetManager->RemoveWidget(m_nostalgiaPVZGameView);
		SafeDeleteWidget(m_nostalgiaPVZGameView);
		m_nostalgiaPVZGameView = NULL;
	}
}

void LawnApp::KillPlantGeneEnhancementView()
{
	if (m_plantGeneEnhancementView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_plantGeneEnhancementView);
		SafeDeleteWidget(m_plantGeneEnhancementView);
		m_plantGeneEnhancementView = NULL;
	}
}

void LawnApp::KillPlantSkillTipsUI()
{
	if (m_board)
		m_board->Pause(false);
	if (m_plantSkillTipsUI)
	{
		mWidgetManager->RemoveWidget(m_plantSkillTipsUI);
		SafeDeleteWidget(m_plantSkillTipsUI);
		m_plantSkillTipsUI = NULL;
	}
}

void LawnApp::KillRechargeGiftUI()
{
	if (m_RechargeGiftUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_RechargeGiftUI);
		SafeDeleteWidget(m_RechargeGiftUI);
		m_RechargeGiftUI = NULL;
	}
}

void LawnApp::KillRedeemRewardUI()
{
	if (m_RedeemRewardUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_RedeemRewardUI);
		SafeDeleteWidget(m_RedeemRewardUI);
		m_RedeemRewardUI = NULL;
	}
}

void LawnApp::KillStarConvert()
{
	if (m_starConvert)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_starConvert);
		SafeDeleteWidget(m_starConvert);
		m_starConvert = NULL;
	}
}

void LawnApp::KillTGAvatarPieceTableUI()
{
	if (m_tgAvatarPieceTableUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_tgAvatarPieceTableUI);
		SafeDeleteWidget(m_tgAvatarPieceTableUI);
		m_tgAvatarPieceTableUI = NULL;
	}
}

void LawnApp::KillTGPieceTableUI()
{
	if (m_tgPieceTableUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_tgPieceTableUI);
		SafeDeleteWidget(m_tgPieceTableUI);
		m_tgPieceTableUI = NULL;
	}
}



void LawnApp::KillPVPMapUI()
{
	if (m_pvpMapUI)
	{
		mWidgetManager->RemoveWidget(m_pvpMapUI);
		SafeDeleteWidget(m_pvpMapUI);
		m_pvpMapUI = NULL;
	}
}




void LawnApp::KillArenaEndingUI()
{
	if (m_arenaEndingUI)
	{
		mWidgetManager->RemoveWidget(m_arenaEndingUI);
		mWidgetManager->RemoveBaseModal(m_arenaEndingUI);
		SafeDeleteWidget(m_arenaEndingUI);
		m_arenaEndingUI = NULL;
	}
}

void LawnApp::KillBoxOpenUI()
{
	if (m_boxOpenUI)
	{
		mWidgetManager->RemoveWidget(m_boxOpenUI);
		mWidgetManager->RemoveBaseModal(m_boxOpenUI);
		SafeDeleteWidget(m_boxOpenUI);
		m_boxOpenUI = NULL;
	}
}

void LawnApp::KillChristmasLotteryReward()
{
	if (m_pChristmasLotteryReward)
	{
		mWidgetManager->RemoveWidget(m_pChristmasLotteryReward);
		mWidgetManager->RemoveBaseModal(m_pChristmasLotteryReward);
		SafeDeleteWidget(m_pChristmasLotteryReward);
		m_pChristmasLotteryReward = NULL;
	}
}

void LawnApp::KillOpenSurpriseBoxUI()
{
	if (m_surpriseBoxOpenUI)
	{
		mWidgetManager->RemoveWidget(m_surpriseBoxOpenUI);
		mWidgetManager->RemoveBaseModal(m_surpriseBoxOpenUI);
		SafeDeleteWidget(m_surpriseBoxOpenUI);
		m_surpriseBoxOpenUI = NULL;
	}
}


void LawnApp::KillPlantOfferOpenUI()
{
	if (m_plantOfferOpenUI)
	{
		mWidgetManager->RemoveWidget(m_plantOfferOpenUI);
		mWidgetManager->RemoveBaseModal(m_plantOfferOpenUI);
		SafeDeleteWidget(m_plantOfferOpenUI);
		m_plantOfferOpenUI = NULL;
	}
}

void LawnApp::KillRedPackOpenUI()
{
	if (m_redPackOpenUI)
	{
		mWidgetManager->RemoveWidget(m_redPackOpenUI);
		mWidgetManager->RemoveBaseModal(m_redPackOpenUI);
		SafeDeleteWidget(m_redPackOpenUI);
		m_redPackOpenUI = NULL;
	}
}

void LawnApp::KillServerBoxOpenUI()
{
	if (m_serverBoxOpenUI)
	{
		mWidgetManager->RemoveWidget(m_serverBoxOpenUI);
		mWidgetManager->RemoveBaseModal(m_serverBoxOpenUI);
		SafeDeleteWidget(m_serverBoxOpenUI);
		m_serverBoxOpenUI = NULL;
	}
}

void LawnApp::KillWorldPreview()
{
	if (m_universeWorldInfo)
	{
		mWidgetManager->RemoveWidget(m_universeWorldInfo);
		mWidgetManager->RemoveBaseModal(m_universeWorldInfo);
		SafeDeleteWidget(m_universeWorldInfo);
		m_universeWorldInfo = NULL;
	}
}

void LawnApp::KillWorldUnlock()
{
	if (m_worldUnlock)
	{
		mWidgetManager->RemoveWidget(m_worldUnlock);
		mWidgetManager->RemoveBaseModal(m_worldUnlock);
		SafeDeleteWidget(m_worldUnlock);
		m_worldUnlock = NULL;
	}
}


void LawnApp::KillActivityCollection()
{
	if (m_activityCollection)
	{
		mWidgetManager->RemoveWidget(m_activityCollection);
		SafeDeleteWidget(m_activityCollection);
		m_activityCollection = NULL;
	}
}

void LawnApp::KillActivityHome()
{
	if (m_activityHome)
	{
		mWidgetManager->RemoveWidget(m_activityHome);
		SafeDeleteWidget(m_activityHome);
		m_activityHome = NULL;
	}
}

void LawnApp::KillActivityHomeExtra()
{
	if (m_activityHomeExtra)
	{
		mWidgetManager->RemoveWidget(m_activityHomeExtra);
		SafeDeleteWidget(m_activityHomeExtra);
		m_activityHomeExtra = NULL;
	}
}


void LawnApp::KillChallengeChooseDialog()
{
	if (m_challengeChooseDialog)
	{
		mWidgetManager->RemoveWidget(m_challengeChooseDialog);
		SafeDeleteWidget(m_challengeChooseDialog);
		m_challengeChooseDialog = NULL;
	}
}

void LawnApp::KillChooseActivityLevelsDialog()
{
	if (m_ChooseActivityLevelsDialog)
	{
		mWidgetManager->RemoveWidget(m_ChooseActivityLevelsDialog);
		SafeDeleteWidget(m_ChooseActivityLevelsDialog);
		m_ChooseActivityLevelsDialog = NULL;
	}
}

void LawnApp::KillChoosePlantsDialog()
{
	if (m_ChoosePlantsDialog)
	{
		mWidgetManager->RemoveWidget(m_ChoosePlantsDialog);
		SafeDeleteWidget(m_ChoosePlantsDialog);
		m_ChoosePlantsDialog = NULL;
	}
}

void LawnApp::KillChooseRiddlesDialog()
{
	if (m_ChooseRiddlesDialog)
	{
		mWidgetManager->RemoveWidget(m_ChooseRiddlesDialog);
		SafeDeleteWidget(m_ChooseRiddlesDialog);
		m_ChooseRiddlesDialog = NULL;
	}
}

void LawnApp::KillChooseWelfareDialog()
{
	if (m_ChooseWelfaleDialog)
	{
		mWidgetManager->RemoveWidget(m_ChooseWelfaleDialog);
		SafeDeleteWidget(m_ChooseWelfaleDialog);
		m_ChooseWelfaleDialog = NULL;
	}
}

void LawnApp::KillCustomLevelView()
{
	if (m_customLevelView)
	{
		mWidgetManager->RemoveWidget(m_customLevelView);
		SafeDeleteWidget(m_customLevelView);
		m_customLevelView = NULL;
	}
}

void LawnApp::KillDailyActivityChooseDialog()
{
	if (m_dailyActivityChooseDialog)
	{
		mWidgetManager->RemoveWidget(m_dailyActivityChooseDialog);
		SafeDeleteWidget(m_dailyActivityChooseDialog);
		m_dailyActivityChooseDialog = NULL;
	}
}



void LawnApp::KillGetGemsRestoreUI()
{
	if (m_GetGemsRestoreUI)
	{
		mWidgetManager->RemoveWidget(m_GetGemsRestoreUI);
		SafeDeleteWidget(m_GetGemsRestoreUI);
		m_GetGemsRestoreUI = NULL;
	}
}

void LawnApp::KillGetNewerBagUI()
{
	if (m_GetNewerBagUI)
	{
		mWidgetManager->RemoveWidget(m_GetNewerBagUI);
		SafeDeleteWidget(m_GetNewerBagUI);
		m_GetNewerBagUI = NULL;
	}
}

void LawnApp::KillGetPlantBagUI()
{
	if (m_GetPlantBagUI)
	{
		mWidgetManager->RemoveWidget(m_GetPlantBagUI);
		SafeDeleteWidget(m_GetPlantBagUI);
		m_GetPlantBagUI = NULL;
	}
}


void LawnApp::KillNetConnectingUI()
{
	if (m_netConnectingUI)
	{
		mWidgetManager->RemoveWidget(m_netConnectingUI);
		SafeDeleteWidget(m_netConnectingUI);
		m_netConnectingUI = NULL;
	}
}

void LawnApp::KillNewPlayerCollection()
{
	if (m_newPlayerCollection)
	{
		mWidgetManager->RemoveWidget(m_newPlayerCollection);
		SafeDeleteWidget(m_newPlayerCollection);
		m_newPlayerCollection = NULL;
	}
}

void LawnApp::KillRechargeRewardDisplayer()
{
	if (m_rechargeRewardDisplayer)
	{
		mWidgetManager->RemoveWidget(m_rechargeRewardDisplayer);
		SafeDeleteWidget(m_rechargeRewardDisplayer);
		m_rechargeRewardDisplayer = NULL;
	}
}

void LawnApp::KillRewardPlantUI()
{
	if (m_rewardPlantUI)
	{
		mWidgetManager->RemoveWidget(m_rewardPlantUI);
		SafeDeleteWidget(m_rewardPlantUI);
		m_rewardPlantUI = NULL;
	}
}


void LawnApp::KillShopChooseDialog()
{
	if (m_shopChooseDialog)
	{
		mWidgetManager->RemoveWidget(m_shopChooseDialog);
		SafeDeleteWidget(m_shopChooseDialog);
		m_shopChooseDialog = NULL;
	}
}

void LawnApp::KillSkycityBossWarnig()
{
	if (m_skycityBossWarningInfo)
	{
		mWidgetManager->RemoveWidget(m_skycityBossWarningInfo);
		SafeDeleteWidget(m_skycityBossWarningInfo);
		m_skycityBossWarningInfo = NULL;
	}
}

void LawnApp::KillWelfareChooseDialog()
{
	if (m_welfareChooseDialog)
	{
		mWidgetManager->RemoveWidget(m_welfareChooseDialog);
		SafeDeleteWidget(m_welfareChooseDialog);
		m_welfareChooseDialog = NULL;
	}
}



void LawnApp::KillPlantLevelUpListView()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
	mWidgetManager->RemoveWidget(m_plantLevelUpListView);
	SafeDeleteWidget(m_plantLevelUpListView);
	m_plantLevelUpListView = NULL;
	AudioMgr::GetInstancePtr()->SendEvent("AutoTestPlantLevelUp");
}

void LawnApp::KillWorldMap()
{
	AudioMgr::GetInstancePtr()->SendEvent("UIWorldMapLuaVirtualBtns");
	mWidgetManager->RemoveWidget(m_worldMap);
	SafeDeleteWidget(m_worldMap);
	m_worldMap = NULL;
	AudioMgr::GetInstancePtr()->SendEvent("WorldMap Shown");
}

void LawnApp::KillBoard()
{
	mWidgetManager->RemoveWidget(m_board);
	SafeDeleteWidget(m_board);
	m_board = NULL;
	BehaviorLog::funnelEnd("Board Shown", false);
}

void LawnApp::KillGachaUI()
{
	if (m_gachaUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		if (mWidgetManager->HasWidget(m_gachaUI))
		{
			mWidgetManager->RemoveWidget(m_gachaUI);
			mWidgetManager->RemoveBaseModal(m_gachaUI);
			SafeDeleteWidget(m_gachaUI);
		}
		else if (m_gachaUI)
			delete m_gachaUI;
		m_gachaUI = NULL;
	}
}

void LawnApp::KillPowerPKView()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
	if (m_board)
	{
		ResumeMusic();
		m_board->Pause(false);
	}
	if (m_powerPKView)
	{
		mWidgetManager->RemoveWidget(m_powerPKView);
		mWidgetManager->RemoveBaseModal(m_powerPKView);
		SafeDeleteWidget(m_powerPKView);
		m_powerPKView = NULL;
	}
}

void LawnApp::KillCollectableAdUI()
{
	if (m_CollectableAdUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_CollectableAdUI);
		SafeDeleteWidget(m_CollectableAdUI);
		m_CollectableAdUI = NULL;
	}
}

void LawnApp::KillDailySignActivityRewardView()
{
	if (m_DailySignRewardView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_DailySignRewardView);
		SafeDeleteWidget(m_DailySignRewardView);
		m_DailySignRewardView = NULL;
	}
}

void LawnApp::KillDangerRoomSpecialOfferUI()
{
	if (m_DangerRoomSpecialOfferUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_DangerRoomSpecialOfferUI);
		SafeDeleteWidget(m_DangerRoomSpecialOfferUI);
		m_DangerRoomSpecialOfferUI = NULL;
	}
}

void LawnApp::KillExpPlantRewardView()
{
	if (m_ExpPlantRewardView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_ExpPlantRewardView);
		SafeDeleteWidget(m_ExpPlantRewardView);
		m_ExpPlantRewardView = NULL;
	}
}

void LawnApp::ShowGLDeliveryUI()
{
	if (!m_GLDeliveryUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_GLDeliveryUI = new GLDeliveryInfoWidget();
		mWidgetManager->AddWidget(m_GLDeliveryUI);
	}
	mWidgetManager->BringToFront(m_GLDeliveryUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_GLDeliveryUI);
	mWidgetManager->SetFocus(m_GLDeliveryUI);
	if (m_GLDeliveryUI)
	{
		if (m_geilivableLottery)
		{
			SexyString tel = m_geilivableLottery->GetTelSexyString();
			SexyString email = m_geilivableLottery->GetEmailSexyString();
			m_GLDeliveryUI->SetDeliveryInfo(tel, email);
			m_GLDeliveryUI->SetPrizeWinOrNot(m_geilivableLottery->GetWinOrNot());
		}
		m_GLDeliveryUI->InitView();
		m_GLDeliveryUI->NormalInit(PT_FromCenter | PT_FromMiddle | PT_Scaled | PT_Fade, 0.2f);
		m_GLDeliveryUI->StartPop();
	}
}

void LawnApp::KillGLDeliveryUI()
{
	if (m_GLDeliveryUI)
	{
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_GLDeliveryUI);
		SafeDeleteWidget(m_GLDeliveryUI);
		m_GLDeliveryUI = NULL;
	}
}

void LawnApp::ShowGLStoneLotInfoWidget()
{
	if (!m_GLGLStoneLotUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_GLGLStoneLotUI = new GLStoneLotInfoWidget();
		mWidgetManager->AddWidget(m_GLGLStoneLotUI);
	}
	mWidgetManager->BringToFront(m_GLGLStoneLotUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_GLGLStoneLotUI);
	mWidgetManager->SetFocus(m_GLGLStoneLotUI);
	if (m_GLGLStoneLotUI)
	{
		if (m_geilivableLottery)
		{
			SexyString tel = m_pStoneLottery->GetTelSexyString();
			SexyString email = m_pStoneLottery->GetEmailSexyString();
			m_GLGLStoneLotUI->SetDeliveryInfo(tel, email);
			m_GLGLStoneLotUI->SetPrizeWinOrNot(m_pStoneLottery->GetWinOrNot());
		}
		m_GLGLStoneLotUI->InitView();
		m_GLGLStoneLotUI->NormalInit(PT_FromCenter | PT_FromMiddle | PT_Scaled | PT_Fade, 0.2f);
		m_GLGLStoneLotUI->StartPop();
	}
}

void LawnApp::KillGLStoneLotInfoWidget()
{
	if (m_GLGLStoneLotUI)
	{
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_GLGLStoneLotUI);
		SafeDeleteWidget(m_GLGLStoneLotUI);
		m_GLGLStoneLotUI = NULL;
	}
}

void LawnApp::KillGemOfferHintUI()
{
	if (m_GemOfferHintUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_GemOfferHintUI);
		SafeDeleteWidget(m_GemOfferHintUI);
		m_GemOfferHintUI = NULL;
	}
}

void LawnApp::KillLostNetActivityUI()
{
	if (m_lostNetActivityUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_lostNetActivityUI);
		SafeDeleteWidget(m_lostNetActivityUI);
		m_lostNetActivityUI = NULL;
	}
}

void LawnApp::KillPlantBundleUI()
{
	if (m_PlantBundleUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_PlantBundleUI);
		SafeDeleteWidget(m_PlantBundleUI);
		m_PlantBundleUI = NULL;
	}
}

void LawnApp::KillPlantSpecialOfferUI()
{
	if (m_PlantSpecialOfferUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_PlantSpecialOfferUI);
		SafeDeleteWidget(m_PlantSpecialOfferUI);
		m_PlantSpecialOfferUI = NULL;
	}
}

void LawnApp::KillRecallOfferUI()
{
	if (m_RecallOfferUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_RecallOfferUI);
		SafeDeleteWidget(m_RecallOfferUI);
		m_RecallOfferUI = NULL;
	}
}

void LawnApp::KillRechargeRewardUI()
{
	if (m_RechargeRewardUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_RechargeRewardUI);
		SafeDeleteWidget(m_RechargeRewardUI);
		m_RechargeRewardUI = NULL;
	}
}

void LawnApp::KillSalesUI()
{
	if (m_salesUI)
	{
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_salesUI);
		SafeDeleteWidget(m_salesUI);
		m_salesUI = NULL;
	}
}

void LawnApp::KillSevenDaysRewardView()
{
	if (m_NDDailyLoginRewardView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_NDDailyLoginRewardView);
		SafeDeleteWidget(m_NDDailyLoginRewardView);
		m_NDDailyLoginRewardView = NULL;
	}
}

void LawnApp::KillShareRewardView()
{
	if (m_ShareRewardView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_ShareRewardView);
		SafeDeleteWidget(m_ShareRewardView);
		m_ShareRewardView = NULL;
	}
}

void LawnApp::KillShareWechatUI()
{
	if (m_ShareWechatUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_ShareWechatUI);
		SafeDeleteWidget(m_ShareWechatUI);
		m_ShareWechatUI = NULL;
	}
}

void LawnApp::RefreshTransGenosisUI()
{
	if (m_transGenosisUI)
	{
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_TransGenosis);
		if (item.IsValid())
		{
			TGConfig config;
			if (!item.GetDataSerialized(config))
				KillTransGenosisUI();
			else
				m_transGenosisUI->SetConfig(config);
		}
	}
}

void LawnApp::ShowTransGenosisUI(bool i_refreshByNetwork)
{
	if (!m_transGenosisUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_transGenosisUI = new TransGenosisUI();
		mWidgetManager->AddWidget(m_transGenosisUI);
	}
	mWidgetManager->BringToFront(m_transGenosisUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_transGenosisUI);
	mWidgetManager->SetFocus(m_transGenosisUI);
	if (m_transGenosisUI)
	{
		bool disabled = CheatManager::GetInstancePtr()->GetToggleValue("DisableNetworkRefresh");
		if (__builtin_expect(!!(!(i_refreshByNetwork && !disabled)), 1))
			m_transGenosisUI->ShowWindow();
		else
		{
			INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
			std::vector<std::pair<int, int>> idList = { { (int)Activity_TransGenosis, 1 } };
			if (!process->RequestActivityList(idList, 0, true))
				ShowNetworkError();
		}
	}
}

void LawnApp::KillTransGenosisUI()
{
	if (m_transGenosisUI)
	{
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_transGenosisUI);
		SafeDeleteWidget(m_transGenosisUI);
		m_transGenosisUI = NULL;
	}
}

void LawnApp::KillTwoYearBirthday()
{
	if (m_TwoYearBirthday)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_TwoYearBirthday);
		SafeDeleteWidget(m_TwoYearBirthday);
		m_TwoYearBirthday = NULL;
	}
}


void LawnApp::KillActiveEntranceUI()
{
	if (m_ActiveEntranceUI)
	{
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_ActiveEntranceUI);
		mWidgetManager->RemoveBaseModal(m_ActiveEntranceUI);
		SafeDeleteWidget(m_ActiveEntranceUI);
		m_ActiveEntranceUI = NULL;
	}
}

void LawnApp::KillDataErrorDialog()
{
	if (m_dataErrorDialog)
	{
		mWidgetManager->RemoveWidget(m_dataErrorDialog);
		mWidgetManager->RemoveBaseModal(m_dataErrorDialog);
		SafeDeleteWidget(m_dataErrorDialog);
		m_dataErrorDialog = NULL;
	}
	if (m_board)
		m_board->Pause(false);
}

void LawnApp::KillWaitingDialog()
{
	if (m_waitingdialog)
	{
		mWidgetManager->RemoveWidget(m_waitingdialog);
		mWidgetManager->RemoveBaseModal(m_waitingdialog);
		SafeDeleteWidget(m_waitingdialog);
		m_waitingdialog = NULL;
	}
	if (m_board)
		m_board->Pause(false);
}


void LawnApp::KillPvpCoinStore()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
	mWidgetManager->RemoveWidget(m_pvpCoinStore);
	mWidgetManager->RemoveBaseModal(m_pvpCoinStore);
	SafeDeleteWidget(m_pvpCoinStore);
	m_pvpCoinStore = NULL;
}

void LawnApp::KillPvpUpgrade()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
	mWidgetManager->RemoveWidget(m_pvpUpgrade);
	mWidgetManager->RemoveBaseModal(m_pvpUpgrade);
	SafeDeleteWidget(m_pvpUpgrade);
	m_pvpUpgrade = NULL;
}

void LawnApp::KillJoustLeagueInfoScreen()
{
	if (m_joustLeagueScreen)
	{
		m_joustLeagueScreen->RemoveAllWidgets();
		mWidgetManager->RemoveWidget(m_joustLeagueScreen);
		SafeDeleteWidget(m_joustLeagueScreen);
		m_joustLeagueScreen = NULL;
	}
}

void LawnApp::KillAlmanac()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Almanac_Close");
	mWidgetManager->RemoveWidget(m_almanac);
	SafeDeleteWidget(m_almanac);
	m_almanac = NULL;
}

void LawnApp::KillAwakenWidget()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Almanac_Close");
	mWidgetManager->RemoveWidget(m_awakenWidget);
	SafeDeleteWidget(m_awakenWidget);
	m_awakenWidget = NULL;
}

void LawnApp::KillNewOptionsDialog()
{
	NewOptionsDialog* dialog = m_pauseMenu;
	m_pauseMenu = NULL;
	if (dialog)
	{
		mWidgetManager->RemoveWidget(dialog);
		mWidgetManager->RemoveBaseModal(dialog);
		SafeDeleteWidget(dialog);
	}
}

void LawnApp::KillPlantAvatarListView()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
	mWidgetManager->RemoveWidget(m_plantAvatarListView);
	SafeDeleteWidget(m_plantAvatarListView);
	m_plantAvatarListView = NULL;
}

void LawnApp::KillPlantTrialView()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
	mWidgetManager->RemoveWidget(m_pPlantTrialView);
	SafeDeleteWidget(m_pPlantTrialView);
	m_pPlantTrialView = NULL;
}

void LawnApp::KillStoreUI()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
	mWidgetManager->RemoveWidget(m_storeUI);
	SafeDeleteWidget(m_storeUI);
	m_storeUI = NULL;
}


void LawnApp::KillGameMaskUI()
{
	if (m_pGameMaskUI)
	{
		mWidgetManager->BringToBack(m_pGameMaskUI);
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		m_pGameMaskUI->DoClose();
		m_pGameMaskUI = NULL;
	}
}

void LawnApp::KillBoardZombieAlmanacUI()
{
	if (m_boardZombieAlmanacUI)
	{
		mWidgetManager->RemoveWidget(m_boardZombieAlmanacUI);
		SafeDeleteWidget(m_boardZombieAlmanacUI);
	}
	m_boardZombieAlmanacUI = NULL;
}

void LawnApp::KillEndLevelUI()
{
	if (m_endLevelUI)
	{
		mWidgetManager->RemoveWidget(m_endLevelUI);
		SafeDeleteWidget(m_endLevelUI);
	}
	m_endLevelUI = NULL;
}

void LawnApp::KillGachaDisplayerDialog()
{
	if (m_gachaDisplayerDialog)
	{
		mWidgetManager->RemoveWidget(m_gachaDisplayerDialog);
		SafeDeleteWidget(m_gachaDisplayerDialog);
	}
	m_gachaDisplayerDialog = NULL;
}

void LawnApp::KillMarqueeView()
{
	if (m_marqueeView)
	{
		if (m_worldMap)
			m_worldMap->RemoveWidget(m_marqueeView);
		SafeDeleteWidget(m_marqueeView);
		m_marqueeView = NULL;
	}
}

void LawnApp::KillScrollBanner()
{
	if (m_scrollBanner)
	{
		if (m_worldMap)
			m_worldMap->RemoveWidget(m_scrollBanner);
		SafeDeleteWidget(m_scrollBanner);
		m_scrollBanner = NULL;
	}
}

void LawnApp::KillMainMenu()
{
	mWidgetManager->RemoveWidget(m_mainMenu);
	SafeDeleteWidget(m_mainMenu);
	m_mainMenu = NULL;
}

void LawnApp::KillTitleScreen()
{
	mWidgetManager->RemoveWidget(m_titleScreen);
	SafeDeleteWidget(m_titleScreen);
	m_titleScreen = NULL;
}

void LawnApp::KillOppoNewerEventUI()
{
	if (m_OppoNewerEventUI)
	{
		UISingletonDialog<OppoNewerEventUI>::CloseDialog();
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		m_OppoNewerEventUI = NULL;
	}
}

void LawnApp::ShowGeilivableLottery(bool i_refreshByNetwork)
{
	if (gLawnApp->IsChannelWithBigDeal())
	{
		if (!m_geilivableLottery)
		{
			AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
			m_geilivableLottery = new GeilivableLottery();
			mWidgetManager->AddWidget(m_geilivableLottery);
		}
		mWidgetManager->BringToFront(m_geilivableLottery);
		PushOverlaysToTop();
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
		mWidgetManager->AddBaseModal(m_geilivableLottery);
		mWidgetManager->SetFocus(m_geilivableLottery);
		if (m_geilivableLottery)
		{
			if (CheatManager::GetInstancePtr()->GetToggleValue("DisableNetworkRefresh") || !i_refreshByNetwork)
				m_geilivableLottery->ShowWindow();
			else
			{
				INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
				bool requested;
				{
					std::vector<std::pair<int, int>> idList = { { (int)Activity_Consumption_Reward, 1 } };
					requested = process->RequestActivityList(idList, 0, true);
				}
				if (!requested)
					ShowNetworkError();
			}
		}
	}
}

void LawnApp::ShowStoneLottery(bool i_refreshByNetwork)
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	if (profile)
	{
		if (!isSameDay(profile->GetLastConsumGemsTime(), ServerTime::Instance()->GetServerTime()))
			profile->ResetLotteryConsumptionGems(true);
	}
	if (!m_pStoneLottery)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_pStoneLottery = new StoneLottery();
		mWidgetManager->AddWidget(m_pStoneLottery);
	}
	mWidgetManager->BringToFront(m_pStoneLottery);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_pStoneLottery);
	mWidgetManager->SetFocus(m_pStoneLottery);
	if (m_pStoneLottery)
	{
		if (CheatManager::GetInstancePtr()->GetToggleValue("DisableNetworkRefresh") || !i_refreshByNetwork)
			m_pStoneLottery->ShowWindow();
		else
		{
			INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
			bool requested;
			{
				std::vector<std::pair<int, int>> idList = { { (int)Activity_NationdayWheelLuck2018, 1 } };
				requested = process->RequestActivityList(idList, 0, true);
			}
			if (!requested)
				ShowNetworkError();
		}
	}
}

void LawnApp::KillGeilivableLottery()
{
	LawnApp* app = gLawnApp;
	if (app->IsGLDeliveryUIValid())
		app->KillGLDeliveryUI();
	if (m_geilivableLottery)
	{
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_geilivableLottery);
		SafeDeleteWidget(m_geilivableLottery);
		m_geilivableLottery = NULL;
	}
}

void LawnApp::RefreshGeilivableLottery()
{
	if (m_geilivableLottery)
	{
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_Consumption_Reward);
		if (__builtin_expect(!!(item.IsValid()), 0))
		{
			GeilivableLotteryConfig config;
			if (gLawnApp->IsChannelWithBigDeal() && item.GetDataSerialized(config) && item.m_bOpen > ((int)config.Bonus.size() < 1))
			{
				m_geilivableLottery->SetDeliveryInfo(config.PlayerAddress.Tel, config.PlayerAddress.Email);
				m_geilivableLottery->SetPrizeWinOrNot(config.DollWon > 0);
				m_geilivableLottery->SetInitInfo(config.Period, 0, 0, 0, config.DollLeft);
				m_geilivableLottery->SetBonusList(config.Bonus);
				m_geilivableLottery->SetSourId(config.SourId);
			}
			else
			{
				std::set<int> changeList;
				m_geilivableLottery->OnNotifyRefresh(false, changeList);
			}
		}
	}
}

void LawnApp::RefreshStoneLottery()
{
	if (m_pStoneLottery)
	{
		ActiveItem item = ActivityManager::GetInstancePtr()->GetActiveItem(Activity_NationdayWheelLuck2018);
		if (__builtin_expect(!!(item.IsValid()), 0))
		{
			StoneLotteryConfig config;
			if (gLawnApp->IsChannelWithBigDeal() && item.GetDataSerialized(config) && item.m_bOpen > ((int)config.Bonus.size() < 1))
			{
				m_pStoneLottery->SetInitInfo(config.Period, config.OncePay, config.TotalChance, config.LeftChance, config.IsFirstToLottery);
				m_pStoneLottery->SetBonusList(config.Bonus);
			}
			else
			{
				std::set<int> changeList;
				m_pStoneLottery->OnNotifyRefresh(false, changeList);
			}
		}
	}
}

SexyString LawnApp::GetAboutContentStringId()
{
	int platform = gLawnApp->GetPlatform();
	if (!gLawnApp->IsServiceAvailable(Service_ShowGMInfoSettingDialog))
		return L"[SETTINGS_ABOUT_PROMPT_HUAWEI]";
	if (platform == PLATFORM_CHINA_TELECOM || (platform >= PLATFORM_TELECOM_KUPAI && platform <= PLATFORM_TELECOM_ZHONGXINGYOUXI))
		return L"[SETTINGS_ABOUT_PROMPT_TELECOM]";
	if (platform == PLATFORM_CHINA_TELECOM_HD || (platform >= PLATFORM_TELECOM_ANHUIYITUO_HD && platform <= PLATFORM_TELECOM_CHANNEL_HD_END))
		return L"[SETTINGS_ABOUT_PROMPT_TELECOM_HD]";
	if (platform >= PLATFORM_QQ && platform <= PLATFORM_QQ_HD)
		return L"[SETTINGS_ABOUT_PROMPT_QQ]";
	if (platform == PLATFORM_JINLI)
		return L"[SETTINGS_ABOUT_PROMPT_JINLI]";
	if (platform == PLATFORM_JINLI_HD)
		return L"[SETTINGS_ABOUT_PROMPT_JINLIHD]";
	return L"[SETTINGS_ABOUT_PROMPT_HD]";
}

void LawnApp::UIOrientationChanged(UI_ORIENTATION theOrientation)
{
	if (IsFullScreen())
	{
		int offset = CalcFullScreenOffset();
		if (GetWorldMap())
		{
			Lua::CUIDialog* daveShopBtn = Lua::CUIDialog::GetDialog("DaveShopBtn");
			Lua::CUIDialog* monthlyCardBtn = Lua::CUIDialog::GetDialog("MonthlyCardBtn");
			if (gLawnApp->GetUIOrientation() == gLawnApp->FullScreenUIOrientationLeft())
			{
				if (daveShopBtn)
					daveShopBtn->Move(offset + daveShopBtn->mX, daveShopBtn->mY);
				if (monthlyCardBtn)
					monthlyCardBtn->Move(offset + monthlyCardBtn->mX, monthlyCardBtn->mY);
			}
			else if (gLawnApp->GetUIOrientation() == gLawnApp->FullScreenUIOrientationRight())
			{
				if (daveShopBtn)
					daveShopBtn->Move(daveShopBtn->mX - offset, daveShopBtn->mY);
				if (monthlyCardBtn)
					monthlyCardBtn->Move(monthlyCardBtn->mX - offset, monthlyCardBtn->mY);
			}
		}
		gGameStateMgr->GetState();
	}
	gMessageRouter->Post(Message::OrientationChanged);
}

void LawnApp::ShowFakeAlert(int32 i_errorCode)
{
	SexyString message = TodStringTranslate(L"[DIA_FAKE_SAVE_WARNING]");
	message += Sexy::StrFormat(L"\n Error Code : [%d]", i_errorCode);
	std::string text = Sexy::SexyStringToUTF8String(message);
	std::string ok = Sexy::SexyStringToUTF8String(TodStringTranslate(L"[BUTTON_OK]"));
	Android::UI::ShowAlertDialog("", text, ok, false);
}

void LawnApp::KillStoneLottery()
{
	LawnApp* app = gLawnApp;
	if (app->IsGLStoneLotInfoWidget())
		app->KillGLStoneLotInfoWidget();
	if (m_pStoneLottery)
	{
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_pStoneLottery);
		SafeDeleteWidget(m_pStoneLottery);
		m_pStoneLottery = NULL;
	}
}

void LawnApp::KillCBTutorialUI()
{
	if (m_cbTutorialUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_cbTutorialUI);
		SafeDeleteWidget(m_cbTutorialUI);
		m_cbTutorialUI = NULL;
		if (m_board)
			m_board->StartLevel();
	}
}

void LawnApp::KillPlantAdventureUI()
{
	if (m_PlantAdventureUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_PlantAdventureUI);
		SafeDeleteWidget(m_PlantAdventureUI);
		m_PlantAdventureUI = NULL;
	}
	SetPlantAdventureTabIndex(-1);
}

long LawnApp::GetServerTimeOffset()
{
	return m_serverTimeOffset;
}

void LawnApp::SetServerTimeOffset(long i_offset)
{
	m_serverTimeOffset = i_offset;
	m_needFixingTime = true;
}

void LawnApp::GettingSpringGift()
{
	m_gettingSpringGift = true;
}

void LawnApp::SetHasShownSpringGiftUI()
{
	m_hasShownSpringGiftUI = true;
}

bool LawnApp::HasPlantAccessoryUI()
{
	return m_plantAccessoryUI != NULL;
}

bool LawnApp::IsRechargeRewardDisplayerValid()
{
	return m_rechargeRewardDisplayer != NULL;
}

bool LawnApp::IsShowDailySignActivityRewardView()
{
	return m_DailySignRewardView != NULL;
}

bool LawnApp::IsShowSevenDaysRewardView()
{
	return m_NDDailyLoginRewardView != NULL;
}

bool LawnApp::IsUIOrientationAllowed(UI_ORIENTATION i_orientation)
{
	return i_orientation == UI_ORIENTATION_LANDSCAPE_RIGHT || i_orientation == UI_ORIENTATION_LANDSCAPE_LEFT;
}

void LawnApp::GetOpenActivityGameUI(FestivalGameMode& eGameMode)
{
	eGameMode = m_eGameMode;
	m_eGameMode = (FestivalGameMode)-1;
}

bool LawnApp::GoldenEggHasBonus()
{
	if (m_goldenEggOpenUI)
		return m_goldenEggOpenUI->HasBonus();
}

bool LawnApp::IsTitleScreenFinished()
{
	if (m_titleScreen)
		return m_titleScreen->IsTitleScreenFinished();
}

void LawnApp::UnregisterBoardTouchGameplayObject(void* i_touchOwner)
{
	if (m_board)
		m_board->UnregisterTouchGameplayObject(i_touchOwner);
}

void LawnApp::EnableCoinStoreTutorial(bool i_enable)
{
	if (m_coinStore)
		m_coinStore->EnableTutorial(i_enable);
}

bool LawnApp::IsRedeemRewardUIValid()
{
	if (m_RedeemRewardUI)
		return m_RedeemRewardUI->mVisible;
}

bool LawnApp::IsPlatformChannel()
{
	int platform = GetPlatform();
	return (platform >= PLATFORM_91_HD && platform <= PLATFORM_THIRD_CHANNEL_HD_END) || (platform > PLATFORM_THIRD_CHANNEL_START && platform < PLATFORM_THIRD_CHANNEL_END);
}

int LawnApp::GetAndroidSDKInitStatus()
{
	if (IsDev())
		return 0;
	return m_androidSDKInitStatus;
}

int LawnApp::IsAndroidSDKInitEnd()
{
	if (IsDev())
		return 1;
	return m_androidSDKInitEnd;
}

bool LawnApp::IsPVZ2DialogExist() const
{
	return m_dialog != NULL || UISingletonDialog<UIMessageBox>::GetSingletonPtr() != NULL;
}

void LawnApp::SetFPS(bool i_highFPS)
{
	SexyAppBase::SetFPS(i_highFPS);
	m_isHighFPSMode = i_highFPS;
}

void LawnApp::DoSwitchAccessory()
{
	gLawnApp->KillPVZ2Dialog();
	m_plantAccessoryUI->DoSwitchTargetAccessory();
}

void LawnApp::onCopySaveWarningOK()
{
	KillPVZ2Dialog();
	m_bCheckCopyCompleted = true;
}

void LawnApp::URLOpenSucceeded(const std::string& theURL)
{
	SexyApp::URLOpenSucceeded(theURL);
	KillDialog(0);
}

void LawnApp::SetVersionLimit(std::string strMinVersion, std::string strMaxVersion)
{
	m_strMinVersion = strMinVersion;
	m_strMaxVersion = strMaxVersion;
}

std::string LawnApp::GetGMInfoExtraType()
{
	return m_gmInfoExtraType;
}

std::string LawnApp::GetDeviceMODEL()
{
	std::string model = GetPlatformName();
	Android::Diag::GetDeviceMODEL(model);
	return model;
}

HintUI* LawnApp::GetHintUI(int i_index)
{
	return m_hintUICollector[i_index];
}

bool LawnApp::IsHintUIValid(int i_index)
{
	return m_hintUICollector[i_index] != NULL;
}

bool LawnApp::HasPlayerUnlockedFeature(GameFeature i_featureType)
{
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	return profile && profile->GameFeatureIsUnlocked(i_featureType);
}

void LawnApp::silenceRelogin()
{
	if (m_silenceReloginTimes > 4)
		return;
	m_silenceReloginTimes++;
	ProfileMgr::GetInstance().ReloginiCloudServer();
}

void LawnApp::GenerateFonts()
{
	if (!m_isLoadingFontsLoaded)
	{
		PrimeText_Game::GenerateFontInstances();
		PrimeText_Game::GenerateFontEffects();
		m_isLoadingFontsLoaded = true;
	}
}

bool LawnApp::IsPrimeTextReady()
{
	return m_isLoadingFontsLoaded && Sexy::PrimeText::Instance() != NULL;
}

void LawnApp::HandleWwiseError()
{
	Sexy::OutputDebugStrF("LawnApp::HandleWwiseError \n");
	m_hasWwiseError = true;
}

bool LawnApp::IsDev()
{
	return GetPlatform() == PLATFORM_DEV_HD;
}

bool LawnApp::isOppoNewerOptimizationOpen()
{
	int platform = GetPlatform();
	return platform == PLATFORM_OPPO_HD || platform == PLATFORM_OPPO;
}

void LawnApp::InitAdsStatus()
{
	for (int i = 0; i < ADS_MAX; i++)
		m_adsStatus[i] = false;
}

bool LawnApp::GetAdsStatus(AdvertisementType adsType)
{
	if ((unsigned)adsType < ADS_MAX)
		return m_adsStatus[adsType];
	return false;
}

void LawnApp::SetAdsStatus(AdvertisementType adsType, bool status)
{
	if ((unsigned)adsType < ADS_MAX)
		m_adsStatus[adsType] = status;
}

void LawnApp::MuteMusic()
{
	AudioMgr::GetInstancePtr()->SendEvent("Mute_Music_Bus");
}

void LawnApp::UnmuteMusic()
{
	AudioMgr::GetInstancePtr()->SendEvent("Unmute_Music_Bus");
}

std::string LawnApp::GetDeviceType()
{
	return UserPrefs::GetDeviceType();
}

std::string LawnApp::GetPackageName(const std::string& i_defaultIOS)
{
	return Android::Util::GetPackageName();
}

void LawnApp::TouchesCanceled()
{
	CheatUIPanel::GetInstancePtr()->TouchesCanceled();
	SexyAppBase::TouchesCanceled();
}

void LawnApp::YetiEscapeRestartLevel()
{
	KillPVZ2Dialog();
	if (m_board)
		m_board->RestartLevel();
}

void LawnApp::OnQuitDangerRoomToWorldMap()
{
	KillPVZ2Dialog();
	gGameStateMgr->ShowWorldMap(GAMETRANSITION_QuickSpiral, GAMETRANSITION_QuickSpiral);
}

void LawnApp::SetMarqueeViewVisible(bool visible)
{
	if (visible)
	{
		if (!m_marqueeView)
			ShowMarqueeView();
	}
	else if (m_marqueeView)
		KillMarqueeView();
}

void LawnApp::SetScrollBannerVisible(bool visible)
{
	if (m_scrollBanner)
		m_scrollBanner->SetVisible(visible);
}

void LawnApp::WeChatShareFailed()
{
	gMessageRouter->Post(&Message::WeChatShareFailed);
}

void LawnApp::WechatShareSuccess()
{
	gMessageRouter->Post(&Message::WechatShareSuccess);
}

void LawnApp::ShowProbabilityDialog(const SexyString& alias)
{
	UISingletonDialog<ProbabilityDLG>::ShowDialog()->InitView(alias);
}

void LawnApp::OnPvpCoinBuyButtonUp(UIMessageBox* dialog, int button)
{
	UISingletonDialog<UIMessageBox>::CloseDialog();
	if (button == 1)
		ShowPvpCoinStore();
}

ImagePtr LawnApp::GetUIImageFromStringId(const std::string& i_imageName)
{
	return GetImageFromStringId(i_imageName, mHeight);
}

void LawnApp::ShowPennyFuelStore(const std::string& i_metricsContext)
{
}

static std::vector<std::string> gAlwaysLoadedGroups;

float LawnApp::InitialLoadProgress()
{
	return GetGroupLoadProgress(gAlwaysLoadedGroups);
}

void LawnApp::DeleteAlwaysLoadedGroups()
{
	DeleteGroups(gAlwaysLoadedGroups);
}

void LawnApp::KillAccessoryAwardDialog()
{
	gLawnApp->KillPVZ2Dialog();
}

bool LawnApp::CanLoadGroup(const std::string& i_groupName)
{
	return mResourceManager->GetResourceGroupNamed(i_groupName) != nullptr;
}

void LawnApp::LaunchMoreGamesWebpage()
{
	Sexy::LazySingleton<ProfileMgr>::GetInstance().GetPurchaseBroker()->LaunchMoreGamesWebpage();
}

bool LawnApp::CheckProfileOpen()
{
	return static_cast<androidNetworkMsgProcess*>(NetworkMgr::Instance()->GetNewNetWorkProcess())->CheckACLogOpen();
}

void LawnApp::FinishInitialLoad()
{
	FinalizeGroupLoads(gAlwaysLoadedGroups);
	GenerateFonts();
}

void LawnApp::ResetDatas()
{
	Sexy::LazySingleton<PVPManager>::GetInstancePtr()->Reset();
	Sexy::LazySingleton<ActivityManager>::GetInstancePtr()->Reset();
	WorldMapActionManager::ResetStaticData();
	Sexy::LazySingleton<DangerRoomManager>::GetInstancePtr()->Reset();
	Sexy::LazySingleton<WorldMapActivityBtnTurnChangeManager>::GetInstancePtr()->clear();
}

void LawnApp::ShowNetworkError()
{
	HintUI* hint = CreateHintUI();
	if (hint)
	{
		hint->DefaultUnconnectInit();
		hint->ShowHintUI();
	}
}

bool LawnApp::IsGMInfoExtraType()
{
	return !m_gmInfoExtraType.empty();
}

void LawnApp::GenerateAdsMapRate()
{
	SetAdsMapRate(m_minAdsTotalRate + Sexy::Rand(m_maxAdsTotalRate - m_minAdsTotalRate + 1));
}

void LawnApp::GotFocus()
{
	SexyAppBase::GotFocus();
	gMessageRouter->Post(&Message::AppResumeFocus);
	ResumeMusic();
}

void LawnApp::LoadingThreadProc()
{
	if (m_titleScreen)
		m_titleScreen->LoadRsbsProc();
	if (!mLoadingThreadCompleted)
		Android::Util::GetJVM()->DetachCurrentThread();
}

void LawnApp::ApplyNetworkContentChanges()
{
	if (m_networkTableManager.NetworkRequestsCompleted())
		m_networkTableManager.ApplyChanges();
}

void LawnApp::ShowStoreUI(const std::string& i_focusCategory)
{
	ServerTime::Instance()->GetServerTimeFromNet(new CServerTimeHandler_Store(i_focusCategory));
}

void LawnApp::ShowStarLevelChallengeUI(int i_index)
{
	ServerTime::Instance()->GetServerTimeFromNet(new CServerTimeHandler_Challenge(i_index));
}

void LawnApp::KillShareDialog()
{
	gLawnApp->KillPVZ2Dialog();
	if (m_board)
		m_board->Pause(false);
}

void LawnApp::KillAvatarRewardDialog()
{
	gLawnApp->KillPVZ2Dialog();
	if (m_board)
		m_board->Pause(false);
}

bool LawnApp::IsUpdateActivity(int i_activityId)
{
	return i_activityId == Activity_LimitedGacha || i_activityId == Activity_Anniversary_2nd || i_activityId == Activity_Anniversary_General || i_activityId == Activity_Plant_Special_Offer || i_activityId == Activity_SummerEvent || i_activityId == Activity_TimeTravel || i_activityId == Activity_PlantDefence;
}

bool LawnApp::GetNetworkRequestsCompleted()
{
	bool completed = false;
	if (__builtin_expect(!!(GetDoneLoadingProfiles() && m_bLoadVersionCompleted && m_bRechargeCheckCompleted), 0))
		completed = m_bCheckCopyCompleted;
	return completed;
}

void LawnApp::StopMusic(const char* i_event)
{
	m_MusicPausedCount = 0;
	m_isMusicPlaying = false;
	AudioMgr::GetInstancePtr()->SendEvent(i_event);
	Sexy::OutputDebugStrF("============= StopMusic - %s\n", i_event);
}

void LawnApp::PlayMusic(const char* i_event)
{
	m_MusicPausedCount = 0;
	m_isMusicPlaying = true;
	AudioMgr::GetInstancePtr()->SendEvent(i_event);
	Sexy::OutputDebugStrF("=============PlayMusic - %s\n", i_event);
}

void LawnApp::OnCancelQuickUnlock()
{
	KillPVZ2Dialog();
	if (m_board)
	{
		ResumeMusic();
		m_board->Pause(false);
	}
}

int LawnApp::GetStartingResolution()
{
	Sexy::Point size = GetNativeScreenSize();
	return 1200;
}

HintUI* LawnApp::CreateHintUI()
{
	HintUI* hint = new HintUI();
	mWidgetManager->AddWidget(hint);
	return hint;
}

bool LawnApp::TestCanPopWorldmapActive()
{
	if (!TestCanShowWorldmapButton())
		return false;
	if (IsStoreUIShowing())
		return false;
	return !IsSalesUIValid();
}

void LawnApp::PlayMusicCallback(const char* i_event, IInteractiveAudioCallbackListener* i_listener)
{
	m_MusicPausedCount = 0;
	m_isMusicPlaying = true;
	m_callbackEventID = AudioMgr::GetInstancePtr()->SendEventCallback(i_event, IACT_MusicSyncAll, i_listener);
}

void LawnApp::onConfirmExitGame()
{
	gMessageRouter->Post(&Message::PlayerLogout);
	gMessageRouter->Post(&Message::GameEnd);
	gLawnApp->KillPVZ2Dialog();
	Android::Device::ExitApp();
}

void LawnApp::AppEnteredBackground()
{
	BehaviorLog::pause();
	TouchesCanceled();
	Sexy::LazySingleton<SaveGameMgr>::GetInstance().TrySaveGame(false);
	gMessageRouter->Post(&Message::AppEnteredBackground);
}

void LawnApp::OnOpenSystemSettingUpdateGame()
{
	if (m_board && !m_coinStore)
	{
		ResumeMusic();
		m_board->Pause(false);
	}
	Android::Util::OpenSystemSetting();
}

void LawnApp::ShowBonus(int i_bonusId, int i_quantity)
{
	HintUI* hint = CreateHintUI();
	if (hint)
	{
		hint->BonusInit();
		hint->SetBonus(i_bonusId, i_quantity);
		hint->ShowHintUI();
	}
}

void LawnApp::KillPlantRewardDialog()
{
	gLawnApp->KillPVZ2Dialog();
	if (m_board)
		m_board->Pause(false);
	gMessageRouter->Post(&Message::NotifyExchangeFinish);
}

void LawnApp::KillPlantFamilyUI()
{
	if (m_pPlantFamilyUI)
	{
		mWidgetManager->RemoveWidget(m_pPlantFamilyUI);
		mWidgetManager->RemoveBaseModal(m_pPlantFamilyUI);
		SafeDeleteWidget(m_pPlantFamilyUI);
		m_pPlantFamilyUI = nullptr;
	}
}



bool LawnApp::CanLoadGroups(const std::vector<std::string>& i_groupNames)
{
	for (int i = 0; i < i_groupNames.size(); ++i)
	{
		if (!mResourceManager->GetResourceGroupNamed(i_groupNames[i]))
			return false;
	}
	return true;
}

void LawnApp::DeleteGroups(const std::vector<std::string>& i_groupNames)
{
	for (int i = 0; i < i_groupNames.size(); ++i)
		DeleteGroup(i_groupNames[i]);
}

void LawnApp::FinalizeGroupLoads(const std::vector<std::string>& i_groupNames)
{
	for (int i = 0; i < i_groupNames.size(); ++i)
		FinalizeGroupLoad(i_groupNames[i]);
}

void LawnApp::LoadGroups(const std::vector<std::string>& i_groupNames)
{
	for (int i = 0; i < i_groupNames.size(); ++i)
		LoadGroup(i_groupNames[i]);
}

void LawnApp::PrepareLoadGroups(const std::vector<std::string>& i_groupNames)
{
	for (int i = 0; i < i_groupNames.size(); ++i)
		PrepareLoadGroup(i_groupNames[i]);
	i_groupNames.empty();
}

void LawnApp::OnOpenSystemSetting()
{
	KillPVZ2Dialog();
	if (m_board && !m_coinStore)
	{
		ResumeMusic();
		m_board->Pause(false);
	}
	Android::Util::OpenSystemSetting();
}

void LawnApp::OnCancelStore()
{
	KillPVZ2Dialog();
	if (m_board && !m_coinStore)
	{
		ResumeMusic();
		m_board->Pause(false);
	}
}

void LawnApp::InitServerTimeOffset(long i_serverTime)
{
	long localTime = ServerTime::Instance()->GetServerTime();
	if (localTime > 0 && i_serverTime > 0)
		SetServerTimeOffset(i_serverTime - localTime);
}

void LawnApp::ButtonDepress(int i_id)
{
	int id = i_id % 10000;
	if (__builtin_expect((unsigned)(id - 2000) < 1000, 1))
		KillDialog(i_id - 2000);
	else if ((unsigned)(id - 3000) < 1000)
		KillDialog(i_id - 3000);
}

bool LawnApp::IsConnectedOnWWAN()
{
	return gSexyApp->mHttpDriver->GetNetworkStatus() == IHttpDriver::NET_REACHABLE_WWAN;
}

bool LawnApp::IsConnectOnWifi()
{
	return gSexyApp->mHttpDriver->GetNetworkStatus() == IHttpDriver::NET_REACHABLE_WIFI;
}

void LawnApp::UpdateFrames()
{
	TimeMgr::GetInstancePtr()->Update();
	SexyApp::UpdateFrames();
	DTimerManager::getInstane()->update();
	m_gameStateMgr.Update();
	ProfileMgr::GetInstance().Update();
	if (gLawnApp->IsAdActivated())
	{
		EASquared::Instance().Update();
		AbtestMgr::GetInstance().Update();
	}
	if (m_hasWwiseError)
	{
		mResourceManager->SetSoundBankInvaild();
		m_hasWwiseError = false;
	}
	NetworkMgr::Instance()->Update();
	Sexy::LazySingleton<Lua::CLuaEngine>::GetInstancePtr()->Update();
	ServerTime::Instance()->Update(0.0f);
	PVPManager::GetInstancePtr()->Update();
	ActivityManager::GetInstancePtr()->Update();
	IdentifierMgr::GetInstancePtr()->Update();
	GemOfferMgr::GetInstance().Update();
	AuthMgr::GetInstance().Update(PVZ_RealDt());
	CustomLevelMgr::GetInstance().Update(PVZ_RealDt());
	TutorialEffectMgr::GetInstance().Update();
	TGALogMgr::GetInstance().UpdateFrame();
	SocialShareMgr::GetInstance().Update();
	NewPVPMgr::GetInstancePtr()->Update();
}

bool LawnApp::IsAdActivated()
{
	return IsAdChannel(VIEW_TYPE_SCREEN) || IsAdChannel(VIEW_TYPE_MEDIA) || IsAdChannel(VIEW_TYPE_MEDIA_PARAM);
}

bool LawnApp::HasAnyServiceAvailable()
{
	return IsServiceAvailable(Service_AdsPause) || IsServiceAvailable(Service_AdsGameStart) || IsServiceAvailable(Service_AdsMap);
}

void LawnApp::TouchBegan(const Sexy::Touch& i_touch)
{
	if (!CheatUIPanel::GetInstancePtr()->TouchBegan(i_touch))
		SexyAppBase::TouchBegan(i_touch);
	Sexy::LazySingleton<CustomLevelMgr>::GetInstance().TryResetTutorialSkipTimer();
}

void LawnApp::TouchMoved(const Sexy::Touch& i_touch)
{
	if (!CheatUIPanel::GetInstancePtr()->TouchMoved(i_touch))
		SexyAppBase::TouchMoved(i_touch);
}

void LawnApp::TouchEnded(const Sexy::Touch& i_touch)
{
	m_lastTouchEndTimne = PVZ_RealT();
	if (!CheatUIPanel::GetInstancePtr()->TouchEnded(i_touch))
		SexyAppBase::TouchEnded(i_touch);
}

void LawnApp::OnConfirmQuickGemStore()
{
	KillPVZ2Dialog();
	if (m_board && !m_coinStore)
	{
		ResumeMusic();
		m_board->Pause(false);
	}
	ShowCoinStore(m_storeType);
}

std::string LawnApp::GetMapName(int index)
{
	return sMapNames[index];
}


void LawnApp::onGameCenterAuthenticationChanged(bool i_connected)
{
	if (i_connected)
		m_gcp->FetchAchievements();
}

void LawnApp::SetUsageSharingSystemStates()
{
	if (m_metricsCollector)
		m_metricsCollector->SetEnabled(!m_hasDisabledUsageSharing);
}

ResourceInfoTypes::ImageRes* LawnApp::GetImageInfoFromStringId(const std::string& i_imageName, const int i_overrideRes)
{
	int savedRes = mResourceManager->mCurArtRes;
	if (i_overrideRes)
		mResourceManager->mCurArtRes = i_overrideRes;
	ResourceInfoTypes::ImageRes* info = gLawnApp->mResourceManager->GetResInfoForStringIdT<Image>(i_imageName);
	mResourceManager->mCurArtRes = savedRes;
	return info;
}

void LawnApp::onWatchDaveShopAds(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason)
{
	if (i_reason == EASquaredAdFinishedReason::Completed)
	{
		PlayerInfo* profile = ProfileUtils::Profile();
		profile->SetCurrentDaveShopAdsRate(profile->GetCurrentDaveShopAdsRate() + 1);
	}
}

void LawnApp::TestLuaExecute()
{
	if (Sexy::LazySingleton<Lua::CLuaEngine>::GetInstance().IsDisabled())
		PopReport("Lua Engine is disabled, maybe Lua Pack not loaded");
	else
		Sexy::LazySingleton<Lua::CLuaEngine>::GetInstance().ExecuteTableFunction("luaApp", "TestExecute");
}

void LawnApp::ShareBtnCallBack()
{
	ShareInfo& info = Sexy::LazySingleton<SocialMgr>::GetInstance().m_cacheShareInfo;
	Sexy::LazySingleton<SocialMgr>::GetInstance().ShareContentToPlatform(info.shareTitle, info.shareDesc, info.shareUrl, info.shareImageUrl);
}

ImagePtr LawnApp::GetImageFromStringId(const std::string& i_imageName, const int i_overrideRes)
{
	int savedRes = mResourceManager->mCurArtRes;
	if (i_overrideRes)
		mResourceManager->mCurArtRes = i_overrideRes;
	ImagePtr image = mResourceManager->GetResourceForStringIdT<Image>(i_imageName, true);
	mResourceManager->mCurArtRes = savedRes;
	return image;
}

Image* LawnApp::GetImagePointerFromStringId(const std::string& i_imageName)
{
	return GetImageFromStringId(i_imageName, mHeight);
}

void LawnApp::ShowJoustLeagueInfoScreen()
{
	AdaptorJoustLeagueInfoScreen* screen = new AdaptorJoustLeagueInfoScreen();
	screen->LoadAndAddWidget();
	m_joustLeagueScreen = screen;
	PushOverlaysToTop();
}

void LawnApp::ShowScrollBanner()
{
	if (!m_scrollBanner)
	{
		m_scrollBanner = new WorldMap_ScrollBannerButton();
		if (m_worldMap)
		{
			m_worldMap->AddWidget(m_scrollBanner);
			m_scrollBanner->RequestNetwork();
		}
	}
}

void LawnApp::ShowMarqueeView()
{
	if (!m_marqueeView)
	{
		m_marqueeView = new WorldMap_MarqueeView();
		if (m_worldMap)
		{
			m_worldMap->AddWidget(m_marqueeView);
			m_marqueeView->RequestNetwork();
		}
	}
}

bool LawnApp::IsPlatformHD()
{
	int platform = GetPlatform();
	if (platform == PLATFORM_NULL || platform == PLATFORM_CHINA_MOBILE_HD)
		return true;
	if (platform == PLATFORM_CHINA_UNICOM_HD || platform == PLATFORM_CHINA_UNICOM_WIDEBAND_HD)
		return true;
	if (platform == PLATFORM_CHINA_MOBILE_MM_HD || platform == PLATFORM_QQ_HD)
		return true;
	if (platform > PLATFORM_THIRD_CHANNEL_HD_START && platform <= PLATFORM_THIRD_CHANNEL_HD_END)
		return true;
	return platform >= PLATFORM_TELECOM_ANHUIYITUO_HD && platform <= PLATFORM_TELECOM_CHANNEL_HD_END;
}

bool LawnApp::TestCanShowWorldmapButton()
{
	bool canShow = gGameStateMgr->GetState() == GAME_WorldMap;
	if (GetWorldMap() && GetWorldMap()->GetUniverseMap() && canShow)
		canShow = !GetWorldMap()->GetUniverseMap()->IsActived();
	return canShow;
}

int LawnApp::GetMaxSeedPacketCount()
{
	int count = 5;
	if (HasPlayerUnlockedFeature(FEATURE_UPGRADE_6_SLOTS))
		count = 6;
	if (HasPlayerUnlockedFeature(FEATURE_UPGRADE_7_SLOTS))
		count++;
	if (HasPlayerUnlockedFeature(FEATURE_UPGRADE_8_SLOTS))
		count++;
	return count;
}

bool LawnApp::KeyDown(int theKey)
{
	if (theKey == KEYCODE_GOBACK)
		return PhysicalKeyDown(theKey);
	if (!LawnApp::IsAppTopLevel())
		return false;
	return LawnApp::DebugKeyDown(theKey);
}

struct tm* LawnApp::BeijingTime(const time_t* i_time)
{
	time_t time = *i_time;
	if (time > 0)
		time += Sexy::GetBJTimeOffset();
	return gmtime(&time);
}

void LawnApp::ShowMainMenu()
{
	UIWidget::ResetUI();
	m_mainMenu = new MainMenu();
	mWidgetManager->AddWidget(m_mainMenu);
	mWidgetManager->SetFocus(m_mainMenu);
	m_mainMenu->Initialize();
	PushOverlaysToTop();
}

void LawnApp::syncProfileSummaryWithServer()
{
	if (ProfileUtils::Profile() && IsNetworkModuleOK())
	{
		if (NetworkMgr::Instance()->GetNewNetWorkProcess()->IsLogined())
			NetworkMgr::Instance()->GetNewNetWorkProcess()->ICloudRequestProfileMd5();
		else
			ProfileMgr::GetInstance().LoginiCloudServer();
	}
}

void LawnApp::GoldenEggOpenUIAddBonus(std::string i_bonusName, int i_quantity, int i_posId)
{
	if (!m_goldenEggOpenUI)
		CreateGoldenEggOpenUI();
	m_goldenEggOpenUI->AddBonus(i_bonusName, i_quantity, i_posId);
}

DangerRoomLevelType LawnApp::GetTargetDangerRoomLevelType(std::string i_name)
{
	DangerRoomLevelType type = DR_LEVEL_ONE;
	if (!(i_name == "festival_level_one"))
	{
		if (i_name == "festival_level_two")
			type = DR_LEVEL_TWO;
		else if (i_name == "festival_level_three")
			type = DR_LEVEL_THREE;
		else if (i_name == "festival_level_four")
			type = DR_LEVEL_FOUR;
		else if (i_name == "festival_level_endless")
			type = DR_LEVEL_ENDLESS;
	}
	return type;
}

void LawnApp::OnFetchVersionComplete()
{
	gMessageRouter->Unsubscribe(&Message::FetchVersionComplete, Sexy::MakeDelegate(*this, &LawnApp::OnFetchVersionComplete));
	m_bLoadVersionCompleted = true;
}

void LawnApp::OnRechargeCheckComplete()
{
	gMessageRouter->Unsubscribe(&Message::RechargeCheckOnServerComplete, Sexy::MakeDelegate(*this, &LawnApp::OnRechargeCheckComplete));
	m_bRechargeCheckCompleted = true;
}

void LawnApp::loadPlayerProfiles()
{
	std::string curUser;
	ProfileMgr& profileMgr = Sexy::LazySingleton<ProfileMgr>::GetInstance();
	profileMgr.Init();
	m_doneLoadingProfiles = false;
	gMessageRouter->Subscribe(&Message::PersistorLoadComplete, Sexy::MakeDelegate(*this, &LawnApp::onDoneLoadingProfiles));
	gMessageRouter->Post(&Message::StartPersistorLoad);
	if (RegistryReadString("CurUser", &curUser))
		profileMgr.LoadAndSetProfile(Sexy::UTF8StringToWString(curUser));
	else
		profileMgr.LoadAndSetProfile(SexyString(L""));
	RegistryReadBoolean("HasDisabledUsageSharing", &m_hasDisabledUsageSharing);
}

void LawnApp::onDoneLoadingProfiles()
{
	gMessageRouter->Unsubscribe(&Message::PersistorLoadComplete, Sexy::MakeDelegate(*this, &LawnApp::onDoneLoadingProfiles));
	m_doneLoadingProfiles = true;
}

void LawnApp::ShowGetPlantBagUI(const MagentoProductPropsPtr& prpduct, bool isRewardCoins)
{
	if (!m_GetPlantBagUI)
	{
		m_GetPlantBagUI = new GetPlantBagUI(prpduct, isRewardCoins);
		mWidgetManager->AddWidget(m_GetPlantBagUI);
	}
	mWidgetManager->BringToFront(m_GetPlantBagUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_GetPlantBagUI);
}

void LawnApp::showDiffProfileSummary()
{
	if (!m_profileSummaryComparer)
	{
		m_profileSummaryComparer = new ProfileSummaryComparer(false);
		mWidgetManager->AddWidget(m_profileSummaryComparer);
		PushOverlaysToTop();
		mWidgetManager->SetFocus(m_profileSummaryComparer);
		if (GetWorldMap())
			GetWorldMap()->SetUserInputEnabled(false);
	}
}

void LawnApp::closeDiffProfileSummary()
{
	if (m_profileSummaryComparer)
	{
		mWidgetManager->RemoveWidget(m_profileSummaryComparer);
		SafeDeleteWidget(m_profileSummaryComparer);
		m_profileSummaryComparer = NULL;
		if (GetWorldMap())
			GetWorldMap()->SetUserInputEnabled(true);
	}
}

void LawnApp::removeSpecifiedWidget(Sexy::Widget* widget, bool bBaseModal)
{
	if (widget)
	{
		mWidgetManager->RemoveWidget(widget);
		if (bBaseModal)
			mWidgetManager->RemoveBaseModal(widget);
		SafeDeleteWidget(widget);
	}
}

void LawnApp::ShowSkycityBossWarnig()
{
	if (!m_skycityBossWarningInfo)
	{
		m_skycityBossWarningInfo = new SkycityBossWarningInfo();
		mWidgetManager->AddWidget(m_skycityBossWarningInfo);
	}
	mWidgetManager->BringToFront(m_skycityBossWarningInfo);
	PushOverlaysToTop();
}

void LawnApp::PlaySample(Sexy::SoundResource* i_sound)
{
	DBG_ASSERT(false);
}

void LawnApp::PlaySample(Sexy::SoundResource* i_sound, int i_pan)
{
	DBG_ASSERT(false);
}

std::string LawnApp::GetDeviceBRAND()
{
	std::string brand = "Apple";
	Android::Diag::GetDeviceBRAND(brand);
	return brand;
}

int LawnApp::GetMaxPlantfoodCount()
{
	if (PVZ1ModeUtils::IsPlayingPVZ1Level())
		return 5;
	int count = 3;
	if (HasPlayerUnlockedFeature(FEATURE_UPGRADE_PF_SLOTS_LVL1))
		count = 4;
	if (HasPlayerUnlockedFeature(FEATURE_UPGRADE_PF_SLOTS_LVL3))
		count++;
	return count;
}

time_t LawnApp::GetRealServerTime()
{
	time_t serverTime = ServerTime::Instance()->GetServerTime();
	if (serverTime <= 0)
		return 0;
	if (IsTimeNeedFix())
		return serverTime + GetServerTimeOffset();
	return serverTime;
}

void LawnApp::PauseMusic()
{
	if (m_isMusicPlaying)
	{
		if (m_MusicPausedCount > 0)
			m_MusicPausedCount++;
		else
		{
			Sexy::OutputDebugStrF("LawnApp::PauseMusic\n");
			AudioMgr::GetInstancePtr()->SendEvent("Pause_Master_Audio_Bus");
			m_MusicPausedCount = 1;
		}
	}
	Sexy::OutputDebugStrF("LawnApp::PauseMusic m_bIsMusicPlaying=%d, m_MusicPausedCount=%d\n", m_isMusicPlaying, m_MusicPausedCount);
}

void LawnApp::ResumeMusic()
{
	if (m_isMusicPlaying)
	{
		m_MusicPausedCount--;
		if (m_MusicPausedCount == 0)
		{
			Sexy::OutputDebugStrF("LawnApp::ResumeMusic\n");
			AudioMgr::GetInstancePtr()->SendEvent("Resume_Master_Audio_Bus");
		}
	}
	Sexy::OutputDebugStrF("LawnApp::ResumeMusic m_bIsMusicPlaying=%d, m_MusicPausedCount=%d\n", m_isMusicPlaying, m_MusicPausedCount);
}

void LawnApp::LostFocus()
{
	gMessageRouter->Post(&Message::AppLostFocus);
	PauseMusic();
	SexyAppBase::LostFocus();
	mInteractiveAudioDriver->Update();
	TouchesCanceled();
}

bool LawnApp::IsNetworkModuleOK()
{
	if (IsConnectOnWifi() || IsConnectedOnWWAN())
		return true;
	return gSexyApp->mHttpDriver->GetNetworkStatus() == IHttpDriver::NET_REACHABIE_ETHERNET;
}

bool LawnApp::ShouldPopAds()
{
	LawnApp* app = gLawnApp;
	int rate = app->GetAdsMapRate();
	app->SetCurrentAdsMapRate((app->GetCurrentAdsMapRate() + 1) % rate);
	if (gLawnApp->GetCurrentAdsMapRate() % rate == 0)
	{
		SetCurrentAdsMapRate(0);
		GenerateAdsMapRate();
		return true;
	}
	return false;
}

bool LawnApp::IsChannelWithBigDeal()
{
	if (gLawnApp->GetPlatform() > PLATFORM_THIRD_CHANNEL_HD_START)
	{
		if (gLawnApp->GetPlatform() < PLATFORM_TELECOM_CHANNEL_HD_START)
			return true;
	}
	if (gLawnApp->GetPlatform() > PLATFORM_THIRD_CHANNEL_START)
	{
		if (gLawnApp->GetPlatform() < PLATFORM_THIRD_CHANNEL_END)
			return gLawnApp->GetPlatform() != PLATFORM_BUBUGAO;
	}
	return false;
}

bool LawnApp::CheckNetWork()
{
	bool connected = IsConnected();
	if (!connected)
	{
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L"[NETWORK_NOT_CONNECTED_TITLE]"), SexyString(L"[NETWORK_NOT_CONNECTED_TEXT]"));
		dialog->SetBackgroundDarken(true, 0.5f);
		dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &LawnApp::OnCancelStore)));
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_PopUp_General");
		if (m_board)
		{
			m_board->ClearCursors();
			m_board->Pause(true);
		}
	}
	return connected;
}

bool LawnApp::IsConnected()
{
	if (IsConnectOnWifi() || IsConnectedOnWWAN())
		return true;
	return gSexyApp->mHttpDriver->GetNetworkStatus() == IHttpDriver::NET_REACHABIE_ETHERNET;
}

void LawnApp::goToUpdateGame()
{
	std::string url = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetPurchaseBroker()->GetChannelUpdateUrl();
	OpenURL(url, false);
	onConfirmExitGame();
}

bool LawnApp::ShouldPopSpAds(int i_type)
{
	if (GetPlatform() == PLATFORM_OPPO_HD)
	{
		PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
		if (i_type == 0 && IsServiceAvailable(Service_AdsDaveShop))
			return profile->GetCurrentDaveShopAdsRate() < GetDaveShopAdsRate();
	}
	return false;
}

void LawnApp::LowMemoryWarning()
{
	CrashTracking::Log(Sexy::StrFormat("LawnApp::LowMemoryWarning at RealT: %.2f", PVZ_RealT()));
	Sexy::LazySingleton<SaveGameMgr>::GetInstance().TrySaveGame(false);
}

void LawnApp::DrawScreen()
{
	SexyAppBase::DrawScreen();
	Sexy::Graphics g(mWidgetManager->mImage);
	m_gameStateMgr.Draw(&g);
	Sexy::LazySingleton<TutorialEffectMgr>::GetInstance().Draw(&g);
}

void LawnApp::ShowTitleScreen()
{
	m_titleScreen = new TitleScreen();
	m_titleScreen->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(m_titleScreen);
	mWidgetManager->SetFocus(m_titleScreen);
}


static bool IsUIGroup(std::string i_groupName)
{
	if (i_groupName.substr(0, 6) == "LUA_UI")
		return true;
	if (i_groupName.substr(0, 6) == "CFDLC_")
		return i_groupName.substr(6).compare(0, 3, "UI_") == 0;
	return i_groupName.compare(0, 3, "UI_") == 0;
}

float LawnApp::GetGroupLoadProgress(const std::vector<std::string>& i_groupNames)
{
	if (mResStreamsManager && mResStreamsManager->IsInitialized("dynamic.rsb"))
	{
		uint32 total = 0;
		uint32 loaded = 0;
		for (size_t i = 0; i < i_groupNames.size(); i++)
		{
			int savedRes = mResourceManager->mCurArtRes;
			if (IsUIGroup(i_groupNames[i]))
				mResourceManager->mCurArtRes = mHeight;
			uint32 groupId = mResStreamsManager->LookupGroup(i_groupNames[i]);
			if (groupId != 0xffffffff)
			{
				int bytes = mResStreamsManager->GetBytesLoadedForGroup(groupId);
				loaded = loaded + bytes;
				bytes = mResStreamsManager->GetTotalBytesForGroup(groupId);
				total = total + bytes;
			}
			mResourceManager->mCurArtRes = savedRes;
		}
		return (float)((double)loaded / (double)total);
	}
	return 0.0f;
}

float LawnApp::GetGroupLoadProgress(const std::string& i_groupName)
{
	std::vector<std::string> groups;
	groups.push_back(i_groupName);
	return GetGroupLoadProgress(groups);
}

bool LawnApp::internalLoadGroup(const std::string& i_groupName)
{
	ResourceGroup* group = mResourceManager->GetResourceGroupNamed(i_groupName);
	if (!group)
	{
		Sexy::OutputDebugStrF("LawnApp::internalLoadGroup failed to GetResourceGroupNamed %s!", i_groupName.c_str());
		CrashTracking::Log(Sexy::StrFormat("[Resources][ERROR] Failed to find resgroup: %s", i_groupName.c_str()));
		return false;
	}
	int savedRes = mResourceManager->mCurArtRes;
	if (IsUIGroup(i_groupName))
		mResourceManager->mCurArtRes = mHeight;
	bool loaded = true;
	if (!group->mIsLoaded)
	{
		loaded = group->Load();
		if (!loaded)
		{
			Sexy::OutputDebugStrF("LawnApp::internalLoadGroup failed to ->Load group %s!", i_groupName.c_str());
			Sexy::OutputDebugStrF("LawnApp::internalLoadGroup failed error: %s!", mResourceManager->GetErrorText().c_str());
			CrashTracking::Log(Sexy::StrFormat("[Resources][ERROR] Failed to ->Load resgroup: %s", i_groupName.c_str()));
		}
	}
	mResourceManager->mCurArtRes = savedRes;
	return loaded;
}

bool LawnApp::IsGroupLoadComplete(const std::string& i_groupName)
{
	int savedRes = mResourceManager->mCurArtRes;
	if (IsUIGroup(i_groupName))
		mResourceManager->mCurArtRes = mHeight;
	float progress = 0.0f;
	bool dlcLoaded = false;
	if (mResStreamsManager->IsGroupLoaded(i_groupName) && GetGroupLoadProgress(i_groupName) >= 1.0f)
	{
		std::string dynamicName = i_groupName + "_Dynamic";
		if (!mResourceManager->GetResourceGroupNamed(dynamicName) ||
			(mResStreamsManager->IsGroupLoaded(dynamicName) && GetGroupLoadProgress(dynamicName) >= 1.0f))
		{
			std::string dlcName = "CFDLC_" + i_groupName;
			if (!mResourceManager->GetResourceGroupNamed(dlcName))
			{
				dlcLoaded = true;
				progress = 1.0f;
			}
			else
			{
				dlcLoaded = mResStreamsManager->IsGroupLoaded(dlcName);
				if (dlcLoaded)
					progress = GetGroupLoadProgress(dlcName);
			}
		}
	}
	mResourceManager->mCurArtRes = savedRes;
	if (dlcLoaded && progress >= 1.0f)
		return true;
	return !mResourceManager->GetResourceGroupNamed(i_groupName);
}

bool LawnApp::IsGroupLoadComplete(const std::vector<std::string>& i_groupNames)
{
	int i = 0;
	while (i < i_groupNames.size())
	{
		if (!IsGroupLoadComplete(i_groupNames[i++]))
			return false;
	}
	return true;
}

void LawnApp::CreateGoldenEggOpenUI()
{
	if (!m_goldenEggOpenUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_goldenEggOpenUI = new GoldenEggOpenUI();
		m_goldenEggOpenUI->InitView();
		mWidgetManager->AddWidget(m_goldenEggOpenUI);
	}
}

void LawnApp::onEASquaredAdvertisementsWillOpen()
{
	PauseMusic();
	ShowNetConnectingUI();
}

void LawnApp::ShowPennyFuelStore()
{
	ShowPennyFuelStore("");
}

PVZ2UIDialog* LawnApp::ShowPVZ2Dialog(const SexyString& i_headerText, const SexyString& i_bodyText)
{
	PVZ2UIDialog* dialog = ShowPVZ2Dialog((float)::UIScaleNum(460), (float)::UIScaleNum(300));
	dialog->SetHeaderLabel(i_headerText);
	dialog->SetFooterLabel(i_bodyText);
	return dialog;
}

PVZ2UIDialog* LawnApp::ShowPVZ2MessageDialog(const SexyString& i_headerText, const SexyString& i_bodyText)
{
	PVZ2UIDialog* dialog = ShowPVZ2Dialog(i_headerText, i_bodyText);
	dialog->AddButton(L"[DIALOG_STRING_OK]", Sexy::Delegate0(Sexy::MakeDelegate(*this, &LawnApp::KillPVZ2Dialog)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
	return dialog;
}

PVZ2UIDialog* LawnApp::ShowPVZ2DialogOneLine(const SexyString& i_headerText)
{
	PVZ2UIDialog* dialog = ShowPVZ2Dialog((float)::UIScaleNum(520), (float)::UIScaleNum(200));
	dialog->SetHeaderLabel(i_headerText);
	dialog->SetHeaderHeight(::UIScaleNum(110));
	dialog->Hide(PVZ2UIDialog::DIALOG_HIDE_FLAG_FOOTER);
	return dialog;
}

void LawnApp::OnCancelStartGameOffLine()
{
	KillPVZ2Dialog();
	if (m_board && !m_coinStore)
	{
		ResumeMusic();
		m_board->Pause(false);
	}
	gLawnApp->setSyncProfileSuccess(false);
	gMessageRouter->Post(&Message::StartGameOffLine);
}

void LawnApp::CheckForNetworkContentChanges()
{
	m_networkTableManager.CheckForUpdates();
	m_nextContentCheckTime = time(NULL) + rand() % (LiveConfig::Get().ContentRefreshMinutes / 3) * 60;
}

void LawnApp::OnConfirmGemStore()
{
	KillPVZ2Dialog();
	if (m_board && !m_coinStore)
	{
		ResumeMusic();
		m_board->Pause(false);
	}
	switch (m_storeType)
	{
	case STORE_TYPE_GEM:
		ShowCoinStore(STORE_TYPE_GEM);
		break;
	case STORE_TYPE_LEAF:
		break;
	default:
		ShowCoinStore();
		break;
	}
}

__attribute__((noinline)) static int PassThrough(int i_value)
{
	return i_value;
}

__attribute__((noinline)) static float PassThroughF(float i_value)
{
	return i_value;
}

__attribute__((noinline)) static void NoOp()
{
	__asm__ volatile("");
}

bool LawnApp::isOppoCukeTipShow()
{
	WaveManager* waveManager = m_board->GetWaveManager();
	if (waveManager)
	{
		PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
		bool hasShownTips = waveManager->getIsHasShowOppoTips();
		bool newerOptimization = gLawnApp->isOppoNewerOptimizationOpen();
		if (newerOptimization)
			return !(hasShownTips || PassThrough(profile->m_loginCount) != 2);
		return false;
	}
	return false;
}

void LawnApp::AddLocalizedLawnStringFile(const std::string& i_fileName)
{
	std::string path = mResourceManager->GetLocaleFolder(true) + i_fileName;
	TodStringListLoad(path.c_str());
}

void LawnApp::KillLoginReward()
{
	if (m_loginReward)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_loginReward);
		mWidgetManager->RemoveBaseModal(m_loginReward);
		SafeDeleteWidget(m_loginReward);
		m_loginReward = NULL;
		gMessageRouter->Post(&Message::ActionLoginRewardEnd);
	}
}

void LawnApp::KillDailySignReward()
{
	if (m_dailySignReward)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_dailySignReward);
		mWidgetManager->RemoveBaseModal(m_dailySignReward);
		SafeDeleteWidget(m_dailySignReward);
		m_dailySignReward = NULL;
		gMessageRouter->Post(&Message::ActionLoginRewardEnd);
	}
}


void LawnApp::killPlantDefenceEntrance()
{
	if (m_plantDefenceEntrance)
	{
		if (m_board)
		{
			ResumeMusic();
			m_board->Pause(false);
		}
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_plantDefenceEntrance);
		mWidgetManager->RemoveBaseModal(m_plantDefenceEntrance);
		SafeDeleteWidget(m_plantDefenceEntrance);
		m_plantDefenceEntrance = NULL;
	}
}

void LawnApp::ShowChoosePlantsDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_ChoosePlantsDialog)
		m_ChoosePlantsDialog = new WorldMapChooseDialog(eDialog_Type_Plant);
	mWidgetManager->AddWidget(m_ChoosePlantsDialog);
	mWidgetManager->BringToFront(m_ChoosePlantsDialog);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_ChoosePlantsDialog);
}

void LawnApp::ShowChooseRiddlesDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_ChooseRiddlesDialog)
		m_ChooseRiddlesDialog = new WorldMapChooseDialog(eDialog_Type_Riddles);
	mWidgetManager->AddWidget(m_ChooseRiddlesDialog);
	mWidgetManager->BringToFront(m_ChooseRiddlesDialog);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_ChooseRiddlesDialog);
}

void LawnApp::ShowChooseWelfareDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_ChooseWelfaleDialog)
		m_ChooseWelfaleDialog = new WorldMapChooseDialog(eDialog_Type_Welfare);
	mWidgetManager->AddWidget(m_ChooseWelfaleDialog);
	mWidgetManager->BringToFront(m_ChooseWelfaleDialog);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_ChooseWelfaleDialog);
}

void LawnApp::ShowChallengeChooseDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_challengeChooseDialog)
		m_challengeChooseDialog = new WorldMapChallengeChooseDialog(1);
	mWidgetManager->AddWidget(m_challengeChooseDialog);
	mWidgetManager->BringToFront(m_challengeChooseDialog);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_challengeChooseDialog);
}

void LawnApp::ShowWelfareChooseDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_welfareChooseDialog)
		m_welfareChooseDialog = new WorldMapWelfareChooseDialog(1);
	mWidgetManager->AddWidget(m_welfareChooseDialog);
	mWidgetManager->BringToFront(m_welfareChooseDialog);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_welfareChooseDialog);
}

void LawnApp::ShowShopChooseDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_shopChooseDialog)
		m_shopChooseDialog = new WorldMapShopChooseDialog(1);
	mWidgetManager->AddWidget(m_shopChooseDialog);
	mWidgetManager->BringToFront(m_shopChooseDialog);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_shopChooseDialog);
}

void LawnApp::ShowDailyActivityChooseDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_dailyActivityChooseDialog)
		m_dailyActivityChooseDialog = new WorldMapDailyActivityChooseDialog(1);
	mWidgetManager->AddWidget(m_dailyActivityChooseDialog);
	mWidgetManager->BringToFront(m_dailyActivityChooseDialog);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_dailyActivityChooseDialog);
}

void LawnApp::ShowChooseActivityLevelsDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_ChooseActivityLevelsDialog)
		m_ChooseActivityLevelsDialog = new WorldMapChooseDialog(eDialog_Type_ActivityLevel);
	mWidgetManager->AddWidget(m_ChooseActivityLevelsDialog);
	mWidgetManager->BringToFront(m_ChooseActivityLevelsDialog);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_ChooseActivityLevelsDialog);
}

void LawnApp::ShowGetGemsRestoreUI()
{
	if (!m_GetGemsRestoreUI)
	{
		m_GetGemsRestoreUI = new ::GetGemsRestoreUI();
		mWidgetManager->AddWidget(m_GetGemsRestoreUI);
	}
	mWidgetManager->BringToFront(m_GetGemsRestoreUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_GetGemsRestoreUI);
}

APP_WIDGET_IMPLEMENT(DailySignRewardWithTW)
APP_WIDGET_IMPLEMENT(CodeRewardUI)

void LawnApp::ShowRechargeBundleUI()
{
	if (m_RechargeBundleUI)
		return;
	m_RechargeBundleUI = new RechargeBundleUI();
	mWidgetManager->AddWidget(m_RechargeBundleUI);
	mWidgetManager->BringToFront(m_RechargeBundleUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_RechargeBundleUI);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_RechargeBundleUI);
}

void LawnApp::KillRechargeBundleUI()
{
	if (m_RechargeBundleUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		gMessageRouter->Post(&Message::ActivePopupUIClosed);
		mWidgetManager->RemoveWidget(m_RechargeBundleUI);
		SafeDeleteWidget(m_RechargeBundleUI);
		m_RechargeBundleUI = nullptr;
	}
}

void LawnApp::ShowActivityHomeExtra()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_activityHomeExtra)
		m_activityHomeExtra = new WorldMapActivityHomeExtra(1);
	mWidgetManager->AddWidget(m_activityHomeExtra);
	mWidgetManager->BringToFront(m_activityHomeExtra);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_activityHomeExtra);
}

void LawnApp::ShowServerBoxOpenUI()
{
	if (m_serverBoxOpenUI)
		KillServerBoxOpenUI();
	m_serverBoxOpenUI = new ServerBoxOpenUI();
	m_serverBoxOpenUI->ResetAnimName();
	m_serverBoxOpenUI->InitView();
	mWidgetManager->AddWidget(m_serverBoxOpenUI);
	mWidgetManager->BringToFront(m_serverBoxOpenUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_serverBoxOpenUI);
	mWidgetManager->SetFocus(m_serverBoxOpenUI);
}

void LawnApp::ShowServerBoxOpenUI(const std::map<int, int>& i_prizePool, SexyString i_title)
{
	ShowServerBoxOpenUI();
	m_serverBoxOpenUI->SetContentList(i_prizePool);
	m_serverBoxOpenUI->SetTitle(i_title);
	m_serverBoxOpenUI->StartPlayingAnimation();
}

void LawnApp::ShowPlantOfferOpenUI()
{
	if (m_plantOfferOpenUI)
		KillPlantOfferOpenUI();
	m_plantOfferOpenUI = new PlantOfferOpenUI();
	m_plantOfferOpenUI->ResetAnimName();
	m_plantOfferOpenUI->InitView();
	mWidgetManager->AddWidget(m_plantOfferOpenUI);
	mWidgetManager->BringToFront(m_plantOfferOpenUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_plantOfferOpenUI);
	mWidgetManager->SetFocus(m_plantOfferOpenUI);
}

void LawnApp::ShowPlantOfferOpenUI(const std::map<int, int>& i_prizePool, SexyString i_title)
{
	ShowPlantOfferOpenUI();
	m_plantOfferOpenUI->SetContentList(i_prizePool);
	m_plantOfferOpenUI->SetTitle(i_title);
	m_plantOfferOpenUI->StartPlayingAnimation();
}

void LawnApp::ShowNewPlayerCollection()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_newPlayerCollection)
	{
		m_newPlayerCollection = new UINewPlayerCollection();
		m_newPlayerCollection->Init();
	}
	mWidgetManager->AddWidget(m_newPlayerCollection);
	mWidgetManager->BringToFront(m_newPlayerCollection);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_newPlayerCollection);
}

void LawnApp::ShowGetNewerBagUI(bool i_ignoreCode, bool i_Newer)
{
	if (!m_GetNewerBagUI)
	{
		m_GetNewerBagUI = new ::GetNewerBagUI(i_ignoreCode, i_Newer);
		mWidgetManager->AddWidget(m_GetNewerBagUI);
	}
	mWidgetManager->BringToFront(m_GetNewerBagUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_GetNewerBagUI);
}

void LawnApp::ShowActiveEntranceUI(ActiveEntranceType i_type)
{
	if (m_ActiveEntranceUI)
		KillActiveEntranceUI();
	m_ActiveEntranceUI = new ActiveEntranceUI(i_type);
	mWidgetManager->AddWidget(m_ActiveEntranceUI);
	mWidgetManager->BringToFront(m_ActiveEntranceUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_ActiveEntranceUI);
	mWidgetManager->SetFocus(m_ActiveEntranceUI);
}

void LawnApp::ShowRedPackOpenUI(int i_redPackOpenNum)
{
	if (m_redPackOpenUI)
		KillRedPackOpenUI();
	m_redPackOpenUI = new RedPackOpenUI(i_redPackOpenNum);
	mWidgetManager->AddWidget(m_redPackOpenUI);
	mWidgetManager->BringToFront(m_redPackOpenUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_redPackOpenUI);
	mWidgetManager->SetFocus(m_redPackOpenUI);
}

void LawnApp::ShowHintUI(int i_index)
{
	if (!IsHintUIValid(i_index))
		return;
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	mWidgetManager->BringToFront(GetHintUI(i_index));
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(GetHintUI(i_index));
	mWidgetManager->SetFocus(GetHintUI(i_index));
	GetHintUI(i_index)->ShowHintUI();
}

void LawnApp::KillHintUI(int i_index)
{
	if (IsHintUIValid(i_index))
	{
		HintUI* hintUI = GetHintUI(i_index);
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(hintUI);
		SafeDeleteWidget(hintUI);
		m_hintUICollector[i_index] = nullptr;
	}
}

int LawnApp::GetNewHintUIIndex(HintUI* i_UI)
{
	for (int i = 0; i < 1000; i++)
	{
		if (!IsHintUIValid(i))
		{
			m_hintUICollector[i] = i_UI;
			return i;
		}
	}
	SafeDeleteWidget(i_UI);
	return -1;
}

void LawnApp::ShowGemOfferHintUI()
{
	if (m_GemOfferHintUI)
		return;
	m_GemOfferHintUI = new GemOfferHintUI();
	mWidgetManager->AddWidget(m_GemOfferHintUI);
	mWidgetManager->BringToFront(m_GemOfferHintUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_GemOfferHintUI);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_GemOfferHintUI);
}

bool LawnApp::IsNormalWorld(std::string i_world)
{
	for (int i = 0; i < GetAllMapCount(); i++)
	{
		if (i_world == GetMapName(i))
			return true;
	}
	return false;
}

bool LawnApp::IsCurrentNormalWorld()
{
	if (GetWorldMap())
	{
		WorldData* world = GetWorldMap()->GetCurrentWorld();
		if (world)
			return IsNormalWorld(world->m_worldName);
	}
	return false;
}

void LawnApp::ShowCustomLevelView()
{
	if (!m_customLevelView)
	{
		m_customLevelView = new CustomLevelView();
		m_customLevelView->InitView();
		mWidgetManager->AddWidget(m_customLevelView);
	}
	mWidgetManager->BringToFront(m_customLevelView);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_customLevelView);
	m_customLevelView->CheckUploadedLevels();
}

void LawnApp::killTimeTravelEntranceUI()
{
	if (m_timeTravelEntranceUI)
	{
		if (m_board)
		{
			ResumeMusic();
			m_board->Pause(false);
		}
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_timeTravelEntranceUI);
		mWidgetManager->RemoveBaseModal(m_timeTravelEntranceUI);
		SafeDeleteWidget(m_timeTravelEntranceUI);
		m_timeTravelEntranceUI = NULL;
	}
}

void LawnApp::killSummerEventEntranceUI()
{
	if (m_summerEventEntranceUI)
	{
		if (m_board)
		{
			ResumeMusic();
			m_board->Pause(false);
		}
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Close");
		mWidgetManager->RemoveWidget(m_summerEventEntranceUI);
		mWidgetManager->RemoveBaseModal(m_summerEventEntranceUI);
		SafeDeleteWidget(m_summerEventEntranceUI);
		m_summerEventEntranceUI = NULL;
	}
}

void LawnApp::GotoNewWorld()
{
	std::string levelName = m_newLevelToJump;
	KillNewWorldDialog();
	if (levelName != "")
		m_worldMap->SwitchToGameLevel(levelName, LEVELSOURCE_Arcade, true);
}

void LawnApp::ShowPVPMapUI()
{
	if (!m_pvpMapUI)
	{
		m_pvpMapUI = new PVPMapUI();
		mWidgetManager->AddWidget(m_pvpMapUI);
		mWidgetManager->BringToFront(m_pvpMapUI);
		PushOverlaysToTop();
	}
	mWidgetManager->SetFocus(m_pvpMapUI);
}

ActivityConfig* LawnApp::GetActivityConfig()
{
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_ACTIVITY_CONFIG);
	return table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("ActivityConfig"))))->CastChecked<ActivityConfig>();
}

GachaConfig* LawnApp::GetGachaConfig()
{
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_GACHA_CONFIG);
	return table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("GachaConfig"))))->CastChecked<GachaConfig>();
}

TreasureConfig* LawnApp::GetTreasureConfig()
{
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_TREASURE_CONFIG);
	return table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("TreasureConfig"))))->CastChecked<TreasureConfig>();
}

TreasureConfig* LawnApp::GetPedTreasureConfig()
{
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PEDTREASURE_CONFIG);
	return table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("PedTreasureConfig"))))->CastChecked<TreasureConfig>();
}

StoreGiftConfig* LawnApp::GetStoreGiftConfig()
{
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_STORE_GIFT_CONFIG);
	return table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("StoreGiftConfig"))))->CastChecked<StoreGiftConfig>();
}

void LawnApp::ShowRechargeRewardDisplayer(RechargeNode i_node)
{
	if (!m_rechargeRewardDisplayer)
	{
		m_rechargeRewardDisplayer = new RechargeRewardDisplayer(i_node);
		mWidgetManager->AddWidget(m_rechargeRewardDisplayer);
	}
	mWidgetManager->BringToFront(m_rechargeRewardDisplayer);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_rechargeRewardDisplayer);
}

void LawnApp::ShowRechargeRewardDisplayer(bool i_activityReward, int i_gemCount)
{
	if (!m_rechargeRewardDisplayer)
	{
		m_rechargeRewardDisplayer = new RechargeRewardDisplayer(i_activityReward, i_gemCount);
		mWidgetManager->AddWidget(m_rechargeRewardDisplayer);
	}
	mWidgetManager->BringToFront(m_rechargeRewardDisplayer);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_rechargeRewardDisplayer);
}

void LawnApp::ShowNetConnectingUI(const std::string& i_tip)
{
	KillNetConnectingUI();
	if (!m_netConnectingUI)
	{
		m_netConnectingUI = new NetConnectingUI(i_tip);
		mWidgetManager->AddWidget(m_netConnectingUI);
	}
	mWidgetManager->BringToFront(m_netConnectingUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_netConnectingUI);
}

void LawnApp::ShowGoldenEggOpenUI()
{
	mWidgetManager->BringToFront(m_goldenEggOpenUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_goldenEggOpenUI);
	mWidgetManager->SetFocus(m_goldenEggOpenUI);
	if (m_goldenEggOpenUI)
		m_goldenEggOpenUI->SetVisible(true);
	gMessageRouter->Post(&Message::OpenUI, "GoldenEggOpenUI");
}

void LawnApp::ShowPVPZombieLevelUpDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_pPVPZombieLevelUpDialog)
		KillPVPZombieLevelUpDialog();
	m_pPVPZombieLevelUpDialog = new PVPZombieLevelUpDlg();
	mWidgetManager->AddWidget(m_pPVPZombieLevelUpDialog);
	mWidgetManager->BringToFront(m_pPVPZombieLevelUpDialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_pPVPZombieLevelUpDialog);
	mWidgetManager->SetFocus(m_pPVPZombieLevelUpDialog);
}

void LawnApp::ShowConsumptionRewardDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_pConsumptionRewardDialog)
		KillConsumptionRewardDialog();
	m_pConsumptionRewardDialog = new ConsumptionRewardDialog();
	mWidgetManager->AddWidget(m_pConsumptionRewardDialog);
	mWidgetManager->BringToFront(m_pConsumptionRewardDialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_pConsumptionRewardDialog);
	mWidgetManager->SetFocus(m_pConsumptionRewardDialog);
}

void LawnApp::ShowLevelOfTheDayRewardDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_pLevelOfTheDayRewardDialog)
		KillLevelOfTheDayRewardDialog();
	m_pLevelOfTheDayRewardDialog = new LevelOfTheDayRewardDialog();
	mWidgetManager->AddWidget(m_pLevelOfTheDayRewardDialog);
	mWidgetManager->BringToFront(m_pLevelOfTheDayRewardDialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_pLevelOfTheDayRewardDialog);
	mWidgetManager->SetFocus(m_pLevelOfTheDayRewardDialog);
}

void LawnApp::ShowLevelOfTheDayProgressiveAwardDialog()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_pLevelOfTheDay_ProgressiveAwardDialog)
		KillLevelOfTheDayProgressiveAwardDialog();
	m_pLevelOfTheDay_ProgressiveAwardDialog = new LevelOfTheDay_ProgressiveAwardDialog();
	mWidgetManager->AddWidget(m_pLevelOfTheDay_ProgressiveAwardDialog);
	mWidgetManager->BringToFront(m_pLevelOfTheDay_ProgressiveAwardDialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_pLevelOfTheDay_ProgressiveAwardDialog);
	mWidgetManager->SetFocus(m_pLevelOfTheDay_ProgressiveAwardDialog);
}

void LawnApp::ShowWorldPreview(const std::string& i_worldName)
{
	if (m_universeWorldInfo)
		return;
	m_universeWorldInfo = new UniverseWorldInfo(i_worldName);
	mWidgetManager->AddWidget(m_universeWorldInfo);
	mWidgetManager->BringToFront(m_universeWorldInfo);
	mWidgetManager->AddBaseModal(m_universeWorldInfo);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_universeWorldInfo);
}

void LawnApp::ShowPlantBundleUI()
{
	if (m_PlantBundleUI)
		return;
	m_PlantBundleUI = new PlantBundleUI();
	mWidgetManager->AddWidget(m_PlantBundleUI);
	mWidgetManager->BringToFront(m_PlantBundleUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_PlantBundleUI);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_PlantBundleUI);
}

void LawnApp::ShowShareWechatUI()
{
	if (m_ShareWechatUI)
		return;
	m_ShareWechatUI = new ShareWechatUI();
	mWidgetManager->AddWidget(m_ShareWechatUI);
	mWidgetManager->BringToFront(m_ShareWechatUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_ShareWechatUI);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_ShareWechatUI);
}

void LawnApp::ShowTwoYearBirthday()
{
	if (m_TwoYearBirthday)
		return;
	m_TwoYearBirthday = new TwoYearBirthday();
	mWidgetManager->AddWidget(m_TwoYearBirthday);
	mWidgetManager->BringToFront(m_TwoYearBirthday);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_TwoYearBirthday);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_TwoYearBirthday);
}

void LawnApp::ShowRechargeRewardUI()
{
	if (m_RechargeRewardUI)
		return;
	m_RechargeRewardUI = new RechargeRewardUI();
	mWidgetManager->AddWidget(m_RechargeRewardUI);
	mWidgetManager->BringToFront(m_RechargeRewardUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_RechargeRewardUI);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_RechargeRewardUI);
}

void LawnApp::ShowRecallOfferUI()
{
	if (m_RecallOfferUI)
		return;
	m_RecallOfferUI = new RecallOfferUI();
	mWidgetManager->AddWidget(m_RecallOfferUI);
	mWidgetManager->BringToFront(m_RecallOfferUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_RecallOfferUI);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_RecallOfferUI);
	m_RecallOfferUI->RefreshActivity();
}

void LawnApp::ShowPlantFamilyUI(int i_type)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_pPlantFamilyUI)
		m_pPlantFamilyUI = new PlantFamilyUI(i_type);
	mWidgetManager->AddWidget(m_pPlantFamilyUI);
	mWidgetManager->BringToFront(m_pPlantFamilyUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_pPlantFamilyUI);
	mWidgetManager->SetFocus(m_pPlantFamilyUI);
}

void LawnApp::ShowNostalgiaPVZGameView()
{
	if (!m_nostalgiaPVZGameView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_Music_Anniversary");
		m_nostalgiaPVZGameView = new NostalgiaPVZGameView();
		m_nostalgiaPVZGameView->InitView();
		mWidgetManager->AddWidget(m_nostalgiaPVZGameView);
	}
	mWidgetManager->BringToFront(m_nostalgiaPVZGameView);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_nostalgiaPVZGameView);
	m_nostalgiaPVZGameView->TriggerTutorial();
}

void LawnApp::ShowAdventureBonusUI(int i_dungeonId, SexyString i_dungeonName)
{
	if (!m_AdventureBonusUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_AdventureBonusUI = new AdventureBonusUI(i_dungeonId, i_dungeonName);
		mWidgetManager->AddWidget(m_AdventureBonusUI);
	}
	m_AdventureBonusUI->SetVisible(true);
	mWidgetManager->BringToFront(m_AdventureBonusUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_AdventureBonusUI);
	mWidgetManager->SetFocus(m_AdventureBonusUI);
	gMessageRouter->Post(&Message::OpenUI, "AdventureBonusUI");
}

void LawnApp::ShowAdventureBonusUI()
{
	if (m_AdventureBonusUI)
	{
		m_AdventureBonusUI->SetVisible(true);
		mWidgetManager->BringToFront(m_AdventureBonusUI);
		PushOverlaysToTop();
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
		mWidgetManager->AddBaseModal(m_AdventureBonusUI);
		mWidgetManager->SetFocus(m_AdventureBonusUI);
		gMessageRouter->Post(&Message::OpenUI, "AdventureBonusUI");
	}
}

void LawnApp::ShowSalesUI()
{
	PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	if (profile)
	{
		bool valid = true;
		{
			CurrentSalesInfo info = profile->GetCurrentSalesInfo();
			if (!info.opening)
				valid = profile->HasValidSales();
		}
		if (!valid)
			return;
	}
	if (!m_salesUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_salesUI = new SalesUI();
		m_salesUI->Init();
		mWidgetManager->AddWidget(m_salesUI);
	}
	mWidgetManager->BringToFront(m_salesUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_salesUI);
	mWidgetManager->SetFocus(m_salesUI);
	gMessageRouter->Post(&Message::SummerActivity, "TimeLimited_Sales");
	if (m_salesUI)
	{
		m_salesUI->NormalInit(PT_FromCenter | PT_FromMiddle | PT_Scaled | PT_Fade, 0.3f);
		m_salesUI->StartPop();
	}
}

void LawnApp::ShowRedPackUI(FestivalEventType i_type)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_redPackUI)
		KillRedPackUI();
	m_redPackUI = new RedPackUI(i_type);
	mWidgetManager->AddWidget(m_redPackUI);
	mWidgetManager->BringToFront(m_redPackUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_redPackUI);
	mWidgetManager->SetFocus(m_redPackUI);
}

void LawnApp::ShowLanternRiddlesUI(bool i_canRiddle)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_lanternRiddlesUI)
		KillLanternRiddlesUI();
	m_lanternRiddlesUI = new LanternRiddlesUI(i_canRiddle);
	mWidgetManager->AddWidget(m_lanternRiddlesUI);
	mWidgetManager->BringToFront(m_lanternRiddlesUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_lanternRiddlesUI);
	mWidgetManager->SetFocus(m_lanternRiddlesUI);
}

bool LawnApp::ShowDailySignReward(bool i_action)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_dailySignReward)
		KillDailySignReward();
	m_dailySignReward = new DailySignReward(i_action);
	mWidgetManager->AddWidget(m_dailySignReward);
	mWidgetManager->BringToFront(m_dailySignReward);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_dailySignReward);
	mWidgetManager->SetFocus(m_dailySignReward);
	return true;
}

void LawnApp::ShowEndLevelUI()
{
	if (m_endLevelUI)
	{
		mWidgetManager->SetFocus(m_endLevelUI);
		return;
	}
	m_endLevelUI = new EndLevelUI();
	m_endLevelUI->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(m_endLevelUI);
	mWidgetManager->BringToFront(m_endLevelUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_endLevelUI);
}

PVZ2UILotteryResult* LawnApp::ShowLotteryResultUI()
{
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	if (!m_lotteryResultUI)
		m_lotteryResultUI = new PVZ2UILotteryResult(mWidth, mHeight);
	mWidgetManager->AddWidget(m_lotteryResultUI);
	mWidgetManager->BringToFront(m_lotteryResultUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_lotteryResultUI);
	mWidgetManager->SetFocus(m_lotteryResultUI);
	return m_lotteryResultUI;
}

void LawnApp::ShowStoreUINow(const std::string& i_focusPanel)
{
	if (!m_storeUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_storeUI = new StoreUI(i_focusPanel);
		mWidgetManager->AddWidget(m_storeUI);
	}
	else
		m_storeUI->ShowPanel(i_focusPanel);
	mWidgetManager->BringToFront(m_storeUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_storeUI);
}

void LawnApp::ShowLotteryUI(bool i_canDoLottery)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (!m_LotteryUI)
		m_LotteryUI = new LotteryUI(i_canDoLottery);
	mWidgetManager->AddWidget(m_LotteryUI);
	mWidgetManager->BringToFront(m_LotteryUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_LotteryUI);
	mWidgetManager->SetFocus(m_LotteryUI);
}

void LawnApp::ShowOpenSurpriseBoxUI(const std::string& i_anim)
{
	if (m_surpriseBoxOpenUI)
		KillOpenSurpriseBoxUI();
	m_surpriseBoxOpenUI = new OpenSurpriseUI(i_anim);
	if (m_surpriseBoxOpenUI)
	{
		m_surpriseBoxOpenUI->ResetAnimName();
		m_surpriseBoxOpenUI->InitView();
		mWidgetManager->AddWidget(m_surpriseBoxOpenUI);
		mWidgetManager->BringToFront(m_surpriseBoxOpenUI);
		PushOverlaysToTop();
	}
	mWidgetManager->AddBaseModal(m_surpriseBoxOpenUI);
	mWidgetManager->SetFocus(m_surpriseBoxOpenUI);
}

void LawnApp::ShowRechargeGiftUI(const std::string& name)
{
	if (!m_RechargeGiftUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_RechargeGiftUI = new RechargeGiftUI(name);
		mWidgetManager->AddWidget(m_RechargeGiftUI);
	}
	mWidgetManager->BringToFront(m_RechargeGiftUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_RechargeGiftUI);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_RechargeGiftUI);
	mWidgetManager->SetFocus(m_RechargeGiftUI);
	gMessageRouter->Post(&Message::OpenUI, "RechargeGift");
}

void LawnApp::ShowChristmasLotteryReward(std::string i_plantName, bool i_IsPlant, int i_nRewardNum)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_pChristmasLotteryReward)
		m_pChristmasLotteryReward = new ChristmasLotteryReward(i_plantName, i_IsPlant, i_nRewardNum);
	mWidgetManager->AddWidget(m_pChristmasLotteryReward);
	mWidgetManager->BringToFront(m_pChristmasLotteryReward);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_pChristmasLotteryReward);
	mWidgetManager->SetFocus(m_pChristmasLotteryReward);
}

void LawnApp::ShowBoxOpenUI(const std::string& i_type)
{
	if (m_boxOpenUI)
		KillBoxOpenUI();
	m_boxOpenUI = new BoxOpenUI(i_type);
	m_boxOpenUI->ResetAnimName();
	m_boxOpenUI->InitView();
	mWidgetManager->AddWidget(m_boxOpenUI);
	mWidgetManager->BringToFront(m_boxOpenUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_boxOpenUI);
	mWidgetManager->SetFocus(m_boxOpenUI);
}

ShareRewardView* LawnApp::ShowShareRewardView()
{
	if (m_ShareRewardView)
		return m_ShareRewardView;
	m_ShareRewardView = new ShareRewardView();
	mWidgetManager->AddWidget(m_ShareRewardView);
	mWidgetManager->BringToFront(m_ShareRewardView);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_ShareRewardView);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_ShareRewardView);
	return m_ShareRewardView;
}

void LawnApp::ShowExpPlantRewardView(const std::string& i_plantName)
{
	if (m_ExpPlantRewardView)
		return;
	m_ExpPlantRewardView = new ExpPlantRewardView(i_plantName);
	mWidgetManager->AddWidget(m_ExpPlantRewardView);
	mWidgetManager->BringToFront(m_ExpPlantRewardView);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_ExpPlantRewardView);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_ExpPlantRewardView);
}

void LawnApp::ShowCollectableAdUI()
{
	if (m_CollectableAdUI)
		return;
	m_CollectableAdUI = new CollectableAdUI();
	mWidgetManager->AddWidget(m_CollectableAdUI);
	mWidgetManager->BringToFront(m_CollectableAdUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_CollectableAdUI);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_CollectableAdUI);
	m_CollectableAdUI->RefreshActivity(CollectableAdBoxMgr::GetInstance().GetReward());
}

void LawnApp::ShowPlantAvatarListView()
{
	if (!m_plantAvatarListView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_plantAvatarListView = new PlantAvatarListView();
		mWidgetManager->AddWidget(m_plantAvatarListView);
	}
	mWidgetManager->BringToFront(m_plantAvatarListView);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_plantAvatarListView);
	m_plantAvatarListView->TriggerTutorial();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
}

void LawnApp::ShowArtifactCultivationListView()
{
	if (!m_artifactCultivationListView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_artifactCultivationListView = new ArtifactCultivationListView();
		mWidgetManager->AddWidget(m_artifactCultivationListView);
	}
	mWidgetManager->BringToFront(m_artifactCultivationListView);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_artifactCultivationListView);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
}

void LawnApp::Init()
{
	Init(InitReason_FirstInit);
}

bool LawnApp::IsInWatchADBlackList(const std::string packageName)
{
	return std::find(m_watchADBlackList.begin(), m_watchADBlackList.end(), packageName) != m_watchADBlackList.end();
}

void LawnApp::StartInitialLoad()
{
	PrepareLoadGroups(gAlwaysLoadedGroups);
	Sexy::Locale::SetSeperators(TodStringTranslate(L"[NUMBER_FORMAT_SEPARATOR_COUNT]"), TodStringTranslate(L"[NUMBER_FORMAT_SEPARATOR]"));
}

std::string LawnApp::GetNetworkType()
{
	std::string networkType;
	if (IsConnectOnWifi())
		networkType = "WIFI";
	else
		networkType = Android::Diag::GetNetworkType();
	return networkType;
}

bool LawnApp::IsFitVersionLimit() const
{
	if (!IsServiceAvailable(Service_LimitVersion))
		return true;
	int versionCode = Android::Info::SysGetProductVersionCode();
	if (!m_strMinVersion.empty() && Version2Int(m_strMinVersion) > versionCode)
		return false;
	if (!m_strMaxVersion.empty() && Version2Int(m_strMaxVersion) < versionCode)
		return false;
	return true;
}

void LawnApp::LoadLocalLawnStrings()
{
	std::string path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "pvz2_l.txt";
	if (FileExists(path))
		TodStringListLoad(path.c_str());
}

void LawnApp::showSpecifiedWidget(Sexy::Widget* widget, bool bFocus, bool bBaseModal)
{
	if (widget)
	{
		mWidgetManager->AddWidget(widget);
		mWidgetManager->BringToFront(widget);
		PushOverlaysToTop();
		if (bBaseModal)
			mWidgetManager->AddBaseModal(widget);
		if (bFocus)
			mWidgetManager->SetFocus(widget);
	}
}

int LawnApp::GetMapNameIndex(std::string world)
{
	for (int i = 0; i < GetAllMapCount(); i++)
	{
		if (world == GetMapName(i))
			return i;
	}
	return -1;
}

Sexy::Dialog* LawnApp::NewDialog(int i_dialogId, bool isModal, const SexyString& i_dialogHeader, const SexyString& i_dialogLines, const SexyString& i_dialogFooter, int i_buttonMode)
{
	LawnDialog* dialog = new LawnDialog(i_dialogId, isModal, i_dialogHeader, i_dialogLines, i_dialogFooter, i_buttonMode);
	dialog->Resize((gLawnApp->mWidth - dialog->mWidth) / 2, (gLawnApp->mHeight - dialog->mHeight) / 2, dialog->mWidth, dialog->mHeight);
	return dialog;
}

void LawnApp::ShowDailyAchievement()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_dailyAchievement)
		KillDailyAchievement();
	m_dailyAchievement = new DailyAchievement();
	mWidgetManager->AddWidget(m_dailyAchievement);
	mWidgetManager->BringToFront(m_dailyAchievement);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_dailyAchievement);
	mWidgetManager->SetFocus(m_dailyAchievement);
}

void LawnApp::ShowLoginReward()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_loginReward)
		KillLoginReward();
	m_loginReward = new LoginReward();
	mWidgetManager->AddWidget(m_loginReward);
	mWidgetManager->BringToFront(m_loginReward);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_loginReward);
	mWidgetManager->SetFocus(m_loginReward);
}

void LawnApp::ShowWorldUnlock(const std::string& i_worldName)
{
	if (m_worldUnlock)
		return;
	m_worldUnlock = new PVZ2UIUnlockPreview();
	m_worldUnlock->SetupForWorldNamed(i_worldName);
	mWidgetManager->AddWidget(m_worldUnlock);
	mWidgetManager->BringToFront(m_worldUnlock);
	mWidgetManager->AddBaseModal(m_worldUnlock);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_worldUnlock);
}

void LawnApp::VersionForceUpdate()
{
	if (m_versionNetworkManager.GetUpdateUrl() != "")
		OpenURL(m_versionNetworkManager.GetUpdateUrl(), false);
}

void LawnApp::WaitingGemCallBack(bool i_Success)
{
	if (mWaitingServerGemCallBack != NULL)
		mWaitingServerGemCallBack(i_Success);
	mWaitingServerGemCallBack = NULL;
	if (m_waitingdialog)
	{
		if (i_Success)
			KillWaitingDialog();
		else
			m_waitingdialog->SetError();
	}
}

void LawnApp::ShowPlantTrialView(const std::string strPlantName)
{
	if (!m_pPlantTrialView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_pPlantTrialView = new PlantTrialViewUI(strPlantName);
		mWidgetManager->AddWidget(m_pPlantTrialView);
	}
	mWidgetManager->BringToFront(m_pPlantTrialView);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_pPlantTrialView);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
}

bool LawnApp::IsNationalDay(bool i_canUseLocalTime)
{
	time_t now = GetRealBeijingTime();
	if (now <= 0)
	{
		if (!i_canUseLocalTime)
			return false;
		now = Sexy::SexyTime() / 1000;
	}
	struct tm* date = gLawnApp->BeijingTime(&now);
	if (date->tm_year == 113 && date->tm_mon == 9 && date->tm_mday >= 1 && date->tm_mday <= 7)
		return true;
	return false;
}

bool LawnApp::IsQQAndSingleDay()
{
	time_t now = gLawnApp->GetRealBeijingTime();
	if (now > 0)
	{
		struct tm* date = gLawnApp->BeijingTime(&now);
		if (date->tm_year == 113 && date->tm_mon == 10 && (unsigned)(date->tm_mday - 8) < 8)
		{
			if (gLawnApp->GetPlatform() == PLATFORM_QQ)
				return true;
			if (gLawnApp->GetPlatform() == PLATFORM_QQ_HD)
				return true;
		}
	}
	return false;
}

bool LawnApp::isSameDay(time_t time1, time_t time2) const
{
	struct tm date1;
	struct tm date2;
	date1 = *localtime_r(&time1, &date1);
	date2 = *localtime_r(&time2, &date2);
	return date1.tm_year == date2.tm_year && date1.tm_mon == date2.tm_mon && date1.tm_mday == date2.tm_mday;
}

void LawnApp::ParseFormation(std::string i_info, int* i_formation, int i_row, int i_column)
{
	char* buffer = (char*)malloc((unsigned int)i_info.size());
	memcpy(buffer, i_info.c_str(), i_info.size());
	strtok(buffer, ",");
	strtok(NULL, ",");
	for (int i = 0; i < i_row * i_column; i++)
	{
		char* token = strtok(NULL, ",");
		if (!token)
			break;
		i_formation[i] = atoi(token);
	}
	free(buffer);
}

void LawnApp::DoNewOptions(const bool i_showBackToMap, const bool i_isDangerRoom)
{
	if (!m_pauseMenu)
	{
		NewOptionsDialog* dialog = new NewOptionsDialog(i_showBackToMap, i_isDangerRoom);
		m_pauseMenu = dialog;
		mWidgetManager->AddWidget(dialog);
		mWidgetManager->BringToFront(dialog);
		PushOverlaysToTop();
		mWidgetManager->AddBaseModal(dialog);
		mWidgetManager->SetFocus(dialog);
	}
	TouchesCanceled();
}

void LawnApp::StartRechargeCheck()
{
	KillPVZ2Dialog();
	if (m_bNeedCheckFakeFromServer)
	{
		m_bRechargeCheckCompleted = false;
		gMessageRouter->Subscribe(&Message::RechargeCheckOnServerComplete, Sexy::MakeDelegate(*this, &LawnApp::OnRechargeCheckComplete));
		m_rechargeCheckServer.RequestRechargeCheck(0);
	}
	else
	{
		m_bRechargeCheckCompleted = true;
	}
}

bool LawnApp::IsForbiddenPlatform()
{
	std::string* it = sForbiddenPackages;
	std::string* end = it + 85;
	std::string packageName = Android::Util::GetPackageName();
	bool found;
	for (; it != end; it++)
	{
		found = packageName == *it;
		if (found)
			break;
	}
	return found;
}

void LawnApp::ShowPlantGeneEnhancementView()
{
	if (!m_plantGeneEnhancementView)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_plantGeneEnhancementView = new PlantGeneEnhancementView();
		m_plantGeneEnhancementView->InitView();
		mWidgetManager->AddWidget(m_plantGeneEnhancementView);
	}
	mWidgetManager->BringToFront(m_plantGeneEnhancementView);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_plantGeneEnhancementView);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	if (PassThrough(profile->m_activeTutorial) == TUTORIAL_GENEENHANCEMENT_NEW)
		m_plantGeneEnhancementView->StartToturial();
	else
		m_plantGeneEnhancementView->ShowIfGeneNewAdditionInfo();
}

ResourceInfoTypes::ImageRes* LawnApp::GetImageInfoFromImageRef(RtWeakPtr<Image>& i_image)
{
	RtId id = i_image.GetId();
	return (ResourceInfoTypes::ImageRes*)(ResourceInfo*)RtWeakPtr<ResourceInfo>(RtId(RtDb::SYSTEMTABLE_ResourceInfo, id.GetSlotIndex(), i_image.GetId().GetRevision()));
}

bool LawnApp::IsNameMapperContainsId(int i_id)
{
	return PlantNameMapperServerID::GetInstance().ContainsId(i_id)
		|| PlantNameMapper::GetInstance().ContainsId(i_id)
		|| PlantChipNameMapperServerID::GetInstance().ContainsId(i_id)
		|| AvatarNameMapperServerID::GetInstance().ContainsId(i_id)
		|| AvatarChipNameMapperServerID::GetInstance().ContainsId(i_id)
		|| PlantNewAvatarMapper::GetInstance().ContainsId(i_id)
		|| PlantNewAvatarPieceMapper::GetInstance().ContainsId(i_id)
		|| PlantAccessoryInfoMapper::GetInstance().ContainsId(i_id)
		|| PlantAccessoryPieceMapper::GetInstance().ContainsId(i_id)
		|| MaterialItemMapper::GetInstance().ContainsId(i_id)
		|| NameMapperBase::GemServerID == i_id
		|| i_id == NameMapperBase::CoinServerID;
}

bool LawnApp::IsNameMapperContains(IdNameInfo i_idName)
{
	IdType type = i_idName.type;
	bool result = false;
	std::string name = i_idName.name;
	switch (type)
	{
	case IdPlant:
		result = PlantNameMapperServerID::GetInstance().ContainsName(name);
		if (!result)
			result = PlantNameMapper::GetInstance().ContainsName(name);
		break;
	case IdPlantChip:
		result = PlantChipNameMapperServerID::GetInstance().ContainsName(name);
		break;
	case IdAvatar:
		result = AvatarNameMapperServerID::GetInstance().ContainsName(name);
		break;
	case IdAvatarChip:
		result = AvatarChipNameMapperServerID::GetInstance().ContainsName(name);
		break;
	case IdAccessory:
		result = PlantAccessoryInfoMapper::GetInstance().ContainsName(name);
		break;
	case IdAccessoryChip:
		result = PlantAccessoryPieceMapper::GetInstance().ContainsName(name);
		break;
	case IdMaterial:
		result = MaterialItemMapper::GetInstance().ContainsName(name);
		break;
	case IdGem:
		result = NameMapperBase::GemServerName == name;
		break;
	case IdCoin:
		result = NameMapperBase::CoinServerName == name;
	}
	return result;
}

int LawnApp::GetNameMapperName(IdNameInfo i_idName)
{
	IdType type = i_idName.type;
	int result = 0;
	std::string name = i_idName.name;
	switch (type)
	{
	case IdPlant:
		if (PlantNameMapperServerID::GetInstance().ContainsName(name))
			result = PlantNameMapperServerID::GetInstance().GetIdForName(name);
		else if (PlantNameMapper::GetInstance().ContainsName(name))
			result = PlantNameMapper::GetInstance().GetIdForName(name);
		break;
	case IdPlantChip:
		if (PlantChipNameMapperServerID::GetInstance().ContainsName(name))
			result = PlantChipNameMapperServerID::GetInstance().GetIdForName(name);
		break;
	case IdAvatar:
		if (AvatarNameMapperServerID::GetInstance().ContainsName(name))
			result = AvatarNameMapperServerID::GetInstance().GetIdForName(name);
		break;
	case IdAvatarChip:
		if (AvatarChipNameMapperServerID::GetInstance().ContainsName(name))
			result = AvatarChipNameMapperServerID::GetInstance().GetIdForName(name);
		break;
	case IdAccessory:
		if (PlantAccessoryInfoMapper::GetInstance().ContainsName(name))
			result = PlantAccessoryInfoMapper::GetInstance().GetIdForName(name);
		break;
	case IdAccessoryChip:
		if (PlantAccessoryPieceMapper::GetInstance().ContainsName(name))
			result = PlantAccessoryPieceMapper::GetInstance().GetIdForName(name);
		break;
	case IdMaterial:
		if (MaterialItemMapper::GetInstance().ContainsName(name))
			result = MaterialItemMapper::GetInstance().GetIdForName(name);
		break;
	case IdGem:
		if (NameMapperBase::GemServerName == name)
			result = NameMapperBase::GemServerID;
		break;
	case IdCoin:
		if (NameMapperBase::CoinServerName == name)
			result = NameMapperBase::CoinServerID;
		break;
	default:
		break;
	}
	return result;
}

IdNameInfo LawnApp::GetNameMapperInfo(int i_id)
{
	IdNameInfo info;
	if (PlantNameMapperServerID::GetInstance().ContainsId(i_id))
	{
		info.type = IdPlant;
		info.name = PlantNameMapperServerID::GetInstance().GetNameForId(i_id);
	}
	else if (PlantNameMapper::GetInstance().ContainsId(i_id))
	{
		info.type = IdPlant;
		info.name = PlantNameMapper::GetInstance().GetNameForId(i_id);
	}
	else if (PlantChipNameMapperServerID::GetInstance().ContainsId(i_id))
	{
		info.type = IdPlantChip;
		info.name = PlantChipNameMapperServerID::GetInstance().GetNameForId(i_id);
	}
	else if (AvatarNameMapperServerID::GetInstance().ContainsId(i_id))
	{
		info.type = IdAvatar;
		info.name = AvatarNameMapperServerID::GetInstance().GetNameForId(i_id);
	}
	else if (AvatarChipNameMapperServerID::GetInstance().ContainsId(i_id))
	{
		info.type = IdAvatarChip;
		info.name = AvatarChipNameMapperServerID::GetInstance().GetNameForId(i_id);
	}
	else if (PlantAccessoryInfoMapper::GetInstance().ContainsId(i_id))
	{
		info.type = IdAccessory;
		info.name = PlantAccessoryInfoMapper::GetInstance().GetNameForId(i_id);
	}
	else if (PlantAccessoryPieceMapper::GetInstance().ContainsId(i_id))
	{
		info.type = IdAccessoryChip;
		info.name = PlantAccessoryPieceMapper::GetInstance().GetNameForId(i_id);
	}
	else if (MaterialItemMapper::GetInstance().ContainsId(i_id))
	{
		info.type = IdMaterial;
		info.name = MaterialItemMapper::GetInstance().GetNameForId(i_id);
	}
	else
	{
		if (NameMapperBase::GemServerID == i_id)
		{
			info.type = IdGem;
			info.name = NameMapperBase::GemServerName;
		}
		else if (NameMapperBase::CoinServerID == i_id)
		{
			info.type = IdCoin;
			info.name = NameMapperBase::CoinServerName;
		}
	}
	return info;
}

bool LawnApp::IsAdChannel(ViewType i_type)
{
	bool result = true;
	if (i_type != VIEW_TYPE_SCREEN)
	{
		if (i_type == VIEW_TYPE_MEDIA)
			GetPlatform();
		else if (i_type != VIEW_TYPE_MEDIA_PARAM)
			result = i_type == VIEW_TYPE_BANNER;
		else
		{
			std::string packageName = Android::Util::GetPackageName();
			std::vector<std::string>::iterator it = std::find(m_adBlackList.begin(), m_adBlackList.end(), packageName);
			result = it == m_adBlackList.end();
		}
	}
	return result;
}

void LawnApp::ShowPvpUpgrade(PVPLabItemType type)
{
	if (m_pvpUpgrade)
		return;
	Widget* upgrade = NULL;
	if (type != LabItem_None)
	{
		if ((unsigned)type < LabItem_Zombie)
		{
			upgrade = new PVPBaseUpgrade(type);
			m_pvpUpgrade = upgrade;
		}
		else if (type == LabItem_Skill)
		{
			upgrade = new PVPSkillUpgrade();
			m_pvpUpgrade = upgrade;
		}
	}
	mWidgetManager->AddWidget(upgrade);
	mWidgetManager->BringToFront(m_pvpUpgrade);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_pvpUpgrade);
	mWidgetManager->SetFocus(m_pvpUpgrade);
}

void LawnApp::CheckForUpdates()
{
	m_bLoadVersionCompleted = false;
	gMessageRouter->Subscribe(&Message::FetchVersionComplete, Sexy::MakeDelegate(*this, &LawnApp::OnFetchVersionComplete));
	m_versionNetworkManager.CheckForUpdates(0);
	if (Sexy::LazySingleton<ProfileMgr>::GetInstance().needCheckFakeFromServer())
		m_bNeedCheckFakeFromServer = true;
	StartRechargeCheck();
	CheckForNetworkContentChanges();
}

void LawnApp::ShowActivityHome()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_activityHome)
		m_activityHome = new WorldMapActivityHome(1);
	mWidgetManager->AddWidget(m_activityHome);
	mWidgetManager->BringToFront(m_activityHome);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_activityHome);
	PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	int tutorial = PassThrough(profile->m_activeTutorial);
	if (tutorial == 53)
		m_activityHome->InitDangerRoomTutotrial();
	else if (tutorial == 35)
		m_activityHome->InitJoustTutotrial();
}

bool LawnApp::UpdateApp()
{
	if (mLoadingThreadCompleted)
		NoOp();
	bool updated = Sexy::SexyAppBase::UpdateApp();
	if (mLoadingThreadCompleted && !mExitToTop)
		NoOp();
	return updated;
}

void LawnApp::KillNewWorldDialog()
{
	gLawnApp->DeleteGroup("UI_WorldPreview");
	m_newLevelToJump = "";
	gLawnApp->KillPVZ2Dialog();
	if (m_board)
		m_board->Pause(false);
}

void LawnApp::ShowCoinStore(StoreType type)
{
	if (m_coinStore)
		KillCoinStore();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_board)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
	}
	m_coinStore = new CoinStore(type);
	mWidgetManager->AddWidget(m_coinStore);
	mWidgetManager->BringToFront(m_coinStore);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_coinStore);
	mWidgetManager->SetFocus(m_coinStore);
}

void LawnApp::ShowSpAds(int i_type)
{
	if (i_type == 0)
		EASquared::Instance().ShowAdvertisement("EA2Mission", Sexy::MakeDelegate(*this, &LawnApp::onWatchDaveShopAds), true, VIEW_TYPE_MEDIA, VIEW_POSITION_DOUBLE_COIN);
}

ActivityDropGroup* LawnApp::GetActivityDropGroup()
{
	ActivityDropGroup* result = NULL;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_DROP_ITEM_GROUPS); it; ++it)
	{
		Sexy::RtWeakPtr<Sexy::RtObject> object = *it;
		ActivityDropGroup* found = NULL;
		if (object)
			found = object->Cast<ActivityDropGroup>();
		if (found)
		{
			result = found;
			break;
		}
	}
	return result;
}

DropOutItems* LawnApp::GetDropItemsList()
{
	DropOutItems* result = NULL;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_DROP_ITEMS); it; ++it)
	{
		Sexy::RtWeakPtr<Sexy::RtObject> object = *it;
		DropOutItems* found = NULL;
		if (object)
			found = object->Cast<DropOutItems>();
		if (found)
		{
			result = found;
			break;
		}
	}
	return result;
}

ChallengeGroupData* LawnApp::GetChallengeDropItemsList(std::string groupid)
{
	ChallengeGroupData* result = NULL;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_CHALLENGE_DROP_ITEMS); it; ++it)
	{
		Sexy::RtWeakPtr<Sexy::RtObject> object = *it;
		ChallengeDropOutItems* items = NULL;
		if (object)
			items = object->Cast<ChallengeDropOutItems>();
		if (items)
		{
			for (size_t i = 0; i < items->DropOutGroupList.size(); i++)
			{
				if (items->DropOutGroupList[i].DropGroupId == groupid)
				{
					int count = ProfileMgr::GetInstance().GetCurrentProfile()->getChallengeCount(getCurrentWorldIndex(), getCurrentChallengeIndex());
					result = &items->DropOutGroupList[i].Groups[count > 2 ? 2 : count];
					break;
				}
			}
			break;
		}
	}
	return result;
}

uint32 LawnApp::GetLevelDaysByLevelString(const std::string& i_level)
{
	std::string prefix = i_level.substr(0, 2);
	if (prefix == "eg")
		return atoi(i_level.substr(5, i_level.size() - 5).c_str());
	if (prefix == "pi")
		return atoi(i_level.substr(6, i_level.size() - 6).c_str()) + 11;
	if (prefix == "co")
		return atoi(i_level.substr(6, i_level.size() - 6).c_str()) + 21;
	if (prefix == "ko")
		return atoi(i_level.substr(6, i_level.size() - 6).c_str()) + 31;
	return 0;
}

void LawnApp::OnLuaNotify(const std::string& rStrEvent)
{
	if (__builtin_expect(!!(rStrEvent == "OpenTrainingRoom"), 1))
	{
		DangerRoomManager::GetInstancePtr()->SetMainDialogVisible(false);
		GetWorldMap()->GetUniverseMap()->TransitionToUniverse(true);
	}
	else if (!(rStrEvent != "OpenUI"))
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		if (profile)
		{
			Sexy::StructuredData json = profile->GetLuaShareJson();
			const Sexy::StructuredData::Value* openUI = json.ObjectForPath("$.OpenUI");
			if (openUI)
			{
				const char* uiType = openUI->StringForName("UiType", NULL);
				if (uiType)
				{
					const char* param1 = openUI->StringForName("Param1", NULL);
					if (param1)
					{
						const char* param2 = openUI->StringForName("Param2", NULL);
						if (param2 && uiType == std::string("AdsRewardUI"))
						{
							AdsRewardUI* ui = UISingletonDialog<AdsRewardUI>::ShowDialog();
							if (ui)
							{
								ui->setReward(atoi(param1), atoi(param2));
								ui->setTitleShow(false);
							}
						}
					}
				}
			}
		}
	}
}

void LawnApp::ShowPowerPKView()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (!m_powerPKView)
		m_powerPKView = new PowerPKWidget();
	if (m_board)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
	}
	m_powerPKView->SetTotalPower(100);
	m_powerPKView->SetCurPower(50);
	mWidgetManager->AddWidget(m_powerPKView);
	mWidgetManager->BringToFront(m_powerPKView);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_powerPKView);
	mWidgetManager->SetFocus(m_powerPKView);
}

Sexy::Dialog* LawnApp::DoDialog(int i_dialogId, bool isModal, const SexyString& i_dialogHeader, const SexyString& i_dialogLines, const SexyString& i_dialogFooter, int i_buttonMode)
{
	SexyString header = TodStringTranslate(i_dialogHeader);
	SexyString lines = TodStringTranslate(i_dialogLines);
	SexyString footer = TodStringTranslate(i_dialogFooter);
	Sexy::Dialog* dialog = SexyAppBase::DoDialog(i_dialogId, isModal, header, lines, footer, i_buttonMode);
	if (!mWidgetManager->mFocusWidget)
		mWidgetManager->mFocusWidget = dialog;
	return dialog;
}

void LawnApp::LaunchNewVersionUrl()
{
	PVZVersion version = Version::LoadedRSB();
	std::string url = Sexy::WStringToString(TodStringTranslate(Sexy::StringToSexyString(version.version_notice.VersionUrl)));
	if (url == "")
		return;
	OpenURL(url, false);
}

PHPServerConfig* LawnApp::GetServerPHPConfig()
{
	SexyString configName = L"PHPServerConfig";
	if (IsServiceAvailable(Service_Https))
		configName += L"Https";
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_SERVER_CONFIG);
	return table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(configName)))->Cast<PHPServerConfig>();
}

int LawnApp::GetBonusStartingSun()
{
	int bonusSun = 0;
	if (HasPlayerUnlockedFeature(FEATURE_UPGRADE_STARTING_SUN_LVL1))
		bonusSun += 25;
	if (HasPlayerUnlockedFeature(FEATURE_UPGRADE_STARTING_SUN_LVL2))
		bonusSun += 25;
	if (HasPlayerUnlockedFeature(FEATURE_UPGRADE_STARTING_SUN_LVL3))
		bonusSun += 25;
	if (HasPlayerUnlockedFeature(FEATURE_UPGRADE_STARTING_SUN_LVL4))
		bonusSun += 25;
	if (RiftUtils::IsPlayingRiftLevel() && RiftUtils::IsRiftTimedLevel())
		return bonusSun;
	PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
	if (profile)
	{
		if (profile->IsMonthlyCardActivated(E_MC_CLASSICAL))
			bonusSun += 50;
		if (profile->IsMonthlyCardActivated(E_MC_CHINA_MOBILE))
			bonusSun += 50;
		if (profile->GetMonthVIPState() > 0)
			bonusSun += 50;
	}
	return bonusSun;
}

void LawnApp::goToMainMenu()
{
	if (GetWorldMap()->CanBeClosed())
	{
		PlayerInfo* profile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
		if (profile)
			profile->SetWorldMapZoomData(PassThroughF(gLawnApp->GetWorldMap()->m_cameraZoom), profile->WasOnUniverseMapLast());
		gGameStateMgr->ShowMainMenu(GAMETRANSITION_QuickBlack, GAMETRANSITION_QuickBlack);
		Sexy::WidgetManager* widgetManager = mWidgetManager;
		TransitionOverlayWidget* overlay = gLawnApp->GetTransitionOverlay();
		widgetManager->BringToFront(overlay);
		PushOverlaysToTop();
	}
	else
		GetWorldMap()->QueueForTransition((GameState)4);
}

void LawnApp::ShowActivityCollection()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_activityCollection)
	{
		m_activityCollection = new UIActivityCollection();
		m_activityCollection->Init();
	}
	mWidgetManager->AddWidget(m_activityCollection);
	mWidgetManager->BringToFront(m_activityCollection);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_activityCollection);
}

void LawnApp::ShowLinkageActivityCollection()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (!m_activityCollection)
	{
		m_activityCollection = new UILinkageActivityCollection();
		m_activityCollection->Init();
	}
	mWidgetManager->AddWidget(m_activityCollection);
	mWidgetManager->BringToFront(m_activityCollection);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_activityCollection);
}

void LawnApp::ShowGachaUI(const std::string& i_objectItem, bool bDiamond)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (!m_gachaUI)
		m_gachaUI = new GachaUI(i_objectItem, bDiamond);
	m_gachaUI->Init();
	mWidgetManager->AddWidget(m_gachaUI);
	mWidgetManager->BringToFront(m_gachaUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_gachaUI);
	mWidgetManager->SetFocus(m_gachaUI);
}

void LawnApp::ShowGachaUI(const std::string& i_objectItem, bool bDiamond, GachaType i_type)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (!m_gachaUI)
		m_gachaUI = new GachaUI(i_objectItem, bDiamond, i_type);
	m_gachaUI->Init();
	mWidgetManager->AddWidget(m_gachaUI);
	mWidgetManager->BringToFront(m_gachaUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_gachaUI);
	mWidgetManager->SetFocus(m_gachaUI);
}

void LawnApp::DrawDarkeningLayer(Graphics* i_g, float backgroundAlpha)
{
	GraphicsAutoState state(i_g);
	i_g->ClearClipRect();
	i_g->mTransX = 0;
	i_g->mTransY = 0;
	i_g->SetColor(Color(0, 0, 0, (int)(backgroundAlpha * 255.0f)));
	i_g->FillRect(0, 0, mScreenBounds.mWidth, mScreenBounds.mHeight);
}

GachaUI* LawnApp::getGachaUI()
{
	if (!m_gachaUI)
		m_gachaUI = new GachaUI("gacha_diamond", false);
	return m_gachaUI;
}

void LawnApp::PushOverlaysToTop()
{
	mWidgetManager->BringToFront(m_npcManager);
	mWidgetManager->BringToFront(m_transitionOverlay);
	mWidgetManager->BringToFront(m_postProcessWidget);
	mWidgetManager->BringToFront(m_busyManager);
	if (m_dialog)
		mWidgetManager->BringToFront(m_dialog);
	UIMessageBox* messageBox = UISingletonDialog<UIMessageBox>::GetSingletonPtr();
	if (messageBox)
		mWidgetManager->BringToFront(messageBox);
}

void LawnApp::ShowDangerRoomSpecialOfferUI()
{
	if (m_DangerRoomSpecialOfferUI)
		return;
	m_DangerRoomSpecialOfferUI = new DangerRoomSpecialOfferUI();
	mWidgetManager->AddWidget(m_DangerRoomSpecialOfferUI);
	mWidgetManager->BringToFront(m_DangerRoomSpecialOfferUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_DangerRoomSpecialOfferUI);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_DangerRoomSpecialOfferUI);
	m_DangerRoomSpecialOfferUI->RefreshActivity();
}

void LawnApp::ShowPlantSpecialOfferUI()
{
	if (m_PlantSpecialOfferUI)
		return;
	m_PlantSpecialOfferUI = new PlantSpecialOfferUI();
	mWidgetManager->AddWidget(m_PlantSpecialOfferUI);
	mWidgetManager->BringToFront(m_PlantSpecialOfferUI);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_PlantSpecialOfferUI);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_PlantSpecialOfferUI);
	m_PlantSpecialOfferUI->RefreshActivity();
}

void LawnApp::ShowArenaEndingUI(ArenaResult i_result, const std::vector<ZombieRecord>& i_zombieList, bool i_league, int iStarNum)
{
	if (!m_arenaEndingUI)
		m_arenaEndingUI = new ArenaEndingUI(i_result, i_zombieList, i_league, iStarNum);
	mWidgetManager->AddWidget(m_arenaEndingUI);
	mWidgetManager->BringToFront(m_arenaEndingUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_arenaEndingUI);
	mWidgetManager->SetFocus(m_arenaEndingUI);
}

void LawnApp::ShowBoardZombieAlmanacUI(const std::vector<std::string>& i_zombieList)
{
	if (!m_boardZombieAlmanacUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_boardZombieAlmanacUI = new BoardZombieAlmanacUI(i_zombieList);
		mWidgetManager->AddWidget(m_boardZombieAlmanacUI);
		mWidgetManager->BringToFront(m_boardZombieAlmanacUI);
		mWidgetManager->AddBaseModal(m_boardZombieAlmanacUI);
		PushOverlaysToTop();
	}
	mWidgetManager->SetFocus(m_boardZombieAlmanacUI);
}

void LawnApp::ShowDailySignActivityRewardView(const std::vector<NDLoginRewardBonus>& i_rewardList)
{
	if (m_DailySignRewardView)
		return;
	m_DailySignRewardView = new DailySignRewardView(i_rewardList);
	m_DailySignRewardView->InitView();
	mWidgetManager->AddWidget(m_DailySignRewardView);
	mWidgetManager->BringToFront(m_DailySignRewardView);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_DailySignRewardView);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_DailySignRewardView);
}

void LawnApp::ShowGachaDisplayerDialog(GachaType i_type)
{
	if (!m_gachaDisplayerDialog)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_gachaDisplayerDialog = new GachaDisplayerDialog(i_type);
		mWidgetManager->AddWidget(m_gachaDisplayerDialog);
		mWidgetManager->BringToFront(m_gachaDisplayerDialog);
		mWidgetManager->AddBaseModal(m_gachaDisplayerDialog);
		PushOverlaysToTop();
	}
	mWidgetManager->SetFocus(m_gachaDisplayerDialog);
}

void LawnApp::ShowSevenDaysRewardView(const std::vector<NDLoginRewardBonus>& i_rewardList)
{
	if (m_NDDailyLoginRewardView)
		return;
	m_NDDailyLoginRewardView = new NDDailyLoginRewardView(i_rewardList);
	m_NDDailyLoginRewardView->InitView();
	mWidgetManager->AddWidget(m_NDDailyLoginRewardView);
	mWidgetManager->BringToFront(m_NDDailyLoginRewardView);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_NDDailyLoginRewardView);
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_NDDailyLoginRewardView);
}

void LawnApp::ShowDaveClubUI(bool i_refreshByNetwork)
{
	if (m_pDaveClubUI)
		KillDaveClubUI();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_board)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
	}
	m_pDaveClubUI = new DaveClubUI();
	mWidgetManager->AddWidget(m_pDaveClubUI);
	mWidgetManager->BringToFront(m_pDaveClubUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_pDaveClubUI);
	mWidgetManager->SetFocus(m_pDaveClubUI);
}

void LawnApp::ShowPlantDefenceEntrance()
{
	if (m_plantDefenceEntrance)
		killPlantDefenceEntrance();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_board)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
	}
	m_plantDefenceEntrance = new PlantDefenceEntrance();
	mWidgetManager->AddWidget(m_plantDefenceEntrance);
	mWidgetManager->BringToFront(m_plantDefenceEntrance);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_plantDefenceEntrance);
	mWidgetManager->SetFocus(m_plantDefenceEntrance);
}

void LawnApp::ShowSummerEventEntranceUI()
{
	if (m_summerEventEntranceUI)
		killSummerEventEntranceUI();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_board)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
	}
	m_summerEventEntranceUI = new SummerEventEntranceUI();
	mWidgetManager->AddWidget(m_summerEventEntranceUI);
	mWidgetManager->BringToFront(m_summerEventEntranceUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_summerEventEntranceUI);
	mWidgetManager->SetFocus(m_summerEventEntranceUI);
}

void LawnApp::ShowTimeTravelEventEntranceUI()
{
	if (m_timeTravelEntranceUI)
		killSummerEventEntranceUI();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_board)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
	}
	m_timeTravelEntranceUI = new TimeTravelEntranceUI();
	mWidgetManager->AddWidget(m_timeTravelEntranceUI);
	mWidgetManager->BringToFront(m_timeTravelEntranceUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_timeTravelEntranceUI);
	mWidgetManager->SetFocus(m_timeTravelEntranceUI);
}

void LawnApp::ShowAlmanac(ObjectTypeDescriptorPtr i_objectType)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Almanac_Open");
	m_almanac = new AlmanacWidget(i_objectType);
	mWidgetManager->AddWidget(m_almanac);
	mWidgetManager->BringToFront(m_almanac);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_almanac);
}

void LawnApp::ShowAwakenWidget(ObjectTypeDescriptorPtr i_objectType)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Almanac_Open");
	m_awakenWidget = new ArenaAwakenWidget(i_objectType);
	mWidgetManager->AddWidget(m_awakenWidget);
	mWidgetManager->BringToFront(m_awakenWidget);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_awakenWidget);
}

void LawnApp::ShowBattleStatementUI(BattleStatementUI::AccountUIType eType)
{
	if (m_battleStatementUI)
		KillBattleStatementUI();
	if (m_board && eType == BattleStatementUI::AccountUIType_Normal)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
		m_board->RemoveBoardResource();
	}
	m_battleStatementUI = new BattleStatementUI(eType);
	mWidgetManager->AddWidget(m_battleStatementUI);
	mWidgetManager->BringToFront(m_battleStatementUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_battleStatementUI);
	mWidgetManager->SetFocus(m_battleStatementUI);
}

void LawnApp::ShowReviveUI(ReviveMode i_mode)
{
	if (m_reviveUI)
		KillReviveUI();
	if (m_board)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
	}
	m_reviveUI = new ReviveUI(i_mode);
	mWidgetManager->AddWidget(m_reviveUI);
	mWidgetManager->BringToFront(m_reviveUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_reviveUI);
	mWidgetManager->SetFocus(m_reviveUI);
}

void LawnApp::ShowAdventureOpenedUI()
{
	if (!m_AdventureOpenedUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_AdventureOpenedUI = new AdventureOpenedUI();
		mWidgetManager->AddWidget(m_AdventureOpenedUI);
	}
	mWidgetManager->BringToFront(m_AdventureOpenedUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_AdventureOpenedUI);
	mWidgetManager->SetFocus(m_AdventureOpenedUI);
	gMessageRouter->Post(&Message::OpenUI, "AdventureOpenUI");
}

void LawnApp::ShowPlantAdventureUI()
{
	if (!m_PlantAdventureUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_PlantAdventureUI = new PlantAdventureUI();
		mWidgetManager->AddWidget(m_PlantAdventureUI);
	}
	mWidgetManager->BringToFront(m_PlantAdventureUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_PlantAdventureUI);
	mWidgetManager->SetFocus(m_PlantAdventureUI);
	gMessageRouter->Post(&Message::OpenUI, "PlantAdventureUI");
}

void LawnApp::ShowNewerPresentUI(int itype)
{
	if (m_newerPresentUI)
		KillNewerPresentUI();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_board)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
	}
	m_newerPresentUI = new NewerPresentUI(itype);
	mWidgetManager->AddWidget(m_newerPresentUI);
	mWidgetManager->BringToFront(m_newerPresentUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_newerPresentUI);
	mWidgetManager->SetFocus(m_newerPresentUI);
}

void LawnApp::ShowStarLevelChallengeUINow(int index)
{
	if (m_starLevelChallengeUI)
		KillStarLevelChallengeUI();
	if (m_board)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
	}
	m_starLevelChallengeUI = new StarLevelChallengeUI(getCurrentWorldIndex(), index);
	mWidgetManager->AddWidget(m_starLevelChallengeUI);
	mWidgetManager->BringToFront(m_starLevelChallengeUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_starLevelChallengeUI);
	mWidgetManager->SetFocus(m_starLevelChallengeUI);
}

void LawnApp::ShowFestivalEntranceUI(FestivalGameMode i_mode)
{
	if (m_festivalEntranceUI)
		KillFestivalEntranceUI();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_board)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
	}
	FestivalManager::GetInstance().SetCurFestivalGameMode(i_mode);
	m_festivalEntranceUI = new FestivalEntranceUI(i_mode);
	mWidgetManager->AddWidget(m_festivalEntranceUI);
	mWidgetManager->BringToFront(m_festivalEntranceUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_festivalEntranceUI);
	mWidgetManager->SetFocus(m_festivalEntranceUI);
}

void LawnApp::ShowFestivalEntranceUINow(FestivalGameMode i_mode)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_board)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
	}
	FestivalManager::GetInstance().SetCurFestivalGameMode(i_mode);
	m_festivalEntranceUI = new FestivalEntranceUI(i_mode);
	mWidgetManager->AddWidget(m_festivalEntranceUI);
	mWidgetManager->BringToFront(m_festivalEntranceUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_festivalEntranceUI);
	mWidgetManager->SetFocus(m_festivalEntranceUI);
}

void LawnApp::ShowAdventureSurpriseUI(int i_dungeonId)
{
	if (!m_AdventureSurpriseUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_AdventureSurpriseUI = new AdventureSurpriseUI(i_dungeonId);
		mWidgetManager->AddWidget(m_AdventureSurpriseUI);
	}
	mWidgetManager->BringToFront(m_AdventureSurpriseUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_AdventureSurpriseUI);
	mWidgetManager->SetFocus(m_AdventureSurpriseUI);
	gMessageRouter->Post(&Message::OpenUI, "AdventureSurpriseUI");
}

void LawnApp::ShowRedeemRewardUI(const std::string& payTime, const std::string& payCode, const std::string& orderNumber)
{
	if (!m_RedeemRewardUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_RedeemRewardUI = new RedeemRewardUI(payTime, payCode, orderNumber);
		mWidgetManager->AddWidget(m_RedeemRewardUI);
	}
	else
		m_RedeemRewardUI->updateRewardList(payTime, payCode, orderNumber);
	mWidgetManager->BringToFront(m_RedeemRewardUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_RedeemRewardUI);
	mWidgetManager->SetFocus(m_RedeemRewardUI);
	m_RedeemRewardUI->showRewardList();
}

void LawnApp::ShowBuyItemUI(int i_type)
{
	if (m_BuyItemUI)
		return;
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_board)
	{
		m_board->ClearCursors();
		PauseMusic();
		m_board->Pause(true);
	}
	m_BuyItemUI = new BuyItemUI((BuyItemUI::BuyType)i_type);
	mWidgetManager->AddWidget(m_BuyItemUI);
	mWidgetManager->BringToFront(m_BuyItemUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_BuyItemUI);
	mWidgetManager->SetFocus(m_BuyItemUI);
}

void LawnApp::ShowRewardPlantUI(PlantTypePtr i_plant)
{
	if (i_plant.IsValid())
	{
		KillRewardPlantUI();
		if (!m_rewardPlantUI)
		{
			m_rewardPlantUI = new RewardPlantUI(i_plant, true);
			mWidgetManager->AddWidget(m_rewardPlantUI);
		}
		mWidgetManager->BringToFront(m_rewardPlantUI);
		PushOverlaysToTop();
		mWidgetManager->SetFocus(m_rewardPlantUI);
	}
}

Sexy::Point LawnApp::GetScreenContentOffset()
{
	float width = (float)mWidth;
	int w = (int)eastl::max_alt(m_contentResolutionWidth, width);
	return Sexy::Point((gLawnApp->mScreenBounds.mWidth - w) / 2, (int)((float)gLawnApp->mScreenBounds.mHeight - m_contentResolutionHeight) / 2);
}

LawnApp::~LawnApp()
{
	gMessageRouter->Unsubscribe(this);
	if (m_board)
		ProfileMgr::GetInstance().Save(false, false);
	if (m_metricsCollector)
	{
		m_metricsCollector->Term();
		if (m_metricsCollector)
		{
			delete m_metricsCollector;
			m_metricsCollector = NULL;
		}
	}
	AudioMgr::GetInstancePtr()->Term();
	if (m_board)
	{
		m_board->EndLevel();
		mWidgetManager->RemoveWidget(m_board);
		if (m_board)
		{
			delete m_board;
			m_board = NULL;
		}
	}
	if (m_titleScreen)
	{
		mWidgetManager->RemoveWidget(m_titleScreen);
		if (m_titleScreen)
		{
			delete m_titleScreen;
			m_titleScreen = NULL;
		}
	}
	if (m_transitionOverlay)
	{
		mWidgetManager->RemoveWidget(m_transitionOverlay);
		if (m_transitionOverlay)
		{
			delete m_transitionOverlay;
			m_transitionOverlay = NULL;
		}
	}
	if (m_busyManager)
	{
		mWidgetManager->RemoveWidget(m_busyManager);
		if (m_busyManager)
		{
			delete m_busyManager;
			m_busyManager = NULL;
		}
	}
	if (m_almanac)
	{
		mWidgetManager->RemoveWidget(m_almanac);
		if (m_almanac)
		{
			delete m_almanac;
			m_almanac = NULL;
		}
	}
	if (m_awakenWidget)
	{
		mWidgetManager->RemoveWidget(m_awakenWidget);
		if (m_awakenWidget)
		{
			delete m_awakenWidget;
			m_awakenWidget = NULL;
		}
	}
	if (m_npcManager)
	{
		mWidgetManager->RemoveWidget(m_npcManager);
		if (m_npcManager)
		{
			delete m_npcManager;
			m_npcManager = NULL;
		}
	}
	if (m_postProcessWidget)
	{
		mWidgetManager->RemoveWidget(m_postProcessWidget);
		if (m_postProcessWidget)
		{
			delete m_postProcessWidget;
			m_postProcessWidget = NULL;
		}
	}
	NetworkMgr* networkMgr = NetworkMgr::Instance();
	if (networkMgr && (networkMgr = NetworkMgr::Instance()))
		delete networkMgr;
	ProcessSafeDeleteList();
}

void LawnApp::onLoginiCloudServerFinish(bool i_success)
{
	const bool success = i_success;
	if (__builtin_expect(!!(success && gLawnApp->IsAdActivated()), 0))
		EASquared::Instance().Initialize(NetworkMgr::Instance()->GetNewNetWorkProcess()->INetworkMsgProcess::GetPlayUserId());
	setProfileSyncing(false);
}

std::string LawnApp::GetTargetDangerRoomLevelName(DangerRoomLevelType i_type)
{
	std::string name = "";
	switch (i_type)
	{
	case DR_LEVEL_ONE:
		name = "festival_level_one";
		break;
	case DR_LEVEL_TWO:
		name = "festival_level_two";
		break;
	case DR_LEVEL_THREE:
		name = "festival_level_three";
		break;
	case DR_LEVEL_FOUR:
		name = "festival_level_four";
		break;
	case DR_LEVEL_ENDLESS:
		name = "festival_level_endless";
		break;
	}
	return name;
}

std::string LawnApp::GetDangerRoomLevelName()
{
	std::string name = "";
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	DangerRoomLevelType level = profile ? profile->GetCurrentDangerRoomLevel() : DR_LEVEL_ONE;
	switch (level)
	{
	case DR_LEVEL_ONE:
		name = "festival_level_one";
		break;
	case DR_LEVEL_TWO:
		name = "festival_level_two";
		break;
	case DR_LEVEL_THREE:
		name = "festival_level_three";
		break;
	case DR_LEVEL_FOUR:
		name = "festival_level_four";
		break;
	case DR_LEVEL_ENDLESS:
		name = "festival_level_endless";
		break;
	}
	return name;
}

void LawnApp::onSyncProfileToServer(bool i_success)
{
	if (!GetMainMenu() && m_selfSync)
	{
		if (i_success)
		{
			m_selfSync = false;
			goToMainMenu();
		}
		else
		{
			gLawnApp->CheckNetWork(L"[NETWORK_NOT_CONNECTED_TITLE]", L"[NETWORK_NOT_CONNECTED_TEXT_FOR_SYNC_PLAYERINFO]");
		}
	}
}

void LawnApp::onSyncProfileFromServer(bool i_success)
{
	if (!GetMainMenu() && m_selfSync)
	{
		if (!i_success)
		{
			gLawnApp->CheckNetWork(L"[NETWORK_NOT_CONNECTED_TITLE]", L"[NETWORK_NOT_CONNECTED_TEXT_FOR_SYNC_PLAYERINFO]");
		}
		else
		{
			m_selfSync = false;
			PlayerInfo* profile = ProfileUtils::Profile();
			if (profile)
				profile->SyncOfflineDataFromOnlineData();
			goToMainMenu();
		}
	}
}

Image* LawnApp::GetUpdateActivityImage(ActivityImageType i_type, const std::string& i_resName)
{
	Image* image = NULL;
	if (i_type == Type_Headshot_Avatar)
	{
		image = StringHelper::ToImage(PlantHeadshot::AvatarBigPrefix + Sexy::StringToUpper(i_resName), false);
		if (!image)
			image = StringHelper::ToImage(PlantHeadshot::UpdateAvatarBigPrefix + Sexy::StringToUpper(i_resName), true);
	}
	return image;
}

void LawnApp::ShowPlantSkillTipsUI(SexyString& sTips, int iPositonX, int iPostionY, int eType, std::function<void(Widget*)> adjust, bool isResumePause)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (m_board && !isResumePause)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	if (!m_plantSkillTipsUI)
		m_plantSkillTipsUI = new PlantSkillTipsUI(sTips, iPositonX, iPostionY, (EPlantSkillTipsType)eType);
	if (adjust)
		adjust(m_plantSkillTipsUI);
	mWidgetManager->AddWidget(m_plantSkillTipsUI);
	mWidgetManager->BringToFront(m_plantSkillTipsUI);
}

void LawnApp::ShowPlantLevelUpCheckDialog(MagentoProductPropsPtr i_props)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	if (m_board)
	{
		m_board->ClearCursors();
		m_board->Pause(true);
	}
	if (!m_plantLevelUpInfoDialog)
		m_plantLevelUpCheckDialog = new PlantLevelUpCheckDialog(i_props);
	mWidgetManager->AddWidget(m_plantLevelUpCheckDialog);
	mWidgetManager->BringToFront(m_plantLevelUpCheckDialog);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_plantLevelUpCheckDialog);
	mWidgetManager->SetFocus(m_plantLevelUpCheckDialog);
}

void LawnApp::ShowTGPieceTableUI()
{
	if (!m_tgPieceTableUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_tgPieceTableUI = new TGPieceTableUI();
		m_tgPieceTableUI->InitView();
		mWidgetManager->AddWidget(m_tgPieceTableUI);
	}
	mWidgetManager->BringToFront(m_tgPieceTableUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_tgPieceTableUI);
	mWidgetManager->SetFocus(m_tgPieceTableUI);
	if (m_tgPieceTableUI)
	{
		m_tgPieceTableUI->NormalInit(PT_FromCenter | PT_FromMiddle | PT_Scaled | PT_Fade);
		m_tgPieceTableUI->StartPop();
	}
}

void LawnApp::ShowTGAvatarPieceTableUI()
{
	if (!m_tgAvatarPieceTableUI)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_tgAvatarPieceTableUI = new TGAvatarPieceTableUI();
		m_tgAvatarPieceTableUI->InitView();
		mWidgetManager->AddWidget(m_tgAvatarPieceTableUI);
	}
	mWidgetManager->BringToFront(m_tgAvatarPieceTableUI);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_tgAvatarPieceTableUI);
	mWidgetManager->SetFocus(m_tgAvatarPieceTableUI);
	if (m_tgAvatarPieceTableUI)
	{
		m_tgAvatarPieceTableUI->NormalInit(PT_FromCenter | PT_FromMiddle | PT_Scaled | PT_Fade);
		m_tgAvatarPieceTableUI->StartPop();
	}
}

WorldMapList* LawnApp::GetWorldMapList()
{
	WorldMapList* list;
	if (m_worldMapList.IsValid())
	{
		list = m_worldMapList;
	}
	else
	{
		Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_WORLDMAPLIST_NEW);
		for (; it; ++it)
		{
			Sexy::RtWeakPtr<Sexy::RtObject> object = *it;
			if (object && object.Get()->Cast<WorldMapList>())
			{
				m_worldMapList = object;
				break;
			}
		}
		list = m_worldMapList;
	}
	return list;
}

bool LawnApp::PhysicalKeyDown(int theKey)
{
	bool handled = false;
	if (theKey == KEYCODE_GOBACK)
	{
		if (m_dialog || IsCoinStoreShowing() || IsWorldPreviewShowing() || IsNewerPresentUIShowing() || IsReviveUIShowing() ||
			IsFestivalEntranceUIShowing() || (m_npcManager && m_npcManager->IsNarrationActive()) || (m_busyManager && m_busyManager->IsActive()))
			return true;
		switch (m_gameStateMgr.GetState())
		{
		case GAME_Game:
			gMessageRouter->Post(&Message::PauseButtonPressed);
			return true;
		case GAME_WorldMap:
		case GAME_MainMenu:
			if (ProfileMgr::GetInstance().GetPurchaseBroker()->ExitGame())
				return true;
			ShowConfirmExitGame();
			return true;
		default:
			return true;
		}
	}
	return handled;
}

void LawnApp::ShowGameMaskUI(Sexy::SexyVector2 maskTargetPos, int maskTargetRadius, Sexy::Widget* event, std::string lawnDesc)
{
	KillGameMaskUI();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	m_pGameMaskUI = new GameMaskUI(maskTargetPos, maskTargetRadius, event, lawnDesc);
	mWidgetManager->AddWidget(m_pGameMaskUI);
	mWidgetManager->PutInfront(m_pGameMaskUI, event);
	PushOverlaysToTop();
	mWidgetManager->SetFocus(m_pGameMaskUI);
}

void LawnApp::ShowLevelofDayEntrance()
{
	if (!m_levelofDayEntrance)
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
		m_levelofDayEntrance = new LevelOfDayEntrance();
		mWidgetManager->AddWidget(m_levelofDayEntrance);
	}
	mWidgetManager->BringToFront(m_levelofDayEntrance);
	PushOverlaysToTop();
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Map_PopUp_Reward");
	mWidgetManager->AddBaseModal(m_levelofDayEntrance);
	mWidgetManager->SetFocus(m_levelofDayEntrance);
	gMessageRouter->Post(&Message::OpenUI, "LevelofDayEntrance");
	m_levelofDayEntrance->NormalInit(PT_FromCenter | PT_FromMiddle | PT_Scaled | PT_Fade);
	m_levelofDayEntrance->StartPop();
}

void LawnApp::ShowPlantAccessoryUI(int iInitTab, PlantTypePtr i_plantType)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Store_Open");
	if (m_plantAccessoryUI)
		KillPlantAccessoryUI();
	m_plantAccessoryUI = new PlantAccessoryUI(i_plantType);
	mWidgetManager->AddWidget(m_plantAccessoryUI);
	mWidgetManager->BringToFront(m_plantAccessoryUI);
	PushOverlaysToTop();
	mWidgetManager->AddBaseModal(m_plantAccessoryUI);
	mWidgetManager->SetFocus(m_plantAccessoryUI);
	if (iInitTab >= 0)
		m_plantAccessoryUI->ToPanel(iInitTab);
	m_plantAccessoryUI->TriggerTutorial();
}
