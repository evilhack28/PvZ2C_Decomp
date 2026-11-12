//
//  SexyAppBase.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-27.
//

#include "SexyAppBase.h"
#include "AsyncTaskManager.h"
#include "AutoCrit.h"
#include "IAchievementDriver.h"
#include "IAppDriver.h"
#include "IDiagDriver.h"
#include "IGraphicsDriver.h"
#include "IHttpDriver.h"
#include "IInteractiveAudioDriver.h"
#include "ILeaderboardDriver.h"
#include "IProfileDriver.h"
#include "ISaveGameDriver.h"
#include "LeaderboardManager.h"
#include "MTRand.h"
#include "NetworkServiceManager.h"
#include "PakLib/PakInterface.h"
#include "PerfTimer.h"
#include "ProfileManager.h"
#include "RenderDevice.h"
#include "ResStreamsManager.h"
#include "ResumeRequestInfo.h"
#include "RtSerial.h"
#include "Widget.h"
#include "WidgetManager.h"

using namespace Sexy;

void SexyAppBase::SetString(const std::string& theId, const std::wstring& theValue)
{
	std::pair<StringWStringMap::iterator, bool> aResult = mStringProperties.insert(std::pair<const std::string, std::wstring>(theId, theValue));
	if (!aResult.second)
		aResult.first->second = theValue;

	int32 aNum = 0;
	if (StringToInt(theId, &aNum))
		mPopLoc.SetString(aNum, ToSexyString(theValue));
}

bool SexyAppBase::GetBoolean(const std::string& theId, bool theDefault)
{
	StringBoolMap::iterator anItr = mBoolProperties.find(theId);
	if (anItr != mBoolProperties.end())
		return anItr->second;

	return theDefault;
}

void SexyAppBase::SetBoolean(const std::string& theId, bool theValue)
{
	std::pair<StringBoolMap::iterator, bool> aResult = mBoolProperties.insert(std::pair<const std::string, bool>(theId, theValue));
	if (!aResult.second)
		aResult.first->second = theValue;
}

void SexyAppBase::ProcessSafeDeleteList()
{
	MTAutoDisallowRand aDisallowRand;

	WidgetSafeDeleteList::iterator anItr = mSafeDeleteList.begin();
	while (anItr != mSafeDeleteList.end())
	{
		WidgetSafeDeleteInfo* aWidgetSafeDeleteInfo = &(*anItr);
		if (mUpdateAppDepth <= aWidgetSafeDeleteInfo->mUpdateAppDepth)
		{
			delete aWidgetSafeDeleteInfo->mWidget;
			anItr = mSafeDeleteList.erase(anItr);
		}
		else
			++anItr;
	}
}

void SexyAppBase::SafeDeleteWidget(Widget* theWidget)
{
	WidgetSafeDeleteInfo aWidgetSafeDeleteInfo;
	aWidgetSafeDeleteInfo.mUpdateAppDepth = mUpdateAppDepth;
	aWidgetSafeDeleteInfo.mWidget = theWidget;
	mSafeDeleteList.push_back(aWidgetSafeDeleteInfo);
}

void SexyAppBase::Init()
{
	SetMainThreadToCurrent();
	OutputDebugStrF("SexyAppBase Init");
	mInteractiveAudioDriver->InitInteractiveAudioDriver();
	mAppDriver->Init();
	mProfileDriver->Init();
	mSaveGameDriver->Init();
	mLeaderboardDriver->Init();
	mAchievementDriver->Init();
	mDiagDriver->Init();
	m_allScreenOffset = mAppDriver->CalcOppoFullScreenOffset();
	OutputDebugStrF("fullScreen SexyAppBase::CalcFullScreenOffset offset = %d", m_allScreenOffset);
}

void SexyAppBase::UpdateFrames()
{
	mUpdateCount++;

	if (!mMinimized)
	{
		PerfTimer aTimer;
		if (mShowFPS && (mShowFPSMode == FPS_ShowFPS || mShowFPSMode == FPS_ShowFPSWithHistory))
			aTimer.Start();

		if (mWidgetManager->UpdateFrame())
			++mFPSDirtyCount;

		if (mShowFPS && (mShowFPSMode == FPS_ShowFPS || mShowFPSMode == FPS_ShowFPSWithHistory))
		{
			mVFPSUpdateCount++;
			mVFPSUpdateTimes += aTimer.GetDuration();
		}
	}

	if (mResStreamsManager != NULL)
		mResStreamsManager->Update();
	UpdateAudio();
	if (mSaveGameDriver != NULL)
		mSaveGameDriver->Update();
	if (mProfileManager != NULL)
		mProfileManager->Update();
	if (mHttpDriver != NULL)
		mHttpDriver->Update();
	if (mLeaderboardManager != NULL)
		mLeaderboardManager->Update();
	if (mAchievementDriver != NULL)
		mAchievementDriver->Update();
	if (mDiagDriver != NULL)
		mDiagDriver->Update();

	AsyncTaskManager* aTaskManager = AsyncTaskManager::DefaultAsyncTaskManager();
	if (aTaskManager != NULL)
		aTaskManager->Update();
	NetworkServiceManager::DefaultNetworkServiceManager()->Update();

	CleanSharedImages();
}

RtSerialBuffer* SexyAppBase::CreateReadBufferFromFile(const std::string& theFilePath, bool allowRSBFixedBuffer)
{
	if (mResStreamsManager != NULL)
	{
		std::string aFilePath = theFilePath;
		uint32 aGroupId = mResStreamsManager->GetGroupForFile(aFilePath);
		if (aGroupId != 0xFFFFFFFF)
		{
			uint8* aData = NULL;
			uint32 aSize;
			if (mResStreamsManager->GetResidentFileBuffer(aGroupId, aFilePath, &aData, &aSize))
			{
				RtSerialBuffer* aBuffer;
				if (allowRSBFixedBuffer)
					aBuffer = new RtSerialBuffer(aData, aSize);
				else
				{
					aBuffer = new RtSerialBuffer();
					aBuffer->Write(aData, aSize);
					aBuffer->SeekStart(0);
				}
				return aBuffer;
			}
		}
	}

	PFILE* aFP = p_fopen(theFilePath.c_str(), "rb");
	if (aFP == NULL)
		return NULL;

	p_fseek(aFP, 0, SEEK_END);
	int aFileSize = p_ftell(aFP);
	p_fseek(aFP, 0, SEEK_SET);

	RtSerialBuffer* aBuffer = new RtSerialBuffer();
	aBuffer->MaybeWrite(NULL, aFileSize);
	p_fread(aBuffer->GetDataPtr(), 1, aFileSize, aFP);
	p_fclose(aFP);
	return aBuffer;
}

void SexyAppBase::GotFocus()
{
	mGraphicsDriver->GetRenderDevice3D()->GotFocus();
	if (mResStreamsManager != NULL && mResStreamsManager->IsInitialized("dynamic.rsb"))
		mResStreamsManager->GotFocus();
}

void SexyAppBase::LostFocus()
{
	if (mResStreamsManager != NULL && mResStreamsManager->IsInitialized("dynamic.rsb"))
		mResStreamsManager->LostFocus();
	if (mGraphicsDriver != NULL)
	{
		RenderDevice3D* aRenderDevice = mGraphicsDriver->GetRenderDevice3D();
		if (aRenderDevice != NULL)
			aRenderDevice->LostFocus();
	}
}

void SexyAppBase::SetResumeCachedFolder(const std::string& i_folder)
{
	mResumeCachedFolder = i_folder;
	MkDir(ResumableRequestInfo::GetResumeCachedFolder());
}

void SexyAppBase::AddMemoryImage(MemoryImage* theMemoryImage)
{
	if (mGraphicsDriver == NULL)
		return;

	AutoCrit aCrit(mImageSetCritSect);
	mMemoryImageSet.insert(theMemoryImage);
}

void SexyAppBase::ModalClose()
{
}

void SexyAppBase::RehupFocus()
{
}

void SexyAppBase::StartSounds()
{
}

void SexyAppBase::UnmuteMusic()
{
}

void SexyAppBase::PreTerminate()
{
}

bool SexyAppBase::ShouldReInit()
{
	return false;
}

void SexyAppBase::ShutdownHook()
{
}

bool SexyAppBase::ChangeDirHook(const char * theIntendedPath)
{
	return false;
}

void SexyAppBase::Done3dTesting()
{
}

void SexyAppBase::UpdateFramesF(float i_dt)
{
}

void SexyAppBase::PreDisplayHook()
{
}

void SexyAppBase::HandleWwiseError()
{
}

void SexyAppBase::LowMemoryWarning()
{
}

void SexyAppBase::CleanSharedImages()
{
}

void SexyAppBase::CloseRequestAsync()
{
}

bool SexyAppBase::DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown)
{
	return false;
}

void SexyAppBase::LoadingThreadProc()
{
}

void SexyAppBase::WechatShareFailed()
{
}

void SexyAppBase::InitPropertiesHook()
{
}

void SexyAppBase::OnResourcesUpdated(ResourceUpdateType theType, void* theInfo)
{
}

void SexyAppBase::UpdateFramesPaused()
{
}

void SexyAppBase::WechatShareSuccess()
{
}

void SexyAppBase::OnFullVersionChange()
{
}

void SexyAppBase::OnLiveLinkConnected()
{
}

void SexyAppBase::AccelerometerChanged(double theTimestamp, double theX, double theY, double theZ)
{
}

void SexyAppBase::AppEnteredBackground()
{
}

void SexyAppBase::AppEnteredForeground()
{
}

bool SexyAppBase::HandleOpenURLRequest(const std::string& theURL)
{
	return false;
}

void SexyAppBase::UIOrientationChanged(UI_ORIENTATION theOrientation)
{
}

void SexyAppBase::AppBecomingForeground()
{
}

void SexyAppBase::LoadingThreadCompleted()
{
}

void SexyAppBase::OnLiveLinkDisconnected()
{
}

void SexyAppBase::PreDDInterfaceInitHook()
{
}

void SexyAppBase::PostDDInterfaceInitHook()
{
}

void SexyAppBase::HandleGameAlreadyRunning()
{
}

bool SexyAppBase::FrameNeedsSwapScreenImage()
{
	return true;
}

bool SexyAppBase::isReducedResolutionIPhone()
{
	return false;
}

UI_ORIENTATION SexyAppBase::FullScreenUIOrientationLeft()
{
	return UI_ORIENTATION_LANDSCAPE_LEFT;
}

UI_ORIENTATION SexyAppBase::FullScreenUIOrientationRight()
{
	return UI_ORIENTATION_LANDSCAPE_RIGHT;
}

bool SexyAppBase::KeyDown(int theKey)
{
	return false;
}

void SexyAppBase::InitHook()
{
}

void SexyAppBase::ModalOpen()
{
}

void SexyAppBase::MuteMusic()
{
}
