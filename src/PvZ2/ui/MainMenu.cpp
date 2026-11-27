//
//  MainMenu.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "MainMenu.h"
#include "LawnApp.h"
#include "ScaledApp.h"
#include "GameEventMgr.h"
#include "TGALogMgr.h"
#include "AudioMgr.h"
#include "TutorialMgr.h"
#include "gameNetWork/androidNetworkMsgProcess.h"
#include "SexyAppFramework/Crypt/SexyZlib.h"
#include "ConfigUpdateMgr.h"
#include "iosExtras.h"
#include "UIPrivacyDialog.h"
#include "GameCommon.h"
#include "StringHelper.h"
#include "ConfirmUrlButtonExtra.h"
#include "PrimeText_Game.h"
#include "IdentityMessages.h"
#include "OfflineBoard.h"
#include "AccountRemove.h"
#include "Social/Widgets/AccountBindDialog.h"
#include "SettingsDialog.h"
#include "PopAnimRig.h"
#include "NetworkItemMgr.h"
#include "NetworkProfileMgr.h"
#include "iCloud/ProfileSummaryComparer.h"
#include "LawnStringUpdater.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"
#include "MainMenu.h"
#include "MainMenu.h"

/////////////// Accessors ///////////////

float MainMenu::GetFirstDecompressTotalAmount()
{
	return 0.2f;
}

float MainMenu::GetSecondDecompressTotalAmount()
{
	return 0.8f;
}

__attribute__((noclone, noinline)) static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

void MainMenu::SetBindBtnEnable(bool show)
{
	if (m_bindUniqueIDButton)
		m_bindUniqueIDButton->SetVisible(show);
}

/////////////// Logic ///////////////

void MainMenu::gotoSystemSetting()
{
}

void MainMenu::TouchEnded(const Sexy::Touch& i_touch)
{
}

void MainMenu::onUploadFirstTimeFinish(bool i_success)
{
	 MainMenu::uploadLocalProfile();
}

void MainMenu::startGame()
{
	 MainMenu::tryStartGame();
}

void MainMenu::ScrollLeft()
{
	m_scrollingPaneWidget->ScrollLeft();
}

void MainMenu::onCloseNetworkErrorDialog()
{
	gLawnApp->KillPVZ2Dialog();
}

void MainMenu::reloadData()
{
	gMessageRouter->Post(Message::ForceReloadData);
}

void MainMenu::OnCheckMD5Failed()
{
	gLawnApp->KillPVZ2Dialog();
	Android::Device::ExitApp();
}

void MainMenu::checkOfflineNotice()
{
	LazySingleton<OfflineBoardMgr>::GetInstance().CheckForNotice();
	LazySingleton<LawnStringUpdater>::GetInstance().CheckForUpdates(1);
}

bool MainMenu::NeedCreateRedeemButton()
{
	return gLawnApp->GetPlatform() == 113;
}

void MainMenu::retryConnect()
{
	gLawnApp->KillPVZ2Dialog();
	m_hasWarningDialog = false;
}

void MainMenu::onUseLocalStorage()
{
	gLawnApp->KillPVZ2Dialog();
	startGame();
}

void MainMenu::onLoginComplete()
{
	gLawnApp->SetQiHooLogin(true);
	syncProfileSummaryWithServer();
}

void MainMenu::tryStartGame()
{
	if (NetworkItemMgr::GetInstance().HasNetworkCacheSyncComplete() || NetworkItemMgr::GetInstance().IsSyncComplete())
		NetworkProfileMgr::GetInstance().TrySync();
	else
		NetworkItemMgr::GetInstance().HandleSyncTask();
}

void MainMenu::closeDiffProfileSummary()
{
	if (m_profileSummaryComparer)
	{
		RemoveWidget(m_profileSummaryComparer);
		delete m_profileSummaryComparer;
		m_profileSummaryComparer = NULL;
	}
}

void MainMenu::onProfileListChanged()
{
	m_scrollingPaneWidget->Close();
	m_scrollingPaneWidget->SetDarkenLayer(false);
}

void MainMenu::updateBackgroundEffect()
{
	if (m_backgroundEffect)
		m_backgroundEffect->UpdateAnim(PVZ_T(), PVZ_Dt());
}

void MainMenu::createSettingsDialog()
{
	m_settingsDialog = new SettingsDialog();
	AddWidget(m_settingsDialog);
	gLawnApp->mWidgetManager->AddBaseModal(m_settingsDialog);
}

void MainMenu::CreateComplainDialog()
{
	m_pComplainDialog = new ComplainDialog();
	AddWidget(m_pComplainDialog);
	gLawnApp->mWidgetManager->AddBaseModal(m_pComplainDialog);
}

void MainMenu::CreateAgeTipDialog()
{
	m_ageTipDialog = new AgeTipDialog();
	AddWidget(m_ageTipDialog);
	gLawnApp->mWidgetManager->AddBaseModal(m_ageTipDialog);
}

void MainMenu::showDiffProfileSummary()
{
	if (!m_profileSummaryComparer)
	{
		m_profileSummaryComparer = new ProfileSummaryComparer(true);
		AddWidget(m_profileSummaryComparer);
	}
}

void MainMenu::createProfilesDialog()
{
	m_scrollingPaneWidget->SetDarkenLayer(true);
	m_scrollingPaneWidget->ScrollRight(new ProfilesDialog());
	BringToFront(m_scrollingPaneWidget);
}

void MainMenu::createAccountBindDialog()
{
	m_accountBindDialog = new AccountBindDialog();
	AddWidget(m_accountBindDialog);
	gLawnApp->mWidgetManager->AddBaseModal(m_accountBindDialog);
	m_accountBindDialog->Move((mWidth - m_accountBindDialog->mWidth) / 2, (mHeight - m_accountBindDialog->mHeight) / 2);
}

void MainMenu::onFinishCheckAccount(bool i_success)
{
	if (i_success)
	{
		if (m_settingsDialog && m_settingsDialog->mVisible)
		{
			RemoveWidget(m_settingsDialog);
			gLawnApp->mWidgetManager->RemoveBaseModal(m_settingsDialog);
			delete m_settingsDialog;
			m_settingsDialog = NULL;
		}
		continuePressStartGame();
	}
	else
	{
		AccountRemoveMgr::GetInstance().DisplayUI();
	}
}

void MainMenu::CreateWelcomeDialog(PlayerInfoPtr i_playerInfo)
{
	m_scrollingPaneWidget->ScrollRight(new EditProfileWidget(i_playerInfo));
	BringToFront(m_scrollingPaneWidget);
}

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}


void MainMenu::playBackgroundEffect()
{
	LawnApp* aApp = gLawnApp;
	bool aSpecial = aApp->IsUsingSpecialBackground();
	Sexy::ResourceManager* aManager = aApp->mResourceManager;
	Sexy::RtWeakPtr<Sexy::PopAnim> aPopAnim = aManager->GetResourceForStringIdT<Sexy::PopAnim>(aSpecial ? "POPANIM_EFFECTS_MAINMENU_BACKGROUND_SPECIAL" : "POPANIM_EFFECTS_MAINMENU_BACKGROUND", true);
	m_backgroundEffect = PopAnimRig::CreateRigOutsideTable(aPopAnim, PopAnimRig::StaticGetClass());
	m_backgroundEffect->PlayAndContinue("idle");
	std::string aScreenType = ::GetScreenType();
	if (aScreenType == "Large")
	{
		float aScale = m_backgroundEffect->GetDrawScale();
		m_backgroundEffect->SetDrawScale(aScale * 0.8f);
	}
}

void MainMenu::createWelcomeDialogIfNeeded()
{
	Sexy::OutputDebugStrF("ACLog - createWelcomeDialogIfNeeded, profiles num : %d", Sexy::LazySingleton<ProfileMgr>::GetInstance().GetNumProfiles());
	if (Sexy::LazySingleton<ProfileMgr>::GetInstance().GetNumProfiles() == 0)
	{
		CreateWelcomeDialog(NULL);
	}
	else
	{
		createMainButtons();
		PlayerInfo* aProfile = Sexy::LazySingleton<ProfileMgr>::GetInstance().GetCurrentProfile();
		if (aProfile != NULL && !aProfile->HasSyncDataWithServer())
			gLawnApp->CheckNetWork(L"[NETWORK_NOT_CONNECTED_TITLE]", L"[NETWORK_NOT_CONNECTED_TEXT_FOR_SYNC_PLAYERINFO]");
	}
}

void MainMenu::onNetworkError(int erroId)
{
	if (!NetworkMgr::Instance()->GetNewNetWorkProcess()->IsLogined())
	{
		m_loginingiCloud = false;
		NetworkMgr::Instance()->GetNewNetWorkProcess()->SetICloudState(INetworkMsgProcess::INIT);
	}
	else if (gLawnApp->CheckNetWork(L"[NETWORK_NOT_CONNECTED_TITLE]", L"[NETWORK_NOT_CONNECTED_TEXT_FOR_SYNC_PLAYERINFO]"))
		gLawnApp->CheckNetWorkWifiIssue();
}


void MainMenu::onPlayerInfoSyncFinish()
{
	m_startedGame = true;
	gMessageRouter->Post(&Message::StartButtonPressed);
	gMessageRouter->Post(&Message::GameStart);
	TGALogMgr::GetInstance().Log("10001", std::vector<std::string>());
	if (gLawnApp->GetIsNewUser())
		TGALogMgr::GetInstance().Log("10000", std::vector<std::string>());
	PlayerInfo* aProfile = ProfileUtils::Profile();
	aProfile->UpdateLoginCount();
	gGameStateMgr->WaitForNetworkLoad();
	aProfile->RefreshRechargeCurrency();
	gLawnApp->ResetDatas();
}

void MainMenu::ShowBindUniqueIDHint()
{
	int aWidth = ::UIScaleNum(450);
	int aHeight = ::UIScaleNum(220);
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(aWidth, aHeight);
	dialog->SetHeaderLabel(L"[BIND_UNIQUE_ID_TITLE]");
	dialog->SetFooterLabel(L"[BIND_UNIQUE_ID_HINT]");
	dialog->SetFooterAlign(DS_ALIGN_CENTER_VERTICAL_MIDDLE);
	dialog->SetFooterBottomPadding(::UIScaleNum(2));
	dialog->SetBackgroundDarken(true, 0.5f);
	dialog->AddButton(L"[OVERVIEW_CONFIRM]", Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
}

void MainMenu::ShowBindUniqueID()
{
	int aWidth;
	int aHeight;
	if (IsDeviceIPad())
	{
		aWidth = ::UIScaleNum(600);
		aHeight = ::UIScaleNum(320);
	}
	else
	{
		aWidth = ::UIScaleNum(650);
		aHeight = ::UIScaleNum(320);
	}
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(aWidth, aHeight);
	dialog->SetHeaderLabel(L"[BIND_UNIQUE_ID_TITLE]");
	dialog->SetFooterLabel(L"[BIND_UNIQUE_ID_DESC]");
	dialog->SetFooterAlign(DS_ALIGN_LEFT_VERTICAL_MIDDLE);
	dialog->SetFooterBottomPadding(::UIScaleNum(2));
	dialog->SetBackgroundDarken(true, 0.5f);
	dialog->AddButton(L"[OVERVIEW_CONFIRM]", Sexy::Delegate0(Sexy::MakeDelegate(*this, &MainMenu::RequesBindUniqueID)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
}

void MainMenu::createPrivacyDialog()
{
	if (!UserPrefs::GetBool("AgreePravicy"))
		UISingletonDialog<UIPrivacyDialog>::ShowDialog();
}

void MainMenu::onSyncProfileToServer(bool i_success)
{
	if (!i_success)
		gLawnApp->CheckNetWork(L"[NETWORK_NOT_CONNECTED_TITLE]", L"[NETWORK_NOT_CONNECTED_TEXT_FOR_SYNC_PLAYERINFO]");
}

void MainMenu::onSyncPlayerInfoFinish(bool i_success)
{
	if (i_success)
		onPlayerInfoSyncFinish();
	else
		gLawnApp->CheckNetWork(L"[NETWORK_NOT_CONNECTED_TITLE]", L"[NETWORK_NOT_CONNECTED_TEXT_FOR_SYNC_PLAYERINFO]");
}

void MainMenu::onSyncProfileListFinish(bool i_success)
{
	if (i_success)
	{
		m_canCreateProfile = true;
		m_areAllProfileValid = true;
	}
	else
		gLawnApp->CheckNetWork(L"[NETWORK_NOT_CONNECTED_TITLE]", L"[NETWORK_NOT_CONNECTED_TEXT_FOR_SYNC_PLAYERINFO]");
}

void MainMenu::UpdateProfieName()
{
	if (ProfileMgr::GetInstancePtr()->getNeedUpdateUI())
	{
		ProfileMgr::GetInstancePtr()->closeNeedUpdateUI();
		std::wstring aName = L"";
		if (ProfileMgr::GetInstance().HasValidProfile())
		{
			aName = ProfileMgr::GetInstance().GetCurrentProfile()->GetName();
			m_changeNameButton->mLabel = aName;
		}
	}
}

void MainMenu::onSyncProfileFromServer(bool i_success)
{
	if (i_success)
	{
		PlayerInfo* aProfile = ProfileUtils::Profile();
		if (aProfile != NULL)
			aProfile->SyncOfflineDataFromOnlineData();
		startGame();
	}
	else
		gLawnApp->CheckNetWork(L"[NETWORK_NOT_CONNECTED_TITLE]", L"[NETWORK_NOT_CONNECTED_TEXT_FOR_SYNC_PLAYERINFO]");
}

int MainMenu::GetPreviousDecompressTime()
{
	int aTime = 0;
	for (int i = 0; i < m_currentDecompressIndex; i++)
		aTime = ceil(m_decompressPercents[i] * GetSecondDecompressTotalAmount() / (PVZ_Dt() * GetSecondDecompressTotalAmount() * 0.9f)) + aTime;
	return aTime;
}

int MainMenu::GetTotalDecompressTime()
{
	int aTime = 0;
	for (int i = 0; i < m_decompressPercents.size(); i++)
		aTime = ceil(m_decompressPercents[i] * GetSecondDecompressTotalAmount() / (PVZ_Dt() * GetSecondDecompressTotalAmount() * 0.9f)) + aTime;
	return aTime;
}

unsigned int MainMenu::GetTargetRSBDecompressSize(const std::string& i_rsbName)
{
	unsigned int aSize = 0;
	std::string aDir = gLawnApp->mFileDriver->GetLoadDataPath();
	std::string aPath = aDir + i_rsbName;
	Sexy::Buffer aBuffer;
	if (gSexyAppBase->ReadBufferFromFile(aPath, &aBuffer))
		aSize = SizeForUncompress2(aBuffer.GetDataPtr());
	return aSize;
}

void MainMenu::TryRedeem()
{
	ProfileMgr::GetInstance().GetPurchaseBroker()->CheckSpecialRedeem();
	m_waitingCD = PVZ_RealT() + 60.0f;
	if (m_redeemButton)
		m_redeemButton->SetDisabled(true);
}

void MainMenu::RequesBindUniqueID()
{
	std::string aUniqueID = ProfileMgr::GetInstance().GetPurchaseBroker()->GetUniqueID();
	std::string anAppName = gLawnApp->GetAppNameForiCloud();
	static_cast<androidNetworkMsgProcess*>(NetworkMgr::Instance()->GetNewNetWorkProcess())->ICloudRequestBindingUniqueID(anAppName, aUniqueID);
	gLawnApp->KillPVZ2Dialog();
}

void MainMenu::SplitString(std::wstring target, std::vector<std::wstring>& tokens, wchar_t delims)
{
	std::wstring aToken;
	for (size_t i = 0; i < target.length(); i++)
	{
		if (target[i] == delims)
		{
			tokens.push_back(aToken);
			aToken.clear();
		}
		else if (target[i] != L'\r' && target[i] != L'\n' && target[i] != L'\t')
			aToken.append(1, target[i]);
	}

	if (!aToken.empty())
		tokens.push_back(aToken);
}

void MainMenu::onNetworkProfileSyncFinish(bool i_success)
{
	if (i_success)
	{
		Sexy::LazySingleton<TutorialMgr>::GetInstance().TryProfileReset();
		NetworkMgr::Instance()->GetNewNetWorkProcess()->ICloudRequestSinglePlayerInfo();
	}
	else
		gLawnApp->ShowMessageDialog("[NETWORK_PROFILE_SYNC_FAILED_TITLE]", "[NETWORK_PROFILE_SYNC_FAILED_DESC]", Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)));
}

static CachedUIResourcePtr<Sexy::Image> sAgeTipsButtonImage("");

PVZ2UIButton* MainMenu::createAgeTipsButton(const int i_xPos, const MainMenuButtons i_button, Image* i_buttonIcon, const bool i_fromLeft)
{
	PVZ2UIButton* button = new PVZ2UIButton(i_button, this, L"");
	button->SetDialogStates(PVZ2UIImage(sAgeTipsButtonImage, PVZ2UIIMAGE_SINGLE_STRETCHED), PVZ2UIImage(sAgeTipsButtonImage, PVZ2UIIMAGE_SINGLE_STRETCHED));
	button->Resize(mWidth - sAgeTipsButtonImage->GetWidth() / 5 * 1.5, sAgeTipsButtonImage->GetHeight() / 5 * 0.5, sAgeTipsButtonImage->GetWidth() / 5, sAgeTipsButtonImage->GetHeight() / 5);
	i_buttonIcon->GetWidth();
	i_buttonIcon->GetHeight();
	button->mClip = false;
	AddWidget(button);
	return button;
}

static CachedUIResourcePtr<Sexy::Image> sRedeemButtonDownImage("");
static CachedUIResourcePtr<Sexy::Image> sRedeemButtonImage("");

void MainMenu::CreateComplainButton()
{
	if (!gLawnApp->IsServiceAvailable(Service_ShowGMInfoComplain))
		return;
	PVZ2UIButton* button = new PVZ2UIButton(MAINMENUBUTTON_COMPLAIN, this, L"[COMPLAIN_TITLE]");
	button->SetDialogStates(PVZ2UIImage(sRedeemButtonImage, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE), PVZ2UIImage(sRedeemButtonDownImage, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE));
	int aWidth = ::UIScaleNum(118);
	int aHeight = sRedeemButtonImage->GetHeight();
	button->Resize(mWidth - aWidth - ::UIScaleNum(20), ::UIScaleNum(412), aWidth, aHeight);
	AddWidget(button);
	if (gLawnApp->GetPlatform() == 27 || gLawnApp->GetPlatform() == 79)
		button->SetVisible(false);
}

void MainMenu::CreateRedeemButton()
{
	if (NeedCreateRedeemButton())
	{
		m_redeemButton = new PVZ2UIButton(MAINMENUBUTTON_REDEEM, this, L"[REDEEM_TITLE]");
		m_redeemButton->SetDialogStates(PVZ2UIImage(sRedeemButtonImage, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE), PVZ2UIImage(sRedeemButtonDownImage, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE));
		int aWidth = ::UIScaleNum(84);
		int aHeight = sRedeemButtonImage->GetHeight();
		m_redeemButton->Resize(mWidth - aWidth - ::UIScaleNum(240), ::UIScaleNum(412), aWidth, aHeight);
		AddWidget(m_redeemButton);
	}
}

PVZ2UIButton* MainMenu::createBottomButton(const int i_xPos, const MainMenuButtons i_button, Image* i_buttonIcon, const bool i_fromLeft)
{
	PVZ2UIButton* button = new PVZ2UIButton(i_button, this, L"");
	button->SetDialogStates(PVZ2UIImage(sRedeemButtonImage, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE), PVZ2UIImage(sRedeemButtonDownImage, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE));
	if (i_fromLeft)
		button->Resize(i_xPos + (i_buttonIcon->GetWidth() - ::UIScaleNum(68)) / 2, ::UIScaleNum(412), ::UIScaleNum(68), sRedeemButtonImage->GetHeight());
	else
		button->Resize(mWidth - i_xPos + (-i_buttonIcon->GetWidth() - ::UIScaleNum(68)) / 2, ::UIScaleNum(412), ::UIScaleNum(68), sRedeemButtonImage->GetHeight());
	int aX = (button->mWidth - i_buttonIcon->GetWidth()) / 2;
	int aY = (button->mHeight - i_buttonIcon->GetHeight()) / 2;
	PVZ2UIImage aIcon(i_buttonIcon, PVZ2UIIMAGE_SINGLE);
	button->AddImage(aIcon, Sexy::Rect(aX, aY, i_buttonIcon->GetWidth() / 2, i_buttonIcon->GetHeight() / 2));
	button->mClip = false;
	AddWidget(button);
	return button;
}

void MainMenu::InitDecompressImage()
{
	int aWidth = ::UIScaleNum(720);
	int aHeight = ::UIScaleNum(35);
	int aX = (mWidth - aWidth) / 2 - ::UIScaleNum(45);
	int aY = ::UIScaleNum(491);
	m_meterRect = Rect(aX, aY, aWidth, aHeight);
	m_meterImg = StringHelper::ToImage("IMAGE_UI_MAINMENU_LOADER_METER_DECOMPRESS");
	m_fillImg = StringHelper::ToImage("IMAGE_UI_MAINMENU_LOADER_METER_DECOMPRESS_FILL");
	int aOffsetX, aOffsetY, aShrinkX, aShrinkY;
	if (!m_meterImg || !m_fillImg)
	{
		aOffsetX = 30;
		aOffsetY = 30;
		aShrinkX = -60;
		aShrinkY = -60;
	}
	else
	{
		aOffsetX = (m_meterImg->GetWidth() - m_fillImg->GetWidth()) / 2;
		aOffsetY = (m_meterImg->GetHeight() - m_fillImg->GetHeight()) / 2;
		aShrinkX = aOffsetX * -2;
		aShrinkY = aOffsetY * -2;
	}
	m_fillRect = Rect(aX + aOffsetX, aY + aOffsetY, aWidth + aShrinkX, aHeight + aShrinkY);
	m_tips1Rect = Rect(::UIScaleNum(0), ::UIScaleNum(441), mWidth, ::UIScaleNum(55));
	m_tips2Rect = Rect(::UIScaleNum(0), ::UIScaleNum(531), mWidth, ::UIScaleNum(55));
	m_tipsPercentRect = Rect(m_meterRect.mX + m_meterRect.mWidth + ::UIScaleNum(0), ::UIScaleNum(489), ::UIScaleNum(60), ::UIScaleNum(55));
}

static CachedUIResourcePtr<Sexy::Image> sPlayButtonDownImage("");
static CachedUIResourcePtr<Sexy::Image> sChangeNameButtonImage("");
static CachedUIResourcePtr<Sexy::Image> sBottomButtonIconImage("");
static CachedUIResourcePtr<Sexy::Image> sChangeNameButtonIconImage("");
static CachedUIResourcePtr<Sexy::Image> sPlayButtonImage("");

void MainMenu::createMainButtons()
{
	if (NetworkItemMgr::GetInstance().HasNetworkCacheSyncComplete())
		NetworkItemMgr::GetInstance().SetAutoSyncComplete(true);
	m_startGameButton = new PVZ2UIButton(MAINMENUBUTTON_STARTGAME, this, L"[MAINMENU_PLAY]");
	m_startGameButton->SetDialogStates(PVZ2UIImage(sPlayButtonImage, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE), PVZ2UIImage(sPlayButtonDownImage, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE));
	int aPlayWidth = ::UIScaleNum(144);
	m_startGameButton->Resize((mWidth - aPlayWidth) / 2, ::UIScaleNum(412), aPlayWidth, sPlayButtonImage->GetHeight());
	AddWidget(m_startGameButton);
	ConfirmUrlButton* aConfirmUrlButton = new ConfirmUrlButton(19);
	float aScale = ::UIScaleNum(110);
	aConfirmUrlButton->Resize((mWidth - (int)(aScale * 2.93475f)) / 2, mHeight - aScale * 0.3875f, aScale * 2.93475f, aScale * 0.175f);
	AddWidget(aConfirmUrlButton);
	ConfirmUrlButtonExtra* aConfirmUrlButtonExtra = new ConfirmUrlButtonExtra(20, "http://filead.talkyun.com.cn/tw/twys.htm", "IMAGE_UI_GENERIC_URL_EXTRA");
	aConfirmUrlButtonExtra->Resize(::UIScaleNum(5), ::UIScaleNum(5), ::UIScaleNum(455), ::UIScaleNum(26));
	AddWidget(aConfirmUrlButtonExtra);
	CreateBindUniqueIDButton();
	int aNameWidth = ::UIScaleNum(292);
	std::wstring aProfileName = L"-Invalid-";
	if (ProfileMgr::GetInstance().GetCurrentProfile())
	{
		Sexy::OutputDebugStrF("ACLog - createMainButtons, profile name");
		aProfileName = ProfileMgr::GetInstance().GetCurrentProfile()->GetName();
	}
	else
		Sexy::OutputDebugStrF("ACLog - createMainButtons, profile name -Invalid-");
	m_changeNameButton = new PVZ2UIButton(MAINMENUBUTTON_CHANGENAME, this, aProfileName, Sexy::Color::Black);
	m_changeNameButton->SetFont(PrimeText_Game::Typeface_FZCuYuan_28->Typeface());
	PVZ2UIButton* aNameButton = m_changeNameButton;
	aNameButton->SetNormalStates(PVZ2UIImage(sChangeNameButtonImage, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE), PVZ2UIImage((Sexy::Image*)NULL, PVZ2UIIMAGE_SINGLE));
	aNameButton = m_changeNameButton;
	aNameButton->AddImage(PVZ2UIImage(sChangeNameButtonIconImage, PVZ2UIIMAGE_SINGLE), Sexy::Rect(aNameWidth - ::UIScaleNum(6) - sChangeNameButtonIconImage->GetWidth(), (::UIScaleNum(45) - sChangeNameButtonIconImage->GetHeight()) / 2, sChangeNameButtonIconImage->GetWidth(), sChangeNameButtonIconImage->GetHeight()));
	m_changeNameButton->Resize((mWidth - aNameWidth) / 2, ::UIScaleNum(354), aNameWidth, ::UIScaleNum(45));
	AddWidget(m_changeNameButton);
	createBottomButton(::UIScaleNum(148), MAINMENUBUTTON_SETTINGS, sBottomButtonIconImage, false);
	createAgeTipsButton(::UIScaleNum(160), MAINMENUBUTTON_AGE_TIP, sAgeTipsButtonImage, false);
	CreateComplainButton();
	CreateRedeemButton();
	checkOfflineNotice();
}
