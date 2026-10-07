//
//  IdentifierMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "IdentifierMgr.h"
#include "LawnApp.h"
#include "MD5.h"
#include "PlatformInterface.h"
#include "DefineIDMgr.h"
#include "PVZ2UIDialog.h"
#include "TodLib/TodStringFile.h"
#include "PrimeText_Game.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "gameNetWork/NetworkMgr.h"
#include "gameNetWork/NetworkMsgProcess.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

/////////////// Statics ///////////////

static std::string s_keyUUID = "pvz2_uuid_";
static std::string s_keyAccessToken = "pvz2_access_token_";
static std::string s_keyVerify = "pvz2_verify_";
static std::string s_keyBind = "pvz2_bind_";
static std::string s_keyUUIDLogin = "pvz2_uuidlogin_";
static std::string s_fileUUID = ".ud_";
static std::string s_fileAccessToken = ".at_";
static std::string s_fileVerify = ".vy_";
static std::string s_fileBind = ".bd_";
static std::string s_fileUUIDLogin = ".ul_";
static std::string s_verifySalt = "B8109D8B6TCBE";

/////////////// Lifecycle ///////////////

IdentifierMgr::IdentifierMgr()
{
	m_uuid = "";
	m_access_token = "";
	m_verify = "";
	m_bind = false;
	m_initBind = false;
	m_BindTip = false;
	m_needUUIDLogin = "yes";
	m_state = IdentifierMgrState_Init;
	m_StorageHome = "";
	m_StorageData = "";
	m_packageName = Android::Util::GetPackageName();
}

IdentifierMgr::~IdentifierMgr()
{
}

/////////////// Accessors ///////////////

std::string IdentifierMgr::GetUUID()
{
	return m_uuid;
}

std::string IdentifierMgr::GetAccessToken()
{
	return m_access_token;
}

bool IdentifierMgr::IsBind()
{
	return m_bind;
}

bool IdentifierMgr::EnableBind()
{
	return true;
}

bool IdentifierMgr::haveBindTip()
{
	return m_BindTip;
}

void IdentifierMgr::setBindTip()
{
	m_BindTip = true;
}

bool IdentifierMgr::NeedUUIDLogin()
{
	return m_needUUIDLogin == "yes";
}

void IdentifierMgr::SetUUIDLogin(bool login)
{
	if (login)
		m_needUUIDLogin = "yes";
	else
		m_needUUIDLogin = "no";
	SaveToKeychain();
}

bool IdentifierMgr::IsRequestFinished()
{
	return m_state == IdentifierMgrState_Finished;
}

bool IdentifierMgr::IsRequestInit()
{
	return m_state == IdentifierMgrState_RequestInit;
}

bool IdentifierMgr::IsRequestCheck()
{
	return m_state == IdentifierMgrState_RequestCheck;
}

bool IdentifierMgr::IsRequestTimeOut()
{
	return m_state == IdentifierMgrState_TimeOut;
}

/////////////// Dialogs ///////////////

static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

void IdentifierMgr::onNotifyUUIDLogin(bool i_success)
{
}

void IdentifierMgr::onBindDialogClosed()
{
	gLawnApp->KillPVZ2Dialog();
	gMessageRouter->Post(&Message::UUIDDialogClosed);
}

void IdentifierMgr::onBindDoubleTipCancel()
{
	gLawnApp->KillPVZ2Dialog();
	TryBind();
}

void IdentifierMgr::onRestartApp()
{
	Android::Device::ExitApp();
}

/////////////// Requests ///////////////

void IdentifierMgr::TryIdentifierInit()
{
	NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestUUIDInit();
	m_state = IdentifierMgrState_RequestInit;
	m_TimeOut = PVZ_T();
}

void IdentifierMgr::TryIdentifierCheck()
{
	if (gLawnApp->IsConnected())
	{
		if (!VerifyMD5())
		{
			ResetKeychain();
			m_state = IdentifierMgrState_Error;
			return;
		}
		if (m_uuid.size() != 0 && m_access_token.size() != 0 && m_bind)
		{
			NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestUUIDCheck();
			m_state = IdentifierMgrState_RequestCheck;
			m_TimeOut = PVZ_T();
			return;
		}
	}
	m_state = IdentifierMgrState_Error;
}

void IdentifierMgr::Update()
{
	if (m_state == IdentifierMgrState_RequestCheck)
	{
		if (PVZ_T() > m_TimeOut + 12.0f)
		{
			m_TimeOut = PVZ_EOT();
			m_state = IdentifierMgrState_TimeOut;
		}
	}
	if (m_state == IdentifierMgrState_RequestInit)
	{
		if (PVZ_T() > m_TimeOut + 12.0f)
		{
			m_TimeOut = PVZ_EOT();
			m_state = IdentifierMgrState_Error;
			gMessageRouter->Post(&Message::UUIDDialogClosed);
		}
	}
}

/////////////// Keychain ///////////////

bool IdentifierMgr::VerifyMD5()
{
	bool valid = true;
	if (m_uuid.size() != 0 && m_access_token.size() != 0)
	{
		std::string joined = m_uuid + m_access_token;
		std::string salted = static_cast<std::string&&>(joined) + s_verifySalt;
		MD5 md5(salted);
		std::string digest = md5.toString();
		valid = m_verify == digest;
	}
	return valid;
}

/////////////// Local file ///////////////

std::string IdentifierMgr::ReadFromSaveFile(const std::string& path)
{
	if (gSexyAppBase->FileExists(path))
	{
		Sexy::Buffer buffer;
		if (!gSexyAppBase->ReadBufferFromFile(path, &buffer))
			return "";
		return buffer.ReadLine();
	}
	return "";
}

void IdentifierMgr::SaveToLoaclFile(const std::string& path, const std::string& content)
{
	Sexy::Buffer buffer;
	buffer.WriteBytes((const uchar*)content.c_str(), content.size());
	if (gSexyAppBase->FileExists(path))
		gSexyAppBase->EraseFile(path);
	gSexyAppBase->WriteBufferToFile(path, &buffer);
}

/////////////// Bind dialogs ///////////////

void IdentifierMgr::onBindTipCancel()
{
	gLawnApp->KillPVZ2Dialog();
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L"[SETTINGS_UUID_BIND_TITLE]"), SexyString(L"[UUID_BIND_CANCEL_SETTING_TIP]"));
	dialog->AddButton(SexyString(L"[DIALOG_STRING_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &IdentifierMgr::onBindDialogClosed)));
}

void IdentifierMgr::onBindTipOK()
{
	gLawnApp->KillPVZ2Dialog();
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(500), UIScaleNum(220));
	dialog->SetHeaderLabel(SexyString(L"[SETTINGS_UUID_BIND_TITLE]"));
	dialog->SetFooterLabel(SexyString(L"[UUID_BIND_TIP_DOUBLE_CONTENT]"));
	dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
	dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
	dialog->SetBackgroundDarken(true, 0.5f);
	dialog->AddButton(SexyString(L"[UUID_BIND_TIP_CANCEL]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &IdentifierMgr::onBindDoubleTipCancel)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_SECONDARY);
	dialog->AddButton(SexyString(L"[UUID_BIND_DOUBLE_TIP_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &IdentifierMgr::onBindDoubleTipOK)));
}

void IdentifierMgr::onBindDoubleTipOK()
{
	gLawnApp->KillPVZ2Dialog();
	m_initBind = false;
	if (m_uuid.size() == 0 || m_access_token.size() == 0)
	{
		NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestUUIDInit();
		m_state = IdentifierMgrState_RequestInit;
		m_initBind = true;
	}
	else
	{
		NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestUUIDBind();
	}
	m_TimeOut = PVZ_T();
	gLawnApp->ShowWaitingDialog(TodStringTranslate(L"[CONNECTING]"), 30, 300, 400);
}

void IdentifierMgr::TryBind()
{
	if (gLawnApp->IsConnectOnWifi() || gLawnApp->IsConnectedOnWWAN() || gSexyApp->mHttpDriver->GetNetworkStatus() == Sexy::IHttpDriver::NET_REACHABIE_ETHERNET)
	{
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(500), UIScaleNum(220));
		dialog->SetHeaderLabel(SexyString(L"[SETTINGS_UUID_BIND_TITLE]"));
		dialog->SetFooterLabel(SexyString(L"[UUID_BIND_TIP_CONTENT]"));
		dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), PrimeText_Game::Color_Generic_Title);
		dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface(), Sexy::Color(Sexy::Color::White));
		dialog->SetBackgroundDarken(true, 0.5f);
		dialog->AddButton(SexyString(L"[UUID_BIND_TIP_CANCEL]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &IdentifierMgr::onBindTipCancel)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_SECONDARY);
		dialog->AddButton(SexyString(L"[UUID_BIND_TIP_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &IdentifierMgr::onBindTipOK)));
	}
	else
	{
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L"[NETWORK_NOT_CONNECTED_TITLE]"), SexyString(L"[NETWORK_NOT_CONNECTED_TEXT]"));
		dialog->AddButton(SexyString(L"[DIALOG_STRING_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &IdentifierMgr::onBindDialogClosed)));
	}
}

/////////////// Notifications ///////////////

void IdentifierMgr::onNotifyUUIDInit(bool i_success, const std::string& uuid, const std::string& access_token)
{
	if (i_success)
	{
		m_state = IdentifierMgrState_RequestInitFinished;
		m_uuid = uuid;
		m_access_token = access_token;
		m_verify = MD5(m_uuid + m_access_token + s_verifySalt).toString();
		SaveToKeychain();
		if (m_initBind)
		{
			NetworkMgr::Instance()->GetNewNetWorkProcess()->RequestUUIDBind();
			m_initBind = false;
		}
	}
	else
	{
		m_state = IdentifierMgrState_Error;
		gLawnApp->KillWaitingDialog();
		gMessageRouter->Post(&Message::UUIDDialogClosed);
	}
}

void IdentifierMgr::onNotifyUUIDCheck(int result, const std::string& access_token)
{
	switch (result)
	{
	case 0:
	{
		m_access_token = access_token;
		m_verify = MD5(m_uuid + m_access_token + s_verifySalt).toString();
		SaveToKeychain();
		m_state = IdentifierMgrState_Finished;
		break;
	}
	case 20004:
	case 20005:
		m_state = IdentifierMgrState_Error;
		break;
	case 20007:
	{
		ResetKeychain();
		DefineIDMgr::GetInstance().ClearSaveDefineID();
		m_state = IdentifierMgrState_Error;
		Android::UI::ShowAlertDialog("设备解绑成功", "请切换WIFI状态后，重启手机，再次登录游戏！", "确定", true);
		Sexy::SexySleep(8000);
		Android::Device::ExitApp();
		break;
	}
	default:
		m_state = IdentifierMgrState_Finished;
		break;
	}
}

void IdentifierMgr::onNotifyUUIDBind(bool i_success)
{
	gLawnApp->KillWaitingDialog();
	if (i_success)
	{
		m_state = IdentifierMgrState_Finished;
		m_bind = true;
		SaveToKeychain();
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L"[SETTINGS_UUID_BIND_TITLE]"), SexyString(L"[UUID_BIND_SUCCEED]"));
		dialog->AddButton(SexyString(L"[UUID_BIND_SUCCEED_TIP]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &IdentifierMgr::onRestartApp)));
	}
	else
	{
		m_state = IdentifierMgrState_Error;
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L"[SETTINGS_UUID_BIND_TITLE]"), SexyString(L"[UUID_BIND_FAIL]"));
		dialog->AddButton(SexyString(L"[DIALOG_STRING_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &IdentifierMgr::onBindDialogClosed)));
	}
}

/////////////// UUID ///////////////

std::string IdentifierMgr::GenerateLocalUUID()
{
	Sexy::SRand(time(NULL));
	time_t now = time(NULL);
	std::stringstream stream(std::ios_base::out | std::ios_base::in);
	stream << now;
	std::string timeStamp = stream.str();
	std::string defineId = DefineIDMgr::GetInstance().GetUserDefineID();
	if (defineId.empty())
		defineId = DefineIDMgr::GetInstance().GetNewUserDefineID();
	if (timeStamp.size() > 4 && defineId.size() > 4)
		timeStamp.replace(0, 4, defineId.substr(0, 4));
	m_uuid = "A" + timeStamp + Sexy::StrFormat("%08x", Sexy::Rand());
	SaveToKeychain();
	return m_uuid;
}

void IdentifierMgr::SaveToKeychain()
{
	if (m_uuid.size() != 0)
	{
		SaveToLoaclFile(m_StorageHome + s_fileUUID + m_packageName, m_uuid);
		SaveToLoaclFile(m_StorageData + s_fileUUID + m_packageName, m_uuid);
		UserPrefs::SetString(s_keyUUID + m_packageName, m_uuid);
	}
	if (m_access_token.size() != 0)
	{
		SaveToLoaclFile(m_StorageHome + s_fileAccessToken + m_packageName, m_access_token);
		SaveToLoaclFile(m_StorageData + s_fileAccessToken + m_packageName, m_access_token);
		UserPrefs::SetString(s_keyAccessToken + m_packageName, m_access_token);
	}
	if (m_verify.size() != 0)
	{
		SaveToLoaclFile(m_StorageHome + s_fileVerify + m_packageName, m_verify);
		SaveToLoaclFile(m_StorageData + s_fileVerify + m_packageName, m_verify);
		UserPrefs::SetString(s_keyVerify + m_packageName, m_verify);
	}
	if (m_bind)
	{
		SaveToLoaclFile(m_StorageHome + s_fileBind + m_packageName, "true");
		SaveToLoaclFile(m_StorageData + s_fileBind + m_packageName, "true");
		UserPrefs::SetString(s_keyBind + m_packageName, "true");
	}
	if (m_needUUIDLogin.size() != 0)
	{
		SaveToLoaclFile(m_StorageHome + s_fileUUIDLogin + m_packageName, m_needUUIDLogin);
		SaveToLoaclFile(m_StorageData + s_fileUUIDLogin + m_packageName, m_needUUIDLogin);
		UserPrefs::SetString(s_keyUUIDLogin + m_packageName, m_needUUIDLogin);
	}
}

void IdentifierMgr::ResetKeychain()
{
	UserPrefs::SetBool("BindTip", false);
	UserPrefs::SetString(s_keyUUID + m_packageName, "");
	UserPrefs::SetString(s_keyAccessToken + m_packageName, "");
	UserPrefs::SetString(s_keyVerify + m_packageName, "");
	UserPrefs::SetString(s_keyBind + m_packageName, "");
	UserPrefs::SetString(s_keyUUIDLogin + m_packageName, "yes");
	if (gSexyAppBase->FileExists(m_StorageHome + s_fileUUID + m_packageName))
		gSexyAppBase->EraseFile(m_StorageHome + s_fileUUID + m_packageName);
	if (gSexyAppBase->FileExists(m_StorageData + s_fileUUID + m_packageName))
		gSexyAppBase->EraseFile(m_StorageData + s_fileUUID + m_packageName);
	if (gSexyAppBase->FileExists(m_StorageHome + s_fileAccessToken + m_packageName))
		gSexyAppBase->EraseFile(m_StorageHome + s_fileAccessToken + m_packageName);
	if (gSexyAppBase->FileExists(m_StorageData + s_fileAccessToken + m_packageName))
		gSexyAppBase->EraseFile(m_StorageData + s_fileAccessToken + m_packageName);
	if (gSexyAppBase->FileExists(m_StorageHome + s_fileVerify + m_packageName))
		gSexyAppBase->EraseFile(m_StorageHome + s_fileVerify + m_packageName);
	if (gSexyAppBase->FileExists(m_StorageData + s_fileVerify + m_packageName))
		gSexyAppBase->EraseFile(m_StorageData + s_fileVerify + m_packageName);
	if (gSexyAppBase->FileExists(m_StorageHome + s_fileBind + m_packageName))
		gSexyAppBase->EraseFile(m_StorageHome + s_fileBind + m_packageName);
	if (gSexyAppBase->FileExists(m_StorageData + s_fileBind + m_packageName))
		gSexyAppBase->EraseFile(m_StorageData + s_fileBind + m_packageName);
	if (gSexyAppBase->FileExists(m_StorageHome + s_fileUUIDLogin + m_packageName))
		gSexyAppBase->EraseFile(m_StorageHome + s_fileUUIDLogin + m_packageName);
	if (gSexyAppBase->FileExists(m_StorageData + s_fileUUIDLogin + m_packageName))
		gSexyAppBase->EraseFile(m_StorageData + s_fileUUIDLogin + m_packageName);
}

/////////////// Init ///////////////

void IdentifierMgr::Init()
{
	std::string storageDir = Android::Resources::GetExternalStorageDirectory((Sexy::AndroidAppDriver*)gLawnApp);
	m_StorageHome = storageDir + "/" + ".pzir/";
	m_StorageData = storageDir + "/" + "Android/data/.zp2ir/";
	Sexy::MkDir(m_StorageHome);
	Sexy::MkDir(m_StorageData);
	if (gLawnApp->IsPlatformHD() && m_packageName.size() != 0)
	{
		if (!(gSexyAppBase->FileExists(m_StorageHome + s_fileUUID + m_packageName) && gSexyAppBase->FileExists(m_StorageHome + s_fileAccessToken + m_packageName) && gSexyAppBase->FileExists(m_StorageHome + s_fileVerify + m_packageName) && gSexyAppBase->FileExists(m_StorageHome + s_fileBind + m_packageName)))
		{
			std::string strippedName = m_packageName;
			size_t pos = strippedName.find("cthd", 0);
			while (pos != std::string::npos)
			{
				strippedName.replace(pos, 4, "");
				pos = strippedName.find("cthd", 0);
			}
			if (gSexyAppBase->FileExists(m_StorageHome + s_fileUUID + strippedName) && gSexyAppBase->FileExists(m_StorageHome + s_fileAccessToken + strippedName) && gSexyAppBase->FileExists(m_StorageHome + s_fileVerify + strippedName) && gSexyAppBase->FileExists(m_StorageHome + s_fileBind + strippedName))
				m_packageName = strippedName;
		}
	}
	m_uuid = ReadFromSaveFile(m_StorageHome + s_fileUUID + m_packageName);
	if (m_uuid.size() == 0)
	{
		m_uuid = ReadFromSaveFile(m_StorageData + s_fileUUID + m_packageName);
		if (m_uuid.size() == 0)
			m_uuid = UserPrefs::GetString(s_keyUUID + m_packageName, "");
	}
	m_access_token = ReadFromSaveFile(m_StorageHome + s_fileAccessToken + m_packageName);
	if (m_access_token.size() == 0)
	{
		m_access_token = ReadFromSaveFile(m_StorageData + s_fileAccessToken + m_packageName);
		if (m_access_token.size() == 0)
			m_access_token = UserPrefs::GetString(s_keyAccessToken + m_packageName, "");
	}
	m_verify = ReadFromSaveFile(m_StorageHome + s_fileVerify + m_packageName);
	if (m_verify.size() == 0)
	{
		m_verify = ReadFromSaveFile(m_StorageData + s_fileVerify + m_packageName);
		if (m_verify.size() == 0)
			m_verify = UserPrefs::GetString(s_keyVerify + m_packageName, "");
	}
	{
		std::string bindFlag = ReadFromSaveFile(m_StorageHome + s_fileBind + m_packageName);
		if (bindFlag.size() == 0)
		{
			bindFlag = ReadFromSaveFile(m_StorageData + s_fileBind + m_packageName);
			if (bindFlag.size() == 0)
			{
				bindFlag = UserPrefs::GetString(s_keyBind + m_packageName, "");
				if (bindFlag.size() == 0)
					goto skipBind;
			}
		}
		m_bind = true;
skipBind:;
	}
	m_needUUIDLogin = ReadFromSaveFile(m_StorageHome + s_fileUUIDLogin + m_packageName);
	if (m_needUUIDLogin.size() == 0)
	{
		m_needUUIDLogin = ReadFromSaveFile(m_StorageData + s_fileUUIDLogin + m_packageName);
		if (m_needUUIDLogin.size() == 0)
			m_needUUIDLogin = UserPrefs::GetString(s_keyUUIDLogin + m_packageName, "yes");
	}
	gMessageRouter->Subscribe(&Message::NotifyUUIDBind, Sexy::MakeDelegate(*this, &IdentifierMgr::onNotifyUUIDBind));
	gMessageRouter->Subscribe(&Message::NotifyUUIDLogin, Sexy::MakeDelegate(*this, &IdentifierMgr::onNotifyUUIDLogin));
	gMessageRouter->Subscribe(&Message::NotifyUUIDInit, Sexy::MakeDelegate(*this, &IdentifierMgr::onNotifyUUIDInit));
	gMessageRouter->Subscribe(&Message::NotifyUUIDCheck, Sexy::MakeDelegate(*this, &IdentifierMgr::onNotifyUUIDCheck));
	m_TimeOut = PVZ_EOT();
}
