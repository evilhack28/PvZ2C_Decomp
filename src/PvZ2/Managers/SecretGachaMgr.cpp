//
//  SecretGachaMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SecretGachaMgr.h"
#include "gameNetWork/NetworkMsgProcess.h"
#include "gameNetWork/NetworkMgr.h"
#include "GameEventMgr.h"
#include "ActivityManager.h"
#include "LawnApp.h"
#include "PVZ2UIDialog.h"
#include "GachaMgr.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"


/////////////// Lifecycle ///////////////

SecretGachaMgr::SecretGachaMgr()
{
	m_delayDialog = false;
	m_requestTime = PVZ_EOT();
	gMessageRouter->Subscribe(Message::NotifyRefreshActivityList, Sexy::MakeDelegate(*this, &SecretGachaMgr::OnNotifyRefreshActivityList));
	gMessageRouter->Subscribe(Message::MsgErrorRequest, Sexy::MakeDelegate(*this, &SecretGachaMgr::OnNetworkError));
}

SecretGachaMgr::~SecretGachaMgr()
{
	gMessageRouter->Unsubscribe(this);
}

/////////////// Accessors ///////////////

const NetworkSecretGachaInfo& SecretGachaMgr::GetGachaInfo()
{
	return m_info;
}

void SecretGachaMgr::SetSelectId(int i_selectId)
{
	m_info.mainObjectId = i_selectId;
}

bool SecretGachaMgr::IsUIActive()
{
	return UISecretGacha::get() != nullptr;
}

void SecretGachaMgr::RemoveMainUI()
{
	UISecretGacha* ui = UISecretGacha::get();
	if (ui != nullptr)
		ui->removeFromParent();
}

/////////////// Logic ///////////////

void SecretGachaMgr::Update()
{
}

void SecretGachaMgr::OnNetworkError(int erroId, const std::string& i_reqID)
{
}

bool SecretGachaMgr::NeedInit()
{
	ActiveItem item = gActivityManager->GetActiveItem(Activity_SecretGacha);
	NetworkSecretGachaInfo info;
	return item.GetDataSerialized(info) && item.m_bOpen;
}

void SecretGachaMgr::RequestGachaInit()
{
	if (!gLawnApp->IsConnected())
	{
		SetDelayDialog(true);
	}
	else
	{
		INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
		std::vector<std::pair<int, int>> idList = { { Activity_SecretGacha, 1 } };
		process->RequestActivityList(idList, 0, false);
	}
}

void SecretGachaMgr::SyncActivityData(const NetworkSecretGachaInfo& i_data)
{
	m_info = i_data;
	time_t realTime = gLawnApp->GetRealBeijingTime();
	struct tm* now = gLawnApp->BeijingTime(&realTime);
	m_info.expireTime = now->tm_min * -60 + now->tm_hour * -3600 - now->tm_sec + 86400 + (int)gLawnApp->GetRealServerTime();
}

void SecretGachaMgr::PopDelayDialog()
{
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L"[NETWORK_NOT_CONNECTED_TITLE]"), SexyString(L"[NETWORK_NOT_CONNECTED_TEXT]"));
	dialog->AddButton(SexyString(L"[DIALOG_STRING_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)));
}

void SecretGachaMgr::CreateMainUI(const Rect& i_rect, Widget* i_parent)
{
	float width = INV_UI_S((float)i_rect.mWidth);
	float height = INV_UI_S((float)i_rect.mHeight);
	Rect rect(0, 0, (int)width, (int)height);
	UISecretGacha* ui = UISecretGacha::create(rect);
	i_parent->AddWidget(ui);
}
std::string SecretGachaMgr::GetScreenType()
{
	int width = 0;
	int height = 0;
	Android::Graphics::GetScreenSizeInPixels((Sexy::AndroidAppDriver*)gSexyAppBase->mAppDriver, &width, &height);
	float ratio = (float)width / (float)height;
	if (ratio >= 2.1f)
		return "Full";
	if (ratio >= 1.5f)
		return "Normal";
	return "Large";
}

void SecretGachaMgr::OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList)
{
	if (i_success)
	{
		if (changeList.find(Activity_SecretGacha) != changeList.end())
		{
			if (gLawnApp->IsStoreUIShowing())
				RefreshActivity();
		}
		return;
	}
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L""), SexyString(L"[GACHA_ACTIVITY_DATA_LOST]"));
	dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_SECONDARY);
}

void SecretGachaMgr::RefreshActivity()
{
	ActiveItem item = gActivityManager->GetActiveItem(Activity_SecretGacha);
	NetworkSecretGachaInfo info;
	if (!item.GetDataSerialized(info))
	{
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L""), SexyString(L"[GACHA_ACTIVITY_DATA_ERROR]"));
		dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_SECONDARY);
	}
	else if (item.m_bOpen)
	{
		SyncActivityData(info);
		gMessageRouter->Post(Message::NotifySyncActivityData, true);
		return;
	}
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L""), SexyString(L"[GACHA_ACTIVITY_CLOSED]"));
	dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_SECONDARY);
}

void SecretGachaMgr::InitTestData()
{
	NetworkSecretGachaInfo info;
	info.mainObjectId = 1015;
	info.subObjectIds.push_back(SecretGachaItem(1119, 10));
	info.subObjectIds.push_back(SecretGachaItem(1120, 10));
	info.subObjectIds.push_back(SecretGachaItem(1121, 10));
	info.subObjectIds.push_back(SecretGachaItem(1333, 10));
	info.subObjectIds.push_back(SecretGachaItem(1334, 10));
	info.subObjectIds.push_back(SecretGachaItem(1335, 10));
	info.drawPrice = 50;
	info.multiDrawPrice = 5000;
	info.mainObjectIds.push_back(info.mainObjectId);
	info.mainObjectIds.push_back(1037);
	info.mainObjectIds.push_back(1048);
	info.mainObjectIds.push_back(1039);
	info.mainObjectIds.push_back(1040);
	info.mainObjectIds.push_back(1041);
	time_t realTime = gLawnApp->GetRealBeijingTime();
	struct tm* now = gLawnApp->BeijingTime(&realTime);
	info.expireTime = now->tm_min * -60 + now->tm_hour * -3600 - now->tm_sec + 86400 + (int)gLawnApp->GetRealServerTime();
	SyncActivityData(info);
	gMessageRouter->Post(Message::NotifySyncActivityData, true);
}
