//
//  ContentDownloader.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-03.
//

#include "ContentDownloader.h"

#include "LawnApp.h"
#include "DebugLog.h"
#include "GameEventMgr.h"
#include "SexyAppFramework/IHttpDriver.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "TodLib/TodStringFile.h"
#include "TimeMgr.h"

ContentDownloader::ContentDownloader()
	: m_delegate(NULL)
	, m_currentDownloadRequestId(-1)
{
	Reset();
}

ContentDownloader::~ContentDownloader()
{
}

void ContentDownloader::Reset()
{
	m_wasDownloadSuccessful = false;
	m_wasDownloadCancelled = false;
	m_progress = 0.0f;
	m_currentPath = 0;
	m_retryTime = PVZ_EOT();
	m_allowRetries = true;
	m_paths.clear();
	m_downloadUpdateErrorMsg = L"";
	m_lastURL = "";
	if (m_currentDownloadRequestId != -1)
		Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->CancelRequest(m_currentDownloadRequestId);
	m_currentDownloadRequestId = -1;
}

void ContentDownloader::SetAllowRetries(bool i_enabled)
{
	m_allowRetries = i_enabled;
	m_retryTime = PVZ_EOT();
}

bool ContentDownloader::IsActive()
{
	return m_currentDownloadRequestId != -1;
}

const std::string& ContentDownloader::GetCurrentURL()
{
	return m_lastURL;
}

void ContentDownloader::setDelegate(ContentDownloaderDelegateProtocol* delegate)
{
	m_delegate = delegate;
}

void ContentDownloader::StartDownload(const std::vector<DownloadPath>& i_paths)
{
	m_wasDownloadCancelled = false;
	if (i_paths.empty())
	{
		m_downloadUpdateErrorMsg = L"[";
		Message::PatchEvent("failed", -100005);
		m_wasDownloadSuccessful = false;
		return;
	}

	m_paths = i_paths;
	m_currentPath = 0;
	m_progress = 0.0f;
	downloadPath(m_paths[0]);
	Message::PatchEvent("downloading", 0);
}

void ContentDownloader::downloadPath(const DownloadPath& i_path)
{
	m_lastURL = i_path.URL;
	m_downloadUpdateErrorMsg = L"";
	m_retryTime = PVZ_EOT();

	if (!gLawnApp->FileExists(i_path.SavePath))
	{
		Sexy::StructuredData data;
		data.BeginObject();
		data.AddString("url", i_path.URL);
		data.AddBoolean("resumable", true);
		data.AddString("targetFilePath", i_path.SavePath);
		data.AddBoolean("disableIfRangeHeader", true);
		data.AddBoolean("slackCerts", true);
		data.AddString("trace", Sexy::StrFormat("downloading %s...", i_path.URL.c_str()).c_str());
		data.EndObject();

		m_currentDownloadRequestId = Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->MakeRequest(&data, this, this);
	}
	else
	{
		onDownloadCompleted(i_path.SavePath);
	}
}

void ContentDownloader::Update()
{
	if (m_allowRetries)
	{
		if (!m_downloadUpdateErrorMsg.empty() && m_retryTime == PVZ_EOT())
			m_retryTime = PVZ_RealT() + 30.0f;

		if (PVZ_RealT() > m_retryTime)
		{
			if (gLawnApp->IsConnected())
				downloadPath(m_paths[m_currentPath]);
			else
				m_retryTime = PVZ_RealT() + 30.0f;
		}
	}
	else
	{
		m_retryTime = PVZ_EOT();
	}
}

void ContentDownloader::onDownloadCompleted(const std::string& i_file)
{
	if (m_delegate && m_currentPath >= 0 && (size_t)m_currentPath < m_paths.size())
		m_delegate->FileDownloadSuccess(m_paths[m_currentPath]);

	m_currentPath++;
	m_currentDownloadRequestId = -1;

	if ((size_t)m_currentPath < m_paths.size())
	{
		downloadPath(m_paths[m_currentPath]);
		return;
	}

	m_wasDownloadSuccessful = true;
	m_progress = 1.0f;
	Message::PatchEvent("downloaded", 0);
	gMessageRouter->Post(&Message::ContentDownloaderFinished);
	if (m_delegate)
		m_delegate->ContentDownloaderFinished();
}

void ContentDownloader::onDownloadFailed(const SexyString& inDownloadErrorMsg, int i_errorID)
{
	m_downloadUpdateErrorMsg = inDownloadErrorMsg;
	Message::PatchEvent("failed", i_errorID);
	m_wasDownloadSuccessful = false;
	m_currentDownloadRequestId = -1;

	std::string log = Sexy::StrFormat("ContentDownloader::onDownloadFailed[%d]", i_errorID);
	gDebugLog->SendLog(log, DebugLog_NetMessage, DebugPath_File | DebugPath_NetWork);

	if (m_delegate && m_currentPath >= 0 && (size_t)m_currentPath < m_paths.size())
		m_delegate->ContentDownloaderFailed(m_paths[m_currentPath], "failed", i_errorID);
}

void ContentDownloader::ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context)
{
	if (i_context != this)
		return;
	onDownloadFailed(L"Unexpected content from server (got JSON).", -100001);
}

void ContentDownloader::ServiceRequestCompleted(ImageLib::Image*& i_image, const void* i_context)
{
	if (i_context != this)
		return;
	onDownloadFailed(L"Unexpected content from server (got an image).", -100002);
}

void ContentDownloader::ServiceRequestCompleted(const Sexy::Buffer* i_buffer, const void* i_context)
{
	if (i_context != this)
		return;
	onDownloadFailed(L"Should not get here. Should be using resumable download.", -100004);
}

void ContentDownloader::ServiceResumableRequestCompleted(const std::string& i_filePath, const void* i_context)
{
	if (i_context == this)
		onDownloadCompleted(i_filePath);
}

void ContentDownloader::ServiceProgressUpdate(uint64 inNumBytesDownloaded, uint64 inTotalBytes, const void* i_context)
{
	if (i_context != this)
		return;

	float frac = inTotalBytes != 0 ? (float)inNumBytesDownloaded / (float)inTotalBytes : 0.0f;

	m_progress = ((float)m_currentPath + frac) / (float)m_paths.size();

	if (m_delegate)
		m_delegate->ContentDownProgress(m_progress);
}

void ContentDownloader::ServiceRequestFailed(const Sexy::StructuredData* i_response, const void* i_context)
{
	if (i_context != this)
		return;

	int errorID = (int)i_response->IntegerForPath("$.errorID", 0);
	std::string error = i_response->StringForPath("$.error", "unknown error");

	std::string log = Sexy::StrFormat("ContentDownloader::ServiceRequestFailed[%d][%s]", errorID, error.c_str());
	gDebugLog->SendLog(log, DebugLog_NetMessage, DebugPath_File | DebugPath_NetWork);

	if (Sexy::gSexyApp->mHttpDriver->GetNetworkStatus() != Sexy::IHttpDriver::NET_NOT_REACHABLE)
	{
		if (errorID > 0)
			onDownloadFailed(Sexy::UTF8StringToWString(error), errorID + 10000);
		else
			onDownloadFailed(TodStringTranslate(_S("[DOWNLOAD_FAILED_BODY]")) + Sexy::StrFormat(_S(" (%d)"), errorID), errorID + 10000);
	}
	else
	{
		onDownloadFailed(_S("[DOWNLOAD_FAILED_BODY]"), -100003);
	}
}

void ContentDownloader::ServiceRequestCanceled(const void* context)
{
	m_wasDownloadCancelled = true;
	m_currentDownloadRequestId = -1;
	Message::PatchEvent("canceled", 0);
}
