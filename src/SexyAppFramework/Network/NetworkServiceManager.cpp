//
//  NetworkServiceManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-17.
//
#include "SexyAppFramework/Common.h"
#include "NetworkServiceManager.h"
#include "AsyncTaskManager.h"
#include "ResumeRequestInfo.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

NetworkServiceManager::NetworkServiceManager()
	: mLogLevel(LOG_NONE)
	, mNextRequestId(1)
{
	AsyncTaskManager* taskManager = AsyncTaskManager::DefaultAsyncTaskManager();
	if (taskManager != NULL)
		mResumeRequestTaskManager = taskManager;
	else
		mResumeRequestTaskManager = new AsyncTaskManager();
	MkDir(ResumableRequestInfo::GetResumeCachedFolder());
	DeleteOldPartialFiles();
}

NetworkServiceManager::~NetworkServiceManager()
{
	delete mResumeRequestTaskManager;
	mResumeRequestTaskManager = NULL;
}
