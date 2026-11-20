//
//  MainMenu.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "MainMenu.h"
#include "LawnApp.h"
#include "GameEventMgr.h"
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

bool MainMenu::NeedDecompressRsbsExtra()
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

