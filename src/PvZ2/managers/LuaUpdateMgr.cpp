//
//  LuaUpdateMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-07.
//

#include "SexyAppFramework/Common.h"

#include "LuaUpdateMgr.h"
#include "LawnApp.h"
#include "TodLib/TodStringFile.h"
#include "PVZ2UIDialog.h"
#include "DebugLog.h"
#include "TodLib/TodCommon.h"
#include "PrimeText_Game.h"
#include "PlatformInterface.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

namespace Lua
{
class CLuaEngine
{
public:
	void DidFinishPrepair();
};
}

namespace Sexy
{
template<> Lua::CLuaEngine& LazySingleton<Lua::CLuaEngine>::GetInstance();
}

/////////////// Lifecycle ///////////////

LuaUpdateMgr::LuaUpdateMgr()
{
	m_waitingDLG = NULL;
	m_AssetsManagerEx = NULL;
	m_failCount = 0;
	m_bNeedUpdate = false;
	m_totalFileSize = 0;
	std::string cacheFolder = "";
	std::string externalDir = Android::Resources::GetExternalFilesDirectory((Sexy::AndroidAppDriver*)gLawnApp);
	cacheFolder = externalDir;
	gLawnApp->SetResumeCachedFolder(cacheFolder);
	cacheFolder += "lua/";
	Sexy::MkDir(cacheFolder);
	Sexy::MkDir(m_storagePath + "rsb/");
	Sexy::MkDir(m_storagePath + "download/");
	m_storagePath = cacheFolder;
}

LuaUpdateMgr::~LuaUpdateMgr()
{
	if (m_AssetsManagerEx != NULL)
	{
		delete m_AssetsManagerEx;
		m_AssetsManagerEx = NULL;
	}
}

/////////////// Accessors ///////////////

const char* LuaUpdateMgr::GetRSBFileName() const
{
	return "LuaAct.rsb";
}

bool LuaUpdateMgr::NeedUpdate() const
{
	return m_bNeedUpdate;
}

void LuaUpdateMgr::onWaitingDialogClose()
{
	m_waitingDLG = NULL;
}

/////////////// Logic ///////////////

void LuaUpdateMgr::onLuaUpdateCancel()
{
	gLawnApp->KillPVZ2Dialog();
	m_bNeedUpdate = false;
}

void LuaUpdateMgr::CheckUpdate()
{
	std::string manifestUrl = gLawnApp->mFileDriver->GetLoadDataPath() + "LuaManifest.json";
	m_AssetsManagerEx = new (std::nothrow) AssetsManagerEx(manifestUrl, m_storagePath);
	m_AssetsManagerEx->setDelegate(this);
	if (__builtin_expect(m_AssetsManagerEx->getLocalManifest()->isLoaded(), 1))
	{
		m_AssetsManagerEx->checkUpdate();
	}
	else
	{
		Sexy::OutputDebugStrF("Fail to update assets, step skipped.\n");
	}
}

void LuaUpdateMgr::Init()
{
	gLawnApp->m_luaDLCVersion = "1.0.0";
	LoadLuaRSB();
}

std::string LuaUpdateMgr::GetPackageRSBFilePath()
{
	std::string path = "";
	path = Android::Resources::GetExternalFilesDirectory((Sexy::AndroidAppDriver*)gLawnApp) + "/";
	if (gSexyAppBase->FileExists(path + GetRSBFileName() + ".smf"))
	{
		return path;
	}
	path = Android::Resources::GetUserDataFolder((Sexy::AndroidAppDriver*)gLawnApp) + "/";
	if (gSexyAppBase->FileExists(path + GetRSBFileName() + ".smf"))
	{
		return path;
	}
	return "";
}

void LuaUpdateMgr::LoadLuaRSB()
{
	std::string manifestUrl = gLawnApp->mFileDriver->GetLoadDataPath() + "LuaManifest.json";
	AssetsManagerManifest manifest("");
	manifest.parse(manifestUrl);
	if (manifest.isLoaded() && manifest.isVersionLoaded())
	{
		std::string version = manifest.getVersion();
		std::string localVersion = UserPrefs::GetString("LuaDLCNewVersion", "");
		std::string packagePath = GetPackageRSBFilePath();
		if (packagePath.size() != 0)
		{
			gLawnApp->m_luaDLCVersion = "Package_RSB";
			std::string rsbName = GetRSBFileName();
			rsbName += ".smf";
			gLawnApp->mResourceManager->AddDLCRsb(packagePath, rsbName, "properties\\resourcesLuaAct.rton");
			Sexy::LazySingleton<Lua::CLuaEngine>::GetInstance().DidFinishPrepair();
		}
	}
}

void LuaUpdateMgr::onLuaUpdateOK()
{
	gLawnApp->KillPVZ2Dialog();
	if (m_AssetsManagerEx != NULL)
	{
		m_AssetsManagerEx->update();
	}
	m_waitingDLG = gLawnApp->ShowWaitingDialog(TodStringTranslate(L"[LUA_UPDATE_TIP]"), 120, 250, 400);
	m_waitingDLG->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), Sexy::Color(Sexy::Color::White));
	m_waitingDLG->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_26->Typeface(), Sexy::Color(97, 52, 0, 255));
	m_waitingDLG->SetShowWaiting(false);
	m_waitingDLG->SetCloseCallBack(Sexy::Delegate0(Sexy::MakeDelegate(*this, &LuaUpdateMgr::onWaitingDialogClose)));
	m_waitingDLG->SetFooterLabel(SexyString(L"[DIALOG_WAITING]"));
}

static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

void LuaUpdateMgr::DoUpdate()
{
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
	dialog->SetHeaderLabel(SexyString(L"[LUA_UPDATE_TIP]"));
	dialog->SetFooterLabel(TodReplaceString(L"[LUA_UPDATE_CONTENT]", L"{NUMBER}", Sexy::StrFormat(L"%.1f", m_totalFileSize)));
	dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), Sexy::Color(Sexy::Color::White));
	dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_26->Typeface(), Sexy::Color(97, 52, 0, 255));
	dialog->SetBackgroundDarken(true, 0.5f);
	if (!gLawnApp->IsServiceAvailable(Service_ForceLua))
	{
		dialog->AddButton(SexyString(L"[LUA_UPDATE_CANCEL]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &LuaUpdateMgr::onLuaUpdateCancel)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_SECONDARY);
	}
	dialog->AddButton(SexyString(L"[LUA_UPDATE_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &LuaUpdateMgr::onLuaUpdateOK)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_PRIMARY);
}

void LuaUpdateMgr::dispatchEvent(AssetsManagerEx* manager, EventCode code, float percent, float percentByFile, const std::string& assetId, const std::string& message, int curle_code, int curlm_code)
{
	switch (code)
	{
	case EventCode::UPDATE_PROGRESSION:
		if (m_waitingDLG != NULL)
		{
			m_waitingDLG->SetFooterLabel(TodReplaceString(L"[LUA_UPDATE_DOWNLOADING]", L"{NUMBER}", UTF8StringToWString(message)));
		}
		break;
	case EventCode::ALREADY_UP_TO_DATE:
		Sexy::OutputDebugStrF("Already up to date. %s \n", message.c_str());
		m_bNeedUpdate = false;
		LoadLuaRSB();
		break;
	case EventCode::ERROR_UPDATING:
	{
		std::string log = Sexy::StrFormat("ERROR_UPDATING Asset %s_%s", assetId.c_str(), message.c_str());
		gDebugLog->SendLog(log, DebugLog_NetMessage, DebugPath_File | DebugPath_NetWork);
		break;
	}
	case EventCode::UPDATE_FINISHED:
	{
		Sexy::OutputDebugStrF("Update finished. %s \n", message.c_str());
		m_bNeedUpdate = false;
		gLawnApp->KillWaitingDialog();
		m_waitingDLG = NULL;
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
		dialog->SetHeaderLabel(SexyString(L"[LUA_UPDATE_TIP]"));
		dialog->SetFooterLabel(SexyString(L"[LUA_UPDATE_SUCCEED]"));
		dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), Sexy::Color(Sexy::Color::White));
		dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_26->Typeface(), Sexy::Color(97, 52, 0, 255));
		dialog->AddButton(SexyString(L"[DIALOG_STRING_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)));
		if (m_AssetsManagerEx != NULL)
		{
			const AssetsManagerManifest* manifest = m_AssetsManagerEx->getLocalManifest();
			if (manifest != NULL && manifest->isLoaded() && manifest->isVersionLoaded())
			{
				std::string version = manifest->getVersion();
				UserPrefs::SetString("LuaDLCNewVersion", version);
				UserPrefs::Synchronize();
			}
		}
		if (gSexyAppBase->FileExists(m_storagePath + "download/" + GetRSBFileName()))
		{
			if (gSexyAppBase->FileExists(m_storagePath + "rsb/" + GetRSBFileName()))
			{
				gSexyAppBase->EraseFile(m_storagePath + "rsb/" + GetRSBFileName());
			}
			gSexyAppBase->RenameFile(m_storagePath + "download/" + GetRSBFileName(), m_storagePath + "rsb/" + GetRSBFileName());
		}
		LoadLuaRSB();
		break;
	}
	case EventCode::ERROR_DECOMPRESS:
	{
		std::string log = Sexy::StrFormat("ERROR_DECOMPRESS %s", message.c_str());
		gDebugLog->SendLog(log, DebugLog_NetMessage, DebugPath_File | DebugPath_NetWork);
		break;
	}
	case EventCode::UPDATE_FAILED:
	case EventCode::ERROR_MD5:
	{
		std::string log = Sexy::StrFormat("Update Failed %s", message.c_str());
		gDebugLog->SendLog(log, DebugLog_NetMessage, DebugPath_File | DebugPath_NetWork);
		m_failCount++;
		if (m_failCount < 3)
		{
			gDebugLog->SendLog("downloadFailedAssets", DebugLog_NetMessage, DebugPath_File | DebugPath_NetWork);
			m_AssetsManagerEx->downloadFailedAssets();
		}
		else
		{
			gDebugLog->SendLog("Reach maximum fail count", DebugLog_NetMessage, DebugPath_File | DebugPath_NetWork);
			m_failCount = 0;
			m_bNeedUpdate = false;
			gLawnApp->KillWaitingDialog();
			m_waitingDLG = NULL;
			PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
			dialog->SetHeaderLabel(SexyString(L"[LUA_UPDATE_TIP]"));
			dialog->SetFooterLabel(SexyString(L"[LUA_UPDATE_FAIL]"));
			dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), Sexy::Color(Sexy::Color::White));
			dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_26->Typeface(), Sexy::Color(97, 52, 0, 255));
			dialog->AddButton(SexyString(L"[DIALOG_STRING_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)));
		}
		break;
	}
	case EventCode::NEW_VERSION_FOUND:
	{
		Sexy::OutputDebugStrF("new version found. \n");
		m_bNeedUpdate = true;
		const AssetsManagerManifest* remoteManifest = m_AssetsManagerEx->getRemoteManifest();
		if (remoteManifest != NULL && remoteManifest->isVersionLoaded())
		{
			m_totalFileSize = remoteManifest->getTotalFileSize();
		}
		break;
	}
	case EventCode::ERROR_PARSE_MANIFEST:
		gDebugLog->SendLog("Fail to parse manifest file", DebugLog_NetMessage, DebugPath_File | DebugPath_NetWork);
		break;
	case EventCode::ERROR_DOWNLOAD_MANIFEST:
		m_bNeedUpdate = false;
		LoadLuaRSB();
		break;
	case EventCode::ERROR_NO_LOCAL_MANIFEST:
		gDebugLog->SendLog("No local manifest file found", DebugLog_NetMessage, DebugPath_File | DebugPath_NetWork);
		break;
	}
}
