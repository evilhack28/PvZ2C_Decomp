//
//  LawnStringUpdater.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "LawnStringUpdater.h"
#include "PVZDB.h"
#include "ServerConfig.h"
#include "LawnApp.h"
#include "TodLib/TodStringFile.h"
#include "Crypt/SexyAES.h"

std::string GetFolder(Sexy::IFileDriver::PathType thePathType);

/////////////// Lifecycle ///////////////

LawnStringUpdater::LawnStringUpdater()
{
	m_retriesLeft = 0;
	m_fileInfoUrl = "";
	m_fileUrl = "";
	m_currentStage = LawnStringRequestStage_None;
	Init();
}

LawnStringUpdater::~LawnStringUpdater()
{
}

void LawnStringUpdater::Init()
{
	Sexy::RtDbTable* table = PVZDB::GetInstance().GetTable(PVZDB::TABLE_SERVER_CONFIG);
	LawnStringServerConfig* cfg = table->GetObjectForId(table->GetIdForAlias(Sexy::RtName(_S("LawnStringServerConfig"))))->CastChecked<LawnStringServerConfig>();
	m_fileInfoUrl = cfg->GetFileInfoURL();
	if (m_fileInfoUrl[m_fileInfoUrl.size() - 1] != '/')
		m_fileInfoUrl += "/";
	m_fileInfoUrl += "file_list.txt";
	m_fileUrl = cfg->GetFileURL();
	if (m_fileUrl[m_fileUrl.size() - 1] != '/')
		m_fileUrl += "/";
}

/////////////// Requests ///////////////

void LawnStringUpdater::CheckForUpdates(int i_retries)
{
	m_retriesLeft = i_retries;
	TryRequest(LawnStringRequestStage_GetFileInfo);
}

void LawnStringUpdater::ServiceRequestFailed(const Sexy::StructuredData*, const void* i_context)
{
	if (i_context == this)
		TryRequest(m_currentStage);
}

void LawnStringUpdater::TryRequest(LawnStringRequestStage i_stage)
{
	if (m_retriesLeft < 0)
	{
		OnRequestFinished("");
		return;
	}

	m_currentStage = i_stage;
	std::string url = (i_stage == LawnStringRequestStage_GetFileInfo) ? m_fileInfoUrl : m_fileUrl;
	Sexy::StructuredData request;
	request.BeginObject();
	request.AddString("url", url);
	request.AddInteger("timeout", 10);
	request.EndObject();
	Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->MakeRequest(&request, this, this);
	m_retriesLeft--;
}

void LawnStringUpdater::ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context)
{
	if (i_context != this)
		return;

	long statusCode = i_response->IntegerForPath("$.statusCode", -1);
	if (statusCode == -1 || statusCode == 200)
	{
		std::string response;
		response = i_response->StringForPath("$.response", "");
		OnRequestFinished(response);
	}
	else
	{
		ServiceRequestFailed(i_response, this);
	}
}

void LawnStringUpdater::ServiceRequestCompleted(ImageLib::Image*&, const void*)
{
}

void LawnStringUpdater::ServiceRequestCompleted(const Sexy::Buffer*, const void*)
{
}

std::string LawnStringUpdater::GetLocalLawnStringMd5()
{
	std::string cachedPath = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + m_fileInfo.m_fileName;
	std::string defaultPath = gLawnApp->mResourceManager->GetLocaleFolder(true) + "properties/LawnStrings.txt";
	std::string md5 = "";
	Sexy::Buffer buffer;
	bool ok;
	if (gSexyAppBase->FileExists(cachedPath))
		ok = gSexyAppBase->ReadBufferFromFile(cachedPath, &buffer);
	else
		ok = gSexyAppBase->ReadBufferFromFile(defaultPath, &buffer);
	if (ok)
		md5 = MD5(buffer.GetDataPtr(), buffer.GetDataLen()).toString();
	return md5;
}

void LawnStringUpdater::OnRequestFinished(std::string i_json)
{
	if (i_json == "")
	{
		gLawnApp->LoadLocalLawnStrings();
	}
	else if (m_currentStage == LawnStringRequestStage_GetFileInfo)
	{
		std::string decrypted = "";
		DecryptString2(i_json.c_str(), decrypted, (int)strlen(i_json.c_str()));
		NetworkLawnStringInfo info;
		if (!info.SerializeJson(decrypted))
			return;
		m_fileInfo.m_fileName = info.m_fileName;
		m_fileInfo.m_md5 = info.m_md5;
		std::string localMd5 = GetLocalLawnStringMd5();
		if (localMd5 != m_fileInfo.m_md5)
		{
			m_fileUrl = m_fileInfo.m_fileName;
			TryRequest(LawnStringRequestStage_GetFile);
		}
		else
		{
			gLawnApp->LoadLocalLawnStrings();
		}
	}
	else
	{
		std::string decrypted = "";
		DecryptString2(i_json.c_str(), decrypted, (int)strlen(i_json.c_str()));
		std::string path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + m_fileInfo.m_fileName;
		Sexy::Buffer buffer;
		buffer.SetData((const uchar*)decrypted.data(), decrypted.size());
		if (gSexyAppBase->WriteBufferToFile(path, &buffer))
			TodStringListLoad(path.c_str());
	}
}
