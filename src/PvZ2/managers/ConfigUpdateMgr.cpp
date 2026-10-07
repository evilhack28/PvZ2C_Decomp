//
//  ConfigUpdateMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-07.
//

#include "SexyAppFramework/Common.h"

#include "ConfigUpdateMgr.h"
#include "LawnApp.h"
#include "PVZ2UIDialog.h"
#include "PrimeText_Game.h"
#include "PlatformInterface.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

/////////////// Lifecycle ///////////////

ConfigUpdateMgr::ConfigUpdateMgr()
{
	m_AssetsManagerEx = NULL;
	m_failCount = 0;
	m_updated = false;
	std::string cacheFolder = "";
	std::string externalDir = Android::Resources::GetExternalFilesDirectory((Sexy::AndroidAppDriver*)gLawnApp);
	cacheFolder = externalDir;
	gLawnApp->SetResumeCachedFolder(cacheFolder);
	cacheFolder += "config/";
	Sexy::MkDir(cacheFolder);
	Sexy::MkDir(m_storagePath + "rsb/");
	Sexy::MkDir(m_storagePath + "download/");
	m_storagePath = cacheFolder;
}

ConfigUpdateMgr::~ConfigUpdateMgr()
{
	if (m_AssetsManagerEx != NULL)
	{
		delete m_AssetsManagerEx;
		m_AssetsManagerEx = NULL;
	}
}

/////////////// Accessors ///////////////

bool ConfigUpdateMgr::IsUpdated() const
{
	return m_updated;
}

const char* ConfigUpdateMgr::GetRSBFileName() const
{
	return "DLCConfig.rsb";
}

/////////////// Logic ///////////////

void ConfigUpdateMgr::onRestart()
{
	gLawnApp->KillPVZ2Dialog();
	Android::Device::ExitApp();
}

void ConfigUpdateMgr::CheckUpdate()
{
	if (gLawnApp->IsConnected())
	{
		std::string manifestUrl = gLawnApp->mFileDriver->GetLoadDataPath() + "ConfigManifest.json";
		m_AssetsManagerEx = new (std::nothrow) AssetsManagerEx(manifestUrl, m_storagePath);
		m_AssetsManagerEx->setDelegate(this);
		if (__builtin_expect(m_AssetsManagerEx->getLocalManifest()->isLoaded(), 1))
		{
			m_AssetsManagerEx->update();
		}
		else
		{
			Sexy::OutputDebugStrF("Fail to update assets, step skipped.\n");
		}
	}
}

static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

void ConfigUpdateMgr::ForceRestart()
{
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(UIScaleNum(400), UIScaleNum(250));
	dialog->SetHeaderLabel(SexyString(L"[LUA_UPDATE_TIP]"));
	dialog->SetFooterLabel(SexyString(L"[CONFIG_UPDATE_RESTART]"));
	dialog->SetHeaderFont(PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface(), Sexy::Color(Sexy::Color::White));
	dialog->SetFooterFont(PrimeText_Game::Typeface_FZCuYuan_26->Typeface(), Sexy::Color(97, 52, 0, 255));
	dialog->AddButton(SexyString(L"[DIALOG_STRING_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &ConfigUpdateMgr::onRestart)));
}

void ConfigUpdateMgr::dispatchEvent(AssetsManagerEx* manager, EventCode code, float percent, float percentByFile, const std::string& assetId, const std::string& message, int curle_code, int curlm_code)
{
	switch (code)
	{
	case EventCode::ERROR_NO_LOCAL_MANIFEST:
		Sexy::OutputDebugStrF("No local manifest file found, skip assets update.\n");
		break;
	case EventCode::ERROR_DOWNLOAD_MANIFEST:
	case EventCode::ERROR_PARSE_MANIFEST:
		Sexy::OutputDebugStrF("Fail to download manifest file, update skipped.\n");
		break;
	case EventCode::ALREADY_UP_TO_DATE:
		Sexy::OutputDebugStrF("Already up to date. %s \n", message.c_str());
		break;
	case EventCode::ERROR_UPDATING:
		Sexy::OutputDebugStrF("ERROR_UPDATING Asset %s : %s \n", assetId.c_str(), message.c_str());
		break;
	case EventCode::UPDATE_FINISHED:
	{
		Sexy::OutputDebugStrF("Update finished. %s \n", message.c_str());
		if (m_AssetsManagerEx != NULL)
		{
			const AssetsManagerManifest* manifest = m_AssetsManagerEx->getLocalManifest();
			if (manifest != NULL && manifest->isLoaded() && manifest->isVersionLoaded())
			{
				std::string version = manifest->getVersion();
				UserPrefs::SetString("ConfigDLCVersion", version);
				UserPrefs::Synchronize();
				m_updated = true;
			}
		}
		break;
	}
	case EventCode::UPDATE_FAILED:
		Sexy::OutputDebugStrF("Update failed. %s \n", message.c_str());
		break;
	case EventCode::ERROR_DECOMPRESS:
		Sexy::OutputDebugStrF("ERROR_DECOMPRESS %s \n", message.c_str());
		break;
	}
}

void ConfigUpdateMgr::Init()
{
	gLawnApp->m_configDLCVersion = "1.0.0";
	if (gSexyAppBase->FileExists(m_storagePath + "download/" + GetRSBFileName()))
	{
		if (gSexyAppBase->FileExists(m_storagePath + "rsb/" + GetRSBFileName()))
		{
			gSexyAppBase->EraseFile(m_storagePath + "rsb/" + GetRSBFileName());
		}
		gSexyAppBase->RenameFile(m_storagePath + "download/" + GetRSBFileName(), m_storagePath + "rsb/" + GetRSBFileName());
	}
	std::string localVersion = UserPrefs::GetString("ConfigDLCVersion", "");
	if (localVersion.size() != 0)
	{
		std::string manifestUrl = gLawnApp->mFileDriver->GetLoadDataPath() + "ConfigManifest.json";
		AssetsManagerManifest manifest("");
		manifest.parse(manifestUrl);
		if (manifest.isLoaded() && manifest.isVersionLoaded())
		{
			std::string remoteVersion = manifest.getVersion();
			if (remoteVersion.size() != 0)
			{
				int remote = AssetsManagerManifest::getVersionToInt(remoteVersion);
				int local = AssetsManagerManifest::getVersionToInt(localVersion);
				if (remote < local)
				{
					std::string rsbPath = m_storagePath + "rsb/" + GetRSBFileName();
					if (gSexyAppBase->FileExists(rsbPath))
					{
						gLawnApp->m_configDLCVersion = localVersion;
						gLawnApp->mResourceManager->AddDLCRsb(m_storagePath + "rsb/", GetRSBFileName(), "properties\\resourcesDLCConfig.rton");
					}
				}
			}
		}
	}
}
