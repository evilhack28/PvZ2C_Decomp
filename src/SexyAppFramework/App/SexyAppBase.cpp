//
//  SexyAppBase.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-27.
//

#include "SexyAppBase.h"
#include "AsyncTaskManager.h"
#include "AutoCrit.h"
#include "DeviceImage.h"
#include "Dialog.h"
#include "Graphics.h"
#include "IAchievementDriver.h"
#include "IAntiHackDriver.h"
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
#include "MemoryImage.h"
#include "NetworkServiceManager.h"
#include "PakLib/PakInterface.h"
#include "PerfTimer.h"
#include "PrimeText/PrimeText.h"
#include "PropertiesParser.h"
#include "Reflection.h"
#include "ProfileManager.h"
#include "RenderDevice.h"
#include "SexyCache.h"
#include "ResStreamsManager.h"
#include "ResumeRequestInfo.h"
#include "RtSerial.h"
#include "SysFont.h"
#include "Widget.h"
#include "WidgetManager.h"

/////////////// Lifecycle ///////////////

SexyAppBase::SexyAppBase()
{
	mResumeCachedFolder = "";
	mResStreamsManager = NULL;
	SetMainThreadToCurrent();
	m_nativeScreenHeight = 0;
	mAllowSwapScreenImage = true;
	mMaxUpdateBacklog = 200;
	mPauseWhenMoving = true;
	m_nativeScreenWidth = 0;
	mGraphicsDriver = NULL;
	mProfileManager = NULL;
	mLeaderboardManager = NULL;

	InitFileDriver();
	mFileDriver = gFileDriver;
	mAppDriver = IAppDriver::CreateAppDriver(this);
	mInteractiveAudioDriver = IInteractiveAudioDriver::CreateInteractiveAudioDriver(this);
	mResStreamsDriver = IResStreamsDriver::CreateResStreamsDriver();
	mProfileDriver = IProfileDriver::CreateProfileDriver();
	mSaveGameDriver = ISaveGameDriver::CreateSaveGameDriver();
	mHttpDriver = IHttpDriver::CreateHttpDriver(this);
	mLeaderboardDriver = ILeaderboardDriver::CreateLeaderboardDriver();
	mAchievementDriver = IAchievementDriver::CreateAchievementDriver();
	mDiagDriver = IDiagDriver::CreateDiagDriver();
	mAntiHackDriver = IAntiHackDriver::CreateAntiHackDriver();
	mCalcFPS = false;

	gSexyAppBase = this;

	mWidgetManager = new WidgetManager(this);
	mResourceManager = new ResourceManager(this);

	mAppDriver->InitAppDriver();
	if (!mFileDriver->InitFileDriver(this))
	{
		Shutdown();
		return;
	}

	mResStreamsManager = new ResStreamsManager(this);
	PrimeText::InstanceCreate(this);
	mbNewSetup = false;
	mEnableMapEdit = false;
	m_allScreenOffset = 0;
	mLostFocusOnly = false;
}

SexyAppBase::~SexyAppBase()
{
	CleanupSysFont();

	DialogMap::iterator aDialogItr = mDialogMap.begin();
	while (aDialogItr != mDialogMap.end())
	{
		Dialog* aDialog = aDialogItr->second;
		if (aDialog->mParent)
			aDialog->mParent->RemoveWidget(aDialog);

		delete aDialogItr->second;
		++aDialogItr;
	}

	mDialogMap.clear();
	mDialogList.clear();

	delete mWidgetManager;
	delete mResourceManager;
	delete mSharedRTPool;
	mSharedRTPool = NULL;

	mAppDriver->Shutdown();

	delete mProfileManager;
	mProfileManager = NULL;
	delete mLeaderboardManager;
	mLeaderboardManager = NULL;

	delete mInteractiveAudioDriver;
	mInteractiveAudioDriver = NULL;
	delete mSaveGameDriver;
	mSaveGameDriver = NULL;
	delete mProfileDriver;
	mProfileDriver = NULL;
	delete mHttpDriver;
	mHttpDriver = NULL;
	delete mLeaderboardDriver;
	mLeaderboardDriver = NULL;
	delete mAchievementDriver;
	mAchievementDriver = NULL;
	delete mDiagDriver;
	mDiagDriver = NULL;
	delete mAppDriver;
	mAppDriver = NULL;
	delete mResStreamsManager;
	mResStreamsManager = NULL;
	delete mResStreamsDriver;
	mResStreamsDriver = NULL;
	delete gFileDriver;
	mFileDriver = NULL;
	gFileDriver = NULL;
	gSexyAppBase = NULL;
}

/////////////// Accessors ///////////////

void SexyAppBase::SetBoolean(const std::string& theId, bool theValue)
{
	std::pair<StringBoolMap::iterator, bool> aResult = mBoolProperties.insert(std::pair<const std::string, bool>(theId, theValue));
	if (!aResult.second)
		aResult.first->second = theValue;
}

void SexyAppBase::SetResumeCachedFolder(const std::string& i_folder)
{
	mResumeCachedFolder = i_folder;
	MkDir(ResumableRequestInfo::GetResumeCachedFolder());
}

Reflection::CRefSymbolDb* SexyAppBase::GetManualReflection()
{
	return Reflection::CRefSymbolDb::GetManualReflection();
}

bool SexyAppBase::GetCheatsEnabled()
{
	return mDebugKeysEnabled;
}

void SexyAppBase::SetCheatsEnabled(bool i_enabled)
{
	mDebugKeysEnabled = i_enabled;
}

bool SexyAppBase::IsScreenSaver()
{
	return mIsScreenSaver;
}

void SexyAppBase::SetNativeScreenSize(int i_width, int i_height)
{
	m_nativeScreenHeight = i_height;
	m_nativeScreenWidth = i_width;
}

bool SexyAppBase::IsMuted()
{
	return mMuteCount > 0;
}

double SexyAppBase::GetMusicVolume()
{
	return mMusicVolume;
}

double SexyAppBase::GetSfxVolume()
{
	return mSfxVolume;
}

int SexyAppBase::GetDialogCount()
{
	return mDialogMap.size();
}

void SexyAppBase::SetMusicVolume(double theVolume)
{
	mMusicVolume = theVolume;
	mInteractiveSoundManager->SetMusicVolume(theVolume);
}

void SexyAppBase::SetMasterVolume(double theVolume)
{
	if (mInteractiveSoundManager)
		mInteractiveSoundManager->SetMasterVolume(theVolume);
}

double SexyAppBase::GetLoadingThreadProgress()
{
	return mAppDriver->GetLoadingThreadProgress();
}

void SexyAppBase::SetCursor(int theCursorNum)
{
	mAppDriver->SetCursor(theCursorNum);
}

int SexyAppBase::GetCursor()
{
	return mAppDriver->GetCursor();
}

void SexyAppBase::SetCursorImage(int theCursorNum, Image* theImage)
{
	mAppDriver->SetCursorImage(theCursorNum, theImage);
}

bool SexyAppBase::IsKeyboardShowing()
{
	return mAppDriver->IsKeyboardShowing();
}

void SexyAppBase::SetFPS(bool i_highFPS)
{
	mAppDriver->SetFPS(i_highFPS);
}

bool SexyAppBase::IsHighFPS()
{
	return mAppDriver->IsHighFPS();
}

bool SexyAppBase::IsFullScreen()
{
	return mAppDriver->isOppoFullScreen();
}

void SexyAppBase::SetMainThreadToCurrent()
{
	mMainThreadId = GetCurrentRunningThread();
}

std::string SexyAppBase::GetClipboard()
{
	return mAppDriver->GetClipboard();
}

void SexyAppBase::SetSfxVolume(double theVolume)
{
	if (mInteractiveSoundManager)
		mInteractiveSoundManager->SetSfxVolume(theVolume);
	mSfxVolume = theVolume;
}

double SexyAppBase::GetMasterVolume()
{
	if (mInteractiveSoundManager)
		return mInteractiveSoundManager->GetMasterVolume();
	return 0;
}

std::string SexyAppBase::GetDeviceName()
{
	return mAppDriver->GetDeviceName();
}

std::string SexyAppBase::GetGameSEHInfo()
{
	return mAppDriver->GetGameSEHInfo();
}

bool SexyAppBase::IsUIOrientationAllowed(UI_ORIENTATION theOrientation)
{
	return mAppDriver->IsUIOrientationAllowed(theOrientation);
}

UI_ORIENTATION SexyAppBase::GetUIOrientation()
{
	return mAppDriver->GetUIOrientation();
}

Point SexyAppBase::GetNativeScreenSize()
{
	return Point(m_nativeScreenWidth, m_nativeScreenHeight);
}

SharedRenderTarget::Pool* SexyAppBase::GetSharedRenderTargetPool()
{
	if (!mSharedRTPool)
		mSharedRTPool = new SharedRenderTarget::Pool();
	return mSharedRTPool;
}

bool SexyAppBase::IsMainThread() const
{
	return mMainThreadId == GetCurrentRunningThread();
}

void SexyAppBase::SetInteger(const std::string& theId, int theValue)
{
	std::pair<StringIntMap::iterator, bool> aResult = mIntProperties.insert(std::pair<const std::string, int>(theId, theValue));
	if (!aResult.second)
		aResult.first->second = theValue;
}

void SexyAppBase::SetDouble(const std::string& theId, double theValue)
{
	std::pair<StringDoubleMap::iterator, bool> aResult = mDoubleProperties.insert(std::pair<const std::string, double>(theId, theValue));
	if (!aResult.second)
		aResult.first->second = theValue;
}

/////////////// Logic ///////////////

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

std::string SexyAppBase::NotifyCrashHook()
{
	return "";
}

void SexyAppBase::TouchBegan(const Touch& theTouch)
{
	mWidgetManager->TouchBegan(theTouch);
}

void SexyAppBase::URLOpenFailed(const std::string& theURL)
{
	mIsOpeningURL = false;
}

void SexyAppBase::DrawScreen()
{
	mWidgetManager->DrawScreen();
}

int SexyAppBase::CalcFullScreenOffset()
{
	return m_allScreenOffset;
}

bool SexyAppBase::AppCanRestore()
{
	return !mIsDisabled;
}

void SexyAppBase::UpdateAudio()
{
	if (mInteractiveSoundManager)
		mInteractiveSoundManager->Update();
}

void SexyAppBase::TouchEnded(const Touch& theTouch)
{
	mWidgetManager->TouchEnded(theTouch);
}

void SexyAppBase::TouchMoved(const Touch& theTouch)
{
	mWidgetManager->TouchMoved(theTouch);
}

void SexyAppBase::ActivateAudioSession()
{
	if (mInteractiveSoundManager)
		mInteractiveSoundManager->PauseAll(false);
}

void SexyAppBase::DeactivateAudioSession()
{
	if (mInteractiveSoundManager)
		mInteractiveSoundManager->PauseAll(true);
}

void SexyAppBase::BeginPopup()
{
	mAppDriver->BeginPopup();
}

void SexyAppBase::EndPopup()
{
	mAppDriver->EndPopup();
}

int SexyAppBase::MsgBox(const std::string& theText, const std::string& theTitle, int theFlags)
{
	return mAppDriver->MsgBox(theText, theTitle, theFlags);
}

int SexyAppBase::MsgBox(const std::wstring& theText, const std::wstring& theTitle, int theFlags)
{
	return mAppDriver->MsgBox(theText, theTitle, theFlags);
}

void SexyAppBase::Popup(const std::string& theString)
{
	mAppDriver->Popup(theString);
}

void SexyAppBase::Popup(const std::wstring& theString)
{
	mAppDriver->Popup(theString);
}

bool SexyAppBase::OpenURL(const std::string& theURL, bool shutdownOnOpen)
{
	return mAppDriver->OpenURL(theURL, shutdownOnOpen);
}

void SexyAppBase::Start()
{
	mAppDriver->Start();
}

void SexyAppBase::Shutdown()
{
	mAppDriver->Shutdown();
}

void SexyAppBase::DoExit(int theCode)
{
	mAppDriver->DoExit(theCode);
}

bool SexyAppBase::UpdateAppStep(bool* updated)
{
	return mAppDriver->UpdateAppStep(updated);
}

void SexyAppBase::ClearUpdateBacklog(bool relaxForASecond)
{
	mAppDriver->ClearUpdateBacklog(relaxForASecond);
}

void SexyAppBase::Remove3DData(MemoryImage* theMemoryImage)
{
	mAppDriver->Remove3DData(theMemoryImage);
}

void SexyAppBase::DoParseCmdLine()
{
	mAppDriver->DoParseCmdLine();
}

void SexyAppBase::ParseCmdLine(const std::string& theCmdLine)
{
	mAppDriver->ParseCmdLine(theCmdLine);
}

void SexyAppBase::HandleCmdLineParam(const std::string& theParamName, const std::string& theParamValue)
{
	mAppDriver->HandleCmdLineParam(theParamName, theParamValue);
}

void SexyAppBase::StartLoadingThread()
{
	mAppDriver->StartLoadingThread();
}

void SexyAppBase::CopyToClipboard(const std::string& theString)
{
	mAppDriver->CopyToClipboard(theString);
}

void SexyAppBase::EnableCustomCursors(bool enabled)
{
	mAppDriver->EnableCustomCursors(enabled);
}

void SexyAppBase::SwitchScreenMode(bool wantWindowed, bool is3d, bool force)
{
	mAppDriver->SwitchScreenMode(wantWindowed, is3d, force);
}

bool SexyAppBase::DebugKeyDown(int theKey)
{
	return mAppDriver->DebugKeyDown(theKey);
}

bool SexyAppBase::Is3DAccelerated()
{
	return mAppDriver->Is3DAccelerated();
}

bool SexyAppBase::Is3DAccelerationSupported()
{
	return mAppDriver->Is3DAccelerationSupported();
}

bool SexyAppBase::Is3DAccelerationRecommended()
{
	return mAppDriver->Is3DAccelerationRecommended();
}

void SexyAppBase::Set3DAcclerated(bool is3D, bool reinit)
{
	mAppDriver->Set3DAcclerated(is3D, reinit);
}

void SexyAppBase::ShowKeyboard()
{
	mAppDriver->ShowKeyboard();
}

void SexyAppBase::ShowPhoneNumKeyboard()
{
	mAppDriver->ShowKeyboard();
}

void SexyAppBase::ShowEmailKeyboard()
{
	mAppDriver->ShowKeyboard();
}

void SexyAppBase::HideKeyboard()
{
	mAppDriver->HideKeyboard();
}

bool SexyAppBase::CheckSignature(const Buffer& theBuffer, const std::string& theFileName)
{
	return mAppDriver->CheckSignature(theBuffer, theFileName);
}

bool SexyAppBase::ReloadAllResources()
{
	return mAppDriver->ReloadAllResources();
}

bool SexyAppBase::RegistryGetSubKeys(const std::string& theKeyName, StringVector* theSubKeys)
{
	return mAppDriver->ConfigGetSubKeys(theKeyName, theSubKeys);
}

bool SexyAppBase::RegistryReadString(const std::string& theValueName, std::string* theString)
{
	return mAppDriver->ConfigReadString(theValueName, theString);
}

bool SexyAppBase::RegistryReadString(const std::string& theValueName, std::wstring* theString)
{
	return mAppDriver->ConfigReadString(theValueName, theString);
}

bool SexyAppBase::RegistryReadInteger(const std::string& theValueName, int* theValue)
{
	return mAppDriver->ConfigReadInteger(theValueName, theValue);
}

bool SexyAppBase::RegistryReadBoolean(const std::string& theValueName, bool* theValue)
{
	return mAppDriver->ConfigReadBoolean(theValueName, theValue);
}

bool SexyAppBase::RegistryReadData(const std::string& theValueName, uchar* theValue, ulong* theLength)
{
	return mAppDriver->ConfigReadData(theValueName, theValue, theLength);
}

bool SexyAppBase::RegistryWriteString(const std::string& theValueName, const std::string& theString)
{
	return mAppDriver->ConfigWriteString(theValueName, theString);
}

bool SexyAppBase::RegistryWriteString(const std::string& theValueName, const std::wstring& theString)
{
	return mAppDriver->ConfigWriteString(theValueName, theString);
}

bool SexyAppBase::RegistryWriteInteger(const std::string& theValueName, int theValue)
{
	return mAppDriver->ConfigWriteInteger(theValueName, theValue);
}

bool SexyAppBase::RegistryWriteBoolean(const std::string& theValueName, bool theValue)
{
	return mAppDriver->ConfigWriteBoolean(theValueName, theValue);
}

bool SexyAppBase::RegistryWriteData(const std::string& theValueName, const uchar* theValue, ulong theLength)
{
	return mAppDriver->ConfigWriteData(theValueName, theValue, theLength);
}

bool SexyAppBase::RegistryEraseKey(const SexyString& theKeyName)
{
	return mAppDriver->ConfigEraseKey(theKeyName);
}

void SexyAppBase::RegistryEraseValue(const SexyString& theValueName)
{
	mAppDriver->ConfigEraseValue(theValueName);
}

bool SexyAppBase::WriteBytesToFile(const std::string& theFilePath, const void* theData, unsigned long theDataLen)
{
	return mAppDriver->WriteBytesToFile(theFilePath, theData, theDataLen);
}

bool SexyAppBase::WriteBytesToFileAt(const std::string& theFilePath, const void* theData, unsigned long theDataLen, unsigned long theSeekPos)
{
	return mAppDriver->WriteBytesToFileAt(theFilePath, theData, theDataLen, theSeekPos);
}

bool SexyAppBase::WriteBytesToFileEnd(const std::string& theFilePath, const void* theData, unsigned long theDataLen)
{
	return mAppDriver->WriteBytesToFileEnd(theFilePath, theData, theDataLen);
}

bool SexyAppBase::CreateFileOfSize(const std::string& theFilePath, unsigned long theDataLen)
{
	return mAppDriver->CreateFileOfSize(theFilePath, theDataLen);
}

bool SexyAppBase::CopyFile(const std::string& theFromFilePath, const std::string& theToFilePath)
{
	return mAppDriver->CopyFile(theFromFilePath, theToFilePath);
}

bool SexyAppBase::RenameFile(const std::string& theFromFilePath, const std::string& theToFilePath)
{
	return mAppDriver->RenameFile(theFromFilePath, theToFilePath);
}

bool SexyAppBase::EraseFile(const std::string& theFilePath)
{
	return mFileDriver->DeleteFile(theFilePath);
}

void SexyAppBase::OnBackButtonPressed()
{
	mWidgetManager->OnBackButtonPressed();
}

void SexyAppBase::SwitchScreenMode()
{
	SwitchScreenMode(mIsWindowed, Is3DAccelerated(), true);
}

void SexyAppBase::SwitchScreenMode(bool wantWindowed)
{
	SwitchScreenMode(wantWindowed, Is3DAccelerated(), false);
}

bool SexyAppBase::FileExists(const std::string& theFilePath)
{
	return mFileDriver->FileExists(theFilePath);
}

bool SexyAppBase::KillDialog(int theDialogId)
{
	return KillDialog(theDialogId, true, true);
}

bool SexyAppBase::KillDialog(Dialog* theDialog)
{
	return KillDialog(theDialog->mId);
}

void SexyAppBase::Vibrate(long long milliseconds)
{
	mAppDriver->Vibrate(milliseconds);
}

void SexyAppBase::VibrateWithPattern(long long pattern[], int isRepeat)
{
	mAppDriver->VibrateWithPattern(pattern, isRepeat);
}

void SexyAppBase::CancelVibrate()
{
	mAppDriver->CancelVibrate();
}

void SexyAppBase::InitFileDriver()
{
	if (!gFileDriver)
		gFileDriver = IFileDriver::CreateFileDriver();
}

void SexyAppBase::TouchesCanceled()
{
	mAppDriver->InputCancelAll();
	mWidgetManager->TouchesCanceled();
}

void SexyAppBase::URLOpenSucceeded(const std::string& theURL)
{
	mIsOpeningURL = false;
	if (mShutdownOnURLOpen)
		Shutdown();
}

bool SexyAppBase::WriteBufferToFile(const std::string& theFilePath, const Buffer* theBuffer)
{
	return WriteBytesToFile(theFilePath, theBuffer->GetDataPtr(), theBuffer->GetDataLen());
}

void SexyAppBase::PrecacheAlpha(MemoryImage* theImage)
{
	theImage->GetRLAlphaData();
}

void SexyAppBase::PrecacheAdditive(MemoryImage* theImage)
{
	theImage->GetRLAdditiveData(mGraphicsDriver->GetNativeDisplayInfo());
}

void SexyAppBase::PrecacheNative(MemoryImage* theImage)
{
	theImage->GetNativeAlphaData(mGraphicsDriver->GetNativeDisplayInfo());
}

bool SexyAppBase::GetBoolean(const std::string& theId)
{
	StringBoolMap::iterator anItr = mBoolProperties.find(theId);
	if (anItr != mBoolProperties.end())
		return anItr->second;

	return false;
}

int SexyAppBase::GetInteger(const std::string& theId)
{
	StringIntMap::iterator anItr = mIntProperties.find(theId);
	if (anItr != mIntProperties.end())
		return anItr->second;

	return 0;
}

int SexyAppBase::GetInteger(const std::string& theId, int theDefault)
{
	StringIntMap::iterator anItr = mIntProperties.find(theId);
	if (anItr != mIntProperties.end())
		return anItr->second;

	return theDefault;
}

double SexyAppBase::GetDouble(const std::string& theId)
{
	StringDoubleMap::iterator anItr = mDoubleProperties.find(theId);
	if (anItr != mDoubleProperties.end())
		return anItr->second;

	return 0.0;
}

double SexyAppBase::GetDouble(const std::string& theId, double theDefault)
{
	StringDoubleMap::iterator anItr = mDoubleProperties.find(theId);
	if (anItr != mDoubleProperties.end())
		return anItr->second;

	return theDefault;
}

SexyString SexyAppBase::GetString(const std::string& theId)
{
	StringWStringMap::iterator anItr = mStringProperties.find(theId);
	if (anItr != mStringProperties.end())
		return WStringToSexyString(anItr->second);

	return L"";
}

SexyString SexyAppBase::GetString(const std::string& theId, const SexyString& theDefault)
{
	StringWStringMap::iterator anItr = mStringProperties.find(theId);
	if (anItr != mStringProperties.end())
		return WStringToSexyString(anItr->second);

	return theDefault;
}

StringVector SexyAppBase::GetStringVector(const std::string& theId)
{
	StringStringVectorMap::iterator anItr = mStringVectorProperties.find(theId);
	if (anItr != mStringVectorProperties.end())
		return anItr->second;

	return StringVector();
}

void SexyAppBase::OnGestureLongPress(Point i_startingLocation)
{
	mWidgetManager->OnGestureLongPress(i_startingLocation);
}

void SexyAppBase::OnGestureFlick(GestureFlickDirection i_direction, Point i_startingLocation)
{
	mWidgetManager->OnGestureFlick(i_direction, i_startingLocation);
}

void SexyAppBase::OnGesturePinch(Point i_centerPoint, int i_distanceBetweenFingersSquared, float i_scaleDelta)
{
	mWidgetManager->OnGesturePinch(i_centerPoint, i_distanceBetweenFingersSquared, i_scaleDelta);
}

void SexyAppBase::DialogButtonPress(int theDialogId, int theButtonId)
{
	if (theButtonId == Dialog::ID_YES)
		ButtonPress(2000 + theDialogId);
	else if (theButtonId == Dialog::ID_NO)
		ButtonPress(3000 + theDialogId);
}

void SexyAppBase::DialogButtonDepress(int theDialogId, int theButtonId)
{
	if (theButtonId == Dialog::ID_YES)
		ButtonDepress(2000 + theDialogId);
	else if (theButtonId == Dialog::ID_NO)
		ButtonDepress(3000 + theDialogId);
}

void SexyAppBase::Mute(bool autoMute)
{
	mMuteCount++;

	if (autoMute)
		mAutoMuteCount++;

	SetMusicVolume(mMusicVolume);
	SetSfxVolume(mSfxVolume);
}

void SexyAppBase::Unmute(bool autoMute)
{
	if (mMuteCount > 0)
	{
		mMuteCount--;

		if (autoMute)
			mAutoMuteCount--;
	}

	SetMusicVolume(mMusicVolume);
	SetSfxVolume(mSfxVolume);
}

Dialog* SexyAppBase::NewDialog(int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode)
{
	return new Dialog(theDialogId, isModal, theDialogHeader, theDialogLines, theDialogFooter, theButtonMode);
}

Dialog* SexyAppBase::DoDialog(int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode)
{
	KillDialog(theDialogId);

	Dialog* aDialog = NewDialog(theDialogId, isModal, theDialogHeader, theDialogLines, theDialogFooter, theButtonMode);
	AddDialog(theDialogId, aDialog);

	return aDialog;
}

Dialog* SexyAppBase::GetDialog(int theDialogId)
{
	DialogMap::iterator anItr = mDialogMap.find(theDialogId);
	if (anItr != mDialogMap.end())
		return anItr->second;

	return NULL;
}

bool SexyAppBase::UpdateApp()
{
	bool updated;
	while (UpdateAppStep(&updated))
	{
		if (updated)
			return true;
	}

	return false;
}

void SexyAppBase::AddDialog(int theDialogId, Dialog* theDialog)
{
	AddDialog(theDialogId, theDialog, mWidgetManager->mDefaultBelowModalFlagsMod);
}

void SexyAppBase::AddDialog(Dialog* theDialog)
{
	AddDialog(theDialog->mId, theDialog);
}

bool SexyAppBase::LoadProperties()
{
	return LoadProperties("properties/default.xml", true, false, true);
}

void SexyAppBase::RemoveMemoryImage(MemoryImage* theMemoryImage)
{
	if (mGraphicsDriver != NULL)
	{
		AutoCrit aCrit(mImageSetCritSect);
		MemoryImageSet::iterator anItr = mMemoryImageSet.find(theMemoryImage);
		if (anItr != mMemoryImageSet.end())
			mMemoryImageSet.erase(anItr);

		Remove3DData(theMemoryImage);
	}
}

void SexyAppBase::ReInitImages()
{
	AutoCrit aCrit(mImageSetCritSect);
	MemoryImageSet::iterator anItr = mMemoryImageSet.begin();
	while (anItr != mMemoryImageSet.end())
	{
		MemoryImage* aMemoryImage = *anItr;
		aMemoryImage->ReInit();
		++anItr;
	}
}

void SexyAppBase::DeleteExtraImageData()
{
	AutoCrit aCrit(mImageSetCritSect);
	MemoryImageSet::iterator anItr = mMemoryImageSet.begin();
	DeviceImage* aScreenImage = mGraphicsDriver->GetScreenImage();
	while (anItr != mMemoryImageSet.end())
	{
		MemoryImage* aMemoryImage = *anItr;
		if (aMemoryImage != aScreenImage)
			aMemoryImage->DeleteExtraBuffers();
		++anItr;
	}
}

void SexyAppBase::DeleteNativeImageData()
{
	AutoCrit aCrit(mImageSetCritSect);
	MemoryImageSet::iterator anItr = mMemoryImageSet.begin();
	while (anItr != mMemoryImageSet.end())
	{
		MemoryImage* aMemoryImage = *anItr;
		aMemoryImage->DeleteNativeData();
		++anItr;
	}
}

void SexyAppBase::FlipImage(Image* theImage)
{
	MemoryImage* aMemoryImage = theImage ? theImage->AsMemoryImage() : NULL;
	uint32* aBits = aMemoryImage->GetBits();
	int aWidth = aMemoryImage->mWidth;
	int aHeight = aMemoryImage->mHeight;

	for (int x = 0; x < aWidth; x++)
	{
		uint32* aTop = aBits + x;
		uint32* aBottom = aBits + (aHeight - 1) * aWidth + x;
		for (int y = 0; y < (aHeight >> 1); y++)
		{
			uint32 aTemp = *aTop;
			*aTop = *aBottom;
			*aBottom = aTemp;
			aTop += aWidth;
			aBottom -= aWidth;
		}
	}

	aMemoryImage->BitsChanged();
}

DeviceImage* SexyAppBase::CopyImage(Image* theImage)
{
	return CopyImage(theImage, Rect(0, 0, theImage->GetWidth(), theImage->GetHeight()));
}

DeviceImage* SexyAppBase::CopyImage(Image* theImage, const Rect& theRect)
{
	DeviceImage* aCopiedImage = new DeviceImage(this);

	aCopiedImage->Create(theRect.mWidth, theRect.mHeight);

	Graphics g(aCopiedImage);
	g.DrawImage(theImage, -theRect.mX, -theRect.mY);

	aCopiedImage->CopyAttributes(theImage);

	return aCopiedImage;
}

void SexyAppBase::RGBToHSL(const ulong* theSource, ulong* theDest, int theSize)
{
	for (int i = 0; i < theSize; i++)
	{
		ulong src = theSource[i];
		theDest[i] = (src & 0xFF000000) | (RGBToHSL((src >> 16) & 0xFF, (src >> 8) & 0xFF, src & 0xFF) & 0xFFFFFF);
	}
}

void SexyAppBase::HSLToRGB(const ulong* theSource, ulong* theDest, int theSize)
{
	for (int i = 0; i < theSize; i++)
	{
		ulong src = theSource[i];
		theDest[i] = (src & 0xFF000000) | (HSLToRGB(src & 0xFF, (src >> 8) & 0xFF, (src >> 16) & 0xFF) & 0xFFFFFF);
	}
}

ulong SexyAppBase::RGBToHSL(int r, int g, int b)
{
	int maxval = std::max(r, std::max(g, b));
	int minval = std::min(r, std::min(g, b));
	int hue = 0;
	int saturation = 0;
	int luminosity = (minval + maxval) / 2;
	int delta = maxval - minval;

	if (delta != 0)
	{
		saturation = (delta * 256) / ((luminosity <= 128) ? (minval + maxval) : (512 - maxval - minval));

		if (r == maxval)
			hue = (g == minval ? 1280 + (((maxval - b) * 256) / delta) : 256 - (((maxval - g) * 256) / delta));
		else if (g == maxval)
			hue = (b == minval ? 256 + (((maxval - r) * 256) / delta) : 768 - (((maxval - b) * 256) / delta));
		else
			hue = (r == minval ? 768 + (((maxval - g) * 256) / delta) : 1280 - (((maxval - r) * 256) / delta));

		hue /= 6;
	}

	return 0xFF000000 | (hue) | (saturation << 8) | (luminosity << 16);
}

bool SexyAppBase::KillDialog(int theDialogId, bool removeWidget, bool deleteWidget)
{
	DialogMap::iterator anItr = mDialogMap.find(theDialogId);
	if (anItr != mDialogMap.end())
	{
		Dialog* aDialog = anItr->second;

		if (aDialog->mResult == -1)
			aDialog->mResult = 0;

		DialogList::iterator aListItr = std::find(mDialogList.begin(), mDialogList.end(), aDialog);
		if (aListItr != mDialogList.end())
			mDialogList.erase(aListItr);

		mDialogMap.erase(anItr);

		if ((removeWidget || deleteWidget) && aDialog->mParent)
			aDialog->mParent->RemoveWidget(aDialog);

		if (aDialog->IsModal())
		{
			ModalClose();
			mWidgetManager->RemoveBaseModal(aDialog);
		}

		if (deleteWidget)
			SafeDeleteWidget(aDialog);

		return true;
	}

	return false;
}

void SexyAppBase::AddDialog(int theDialogId, Dialog* theDialog, const FlagsMod& belowModalFlagsMod)
{
	KillDialog(theDialogId);

	if (theDialog->mWidth == 0)
	{
		int aWidth = mWidth / 2;
		theDialog->Resize((mWidth - aWidth) / 2, mHeight / 5, aWidth, theDialog->GetPreferredHeight(aWidth));
	}

	mDialogMap.insert(DialogMap::value_type(theDialogId, theDialog));
	mDialogList.push_back(theDialog);

	mWidgetManager->AddWidget(theDialog);

	if (theDialog->IsModal())
	{
		mWidgetManager->AddBaseModal(theDialog, belowModalFlagsMod);
		ModalOpen();
	}
}

void SexyAppBase::WriteToRegistry()
{
	RegistryWriteInteger("MusicVolume", (int)(mMusicVolume * 100));
	RegistryWriteInteger("SfxVolume", (int)(mSfxVolume * 100));
	RegistryWriteInteger("Muted", (mMuteCount - mAutoMuteCount > 0) ? 1 : 0);
	RegistryWriteInteger("ScreenMode", mIsWindowed ? 0 : 1);
	RegistryWriteInteger("PreferredX", mPreferredX);
	RegistryWriteInteger("PreferredY", mPreferredY);
	RegistryWriteInteger("PreferredWidth", mPreferredWidth);
	RegistryWriteInteger("PreferredHeight", mPreferredHeight);
	RegistryWriteInteger("CustomCursors", mCustomCursorsEnabled ? 1 : 0);
	RegistryWriteInteger("InProgress", 0);
	RegistryWriteBoolean("WaitForVSync", mWaitForVSync);

	mAppDriver->WriteToConfig();
}

void SexyAppBase::ReadFromRegistry()
{
	mReadFromRegistry = true;
	mRegKey = SexyStringToString(GetString("RegistryKey", StringToSexyString(mRegKey)));

	if (mRegKey.length() == 0)
		return;

	int anInt;
	if (RegistryReadInteger("MusicVolume", &anInt))
		mMusicVolume = anInt * 0.01;

	if (RegistryReadInteger("SfxVolume", &anInt))
		mSfxVolume = anInt * 0.01;

	if (RegistryReadInteger("Muted", &anInt))
		mMuteCount = anInt;

	if (RegistryReadInteger("ScreenMode", &anInt))
		mIsWindowed = anInt ? false : !mForceFullscreen;

	RegistryReadInteger("PreferredX", &mPreferredX);
	RegistryReadInteger("PreferredY", &mPreferredY);
	RegistryReadInteger("PreferredWidth", &mPreferredWidth);
	RegistryReadInteger("PreferredHeight", &mPreferredHeight);

	if (RegistryReadInteger("CustomCursors", &anInt))
		EnableCustomCursors(anInt != 0);

	RegistryReadBoolean("WaitForVSync", &mWaitForVSync);

	if (RegistryReadInteger("InProgress", &anInt))
		mLastShutdownWasGraceful = anInt == 0;

	if (!IsScreenSaver())
		RegistryWriteInteger("InProgress", 1);

	mAppDriver->ReadFromConfig();
}

bool SexyAppBase::LoadProperties(const std::string& theFileName, bool required, bool checkSig, bool needsLocaleCorrection)
{
	Buffer aBuffer;
	if (!ReadBufferFromFile(theFileName, &aBuffer))
	{
		bool aReadLocalized = false;
		if (needsLocaleCorrection && mResourceManager)
		{
			aBuffer.Clear();
			aReadLocalized = ReadBufferFromFile(mResourceManager->GetLocaleFolder(true) + theFileName, &aBuffer);
		}

		if (!aReadLocalized)
		{
			if (!required)
				return true;

			Popup(GetString("UNABLE_OPEN_PROPERTIES", L"Unable to open properties file ") + StringToSexyString(theFileName));
			return false;
		}
	}

	if (checkSig)
	{
		if (!CheckSignature(aBuffer, theFileName))
		{
			Popup(GetString("PROPERTIES_SIG_FAILED", L"Signature check failed on ") + StringToSexyString(theFileName + "'"));
			return false;
		}
	}

	PropertiesParser aParser(this);
	if (!aParser.ParsePropertiesBuffer(aBuffer))
	{
		Popup(aParser.GetErrorText());
		return false;
	}

	return true;
}

bool SexyAppBase::ReadBufferFromFile(const std::string& theFileName, Buffer* theBuffer, bool dontWriteToDemo)
{
	mErrorLog.clear();

	void* aDataPtr = NULL;
	int aDataSize;
	if (!mSexyCacheBuffers || !gSexyCache.GetData(GetFullPath(theFileName), "Buffer", &aDataPtr, &aDataSize))
	{
		if (mResStreamsManager != NULL && mResStreamsManager->IsInitialized("dynamic.rsb"))
		{
			std::string aFilePath = theFileName;
			uint32 aGroupId = mResStreamsManager->GetGroupForFile(aFilePath);
			if (aGroupId == 0xFFFFFFFF)
				mErrorLog += " | UNKNOWN_GROUP ";
			else
			{
				uint8* aData = NULL;
				uint32 aSize;
				if (mResStreamsManager->GetResidentFileBuffer(aGroupId, aFilePath, &aData, &aSize))
				{
					theBuffer->Clear();
					theBuffer->SetData(aData, aSize);
					return true;
				}

				mErrorLog += " | GetResidentFileBuffer() return false";
			}
		}

		PFILE* aFP = p_fopen(theFileName.c_str(), "rb");
		if (aFP == NULL)
		{
			if (mWriteToSexyCache && mSexyCacheBuffers)
			{
				uchar* aPtr = (uchar*)gSexyCache.AllocSetData(GetFullPath(theFileName), "Buffer", 1);
				if (aPtr != NULL)
				{
					*aPtr = 0;
					gSexyCache.SetFileDeps(GetFullPath(theFileName), "Buffer", GetFullPath(theFileName));
					gSexyCache.SetData(aPtr);
				}
			}

			mErrorLog += "aFP == NULL";
			return false;
		}

		p_fseek(aFP, 0, SEEK_END);
		int aSize = p_ftell(aFP);
		p_fseek(aFP, 0, SEEK_SET);
		uchar* aData = new uchar[aSize];
		p_fread(aData, 1, aSize, aFP);
		p_fclose(aFP);
		theBuffer->Clear();
		theBuffer->SetData(aData, aSize);
		if (mWriteToSexyCache && mSexyCacheBuffers)
		{
			uchar* aPtr = (uchar*)gSexyCache.AllocSetData(GetFullPath(theFileName), "Buffer", aSize + 1);
			if (aPtr != NULL)
			{
				*aPtr = 1;
				memcpy(aPtr + 1, aData, aSize);
				gSexyCache.SetFileDeps(GetFullPath(theFileName), "Buffer", GetFullPath(theFileName));
				gSexyCache.SetData(aPtr);
			}
		}

		delete[] aData;
		return true;
	}

	if (!*(uchar*)aDataPtr)
		return false;

	theBuffer->Clear();
	theBuffer->SetData((uchar*)aDataPtr + 1, aDataSize - 1);
	return true;
}

bool SexyAppBase::ReadBufferFromFile(const std::string& theFileName, void*& theBuffer, unsigned long& theBufferLen)
{
	void* aDataPtr = NULL;
	int aDataSize;
	if (!mSexyCacheBuffers || !gSexyCache.GetData(GetFullPath(theFileName), "Buffer", &aDataPtr, &aDataSize))
	{
		if (mResStreamsManager != NULL && mResStreamsManager->IsInitialized("dynamic.rsb"))
		{
			std::string aFilePath = theFileName;
			uint32 aGroupId = mResStreamsManager->GetGroupForFile(aFilePath);
			if (aGroupId != 0xFFFFFFFF)
			{
				uint8* aData = NULL;
				uint32 aSize = 0;
				if (mResStreamsManager->GetResidentFileBuffer(aGroupId, aFilePath, &aData, &aSize))
				{
					theBuffer = aData;
					theBufferLen = aSize;
					return true;
				}
			}
		}

		PFILE* aFP = p_fopen(theFileName.c_str(), "rb");
		if (aFP == NULL)
		{
			if (mWriteToSexyCache && mSexyCacheBuffers)
			{
				uchar* aPtr = (uchar*)gSexyCache.AllocSetData(GetFullPath(theFileName), "Buffer", 1);
				if (aPtr != NULL)
				{
					*aPtr = 0;
					gSexyCache.SetFileDeps(GetFullPath(theFileName), "Buffer", GetFullPath(theFileName));
					gSexyCache.SetData(aPtr);
				}
			}

			mErrorLog = "aFP == NULL";
			return false;
		}

		p_fseek(aFP, 0, SEEK_END);
		int aSize = p_ftell(aFP);
		p_fseek(aFP, 0, SEEK_SET);
		uchar* aData = new uchar[aSize];
		p_fread(aData, 1, aSize, aFP);
		p_fclose(aFP);
		theBuffer = aData;
		theBufferLen = aSize;
		if (mWriteToSexyCache && mSexyCacheBuffers)
		{
			uchar* aPtr = (uchar*)gSexyCache.AllocSetData(GetFullPath(theFileName), "Buffer", aSize + 1);
			if (aPtr != NULL)
			{
				*aPtr = 1;
				memcpy(aPtr + 1, aData, aSize);
				gSexyCache.SetFileDeps(GetFullPath(theFileName), "Buffer", GetFullPath(theFileName));
				gSexyCache.SetData(aPtr);
			}
		}

		return true;
	}

	if (!*(uchar*)aDataPtr)
		return false;

	theBuffer = (uchar*)aDataPtr + 1;
	theBufferLen = aDataSize - 1;
	return true;
}

void SexyAppBase::ColorizeImage(Image* theImage, const Color& theColor)
{
	MemoryImage* aSrcMemoryImage = theImage ? theImage->AsMemoryImage() : NULL;
	if (aSrcMemoryImage == NULL)
		return;

	uint32* aBits;
	int aNumColors;

	if (aSrcMemoryImage->mColorTable == NULL)
	{
		aBits = aSrcMemoryImage->GetBits();
		aNumColors = theImage->GetWidth() * theImage->GetHeight();
	}
	else
	{
		aBits = aSrcMemoryImage->mColorTable;
		aNumColors = 256;
	}

	if ((theColor.mAlpha <= 255) && (theColor.mRed <= 255) && (theColor.mGreen <= 255) && (theColor.mBlue <= 255))
	{
		for (int i = 0; i < aNumColors; i++)
		{
			ulong aColor = aBits[i];
			aBits[i] =
				((((aColor & 0xFF000000) >> 8) * theColor.mAlpha) & 0xFF000000) |
				((((aColor & 0xFF0000) * theColor.mRed) >> 8) & 0xFF0000) |
				((((aColor & 0x00FF00) * theColor.mGreen) >> 8) & 0x00FF00) |
				((((aColor & 0x0000FF) * theColor.mBlue) >> 8) & 0x0000FF);
		}
	}
	else
	{
		for (int i = 0; i < aNumColors; i++)
		{
			uint32 aColor = aBits[i];

			int aAlpha = ((aColor >> 24) * theColor.mAlpha) / 255;
			int aRed = (((aColor >> 16) & 0xFF) * theColor.mRed) / 255;
			int aGreen = (((aColor >> 8) & 0xFF) * theColor.mGreen) / 255;
			int aBlue = ((aColor & 0xFF) * theColor.mBlue) / 255;

			if (aAlpha > 255)
				aAlpha = 255;
			if (aRed > 255)
				aRed = 255;
			if (aGreen > 255)
				aGreen = 255;
			if (aBlue > 255)
				aBlue = 255;

			aBits[i] = (aAlpha << 24) | (aRed << 16) | (aGreen << 8) | aBlue;
		}
	}

	aSrcMemoryImage->BitsChanged();
}

DeviceImage* SexyAppBase::CreateColorizedImage(Image* theImage, const Color& theColor)
{
	MemoryImage* aSrcMemoryImage = theImage ? theImage->AsMemoryImage() : NULL;
	if (aSrcMemoryImage == NULL)
		return NULL;

	DeviceImage* anImage = new DeviceImage(this);
	anImage->Create(theImage->GetWidth(), theImage->GetHeight());

	uint32* aSrcBits;
	uint32* aDestBits;
	int aNumColors;

	if (aSrcMemoryImage->mColorTable == NULL)
	{
		aSrcBits = aSrcMemoryImage->GetBits();
		aDestBits = anImage->GetBits();
		aNumColors = theImage->GetWidth() * theImage->GetHeight();
	}
	else
	{
		aSrcBits = aSrcMemoryImage->mColorTable;
		aDestBits = anImage->mColorTable = new uint32[256];
		anImage->mColorIndices = new uchar[anImage->mWidth * theImage->mHeight];
		memcpy(anImage->mColorIndices, aSrcMemoryImage->mColorIndices, anImage->mWidth * theImage->mHeight);
		aNumColors = 256;
	}

	if ((theColor.mAlpha <= 255) && (theColor.mRed <= 255) && (theColor.mGreen <= 255) && (theColor.mBlue <= 255))
	{
		for (int i = 0; i < aNumColors; i++)
		{
			ulong aColor = aSrcBits[i];
			aDestBits[i] =
				((((aColor & 0xFF000000) >> 8) * theColor.mAlpha) & 0xFF000000) |
				((((aColor & 0xFF0000) * theColor.mRed) >> 8) & 0xFF0000) |
				((((aColor & 0x00FF00) * theColor.mGreen) >> 8) & 0x00FF00) |
				((((aColor & 0x0000FF) * theColor.mBlue) >> 8) & 0x0000FF);
		}
	}
	else
	{
		for (int i = 0; i < aNumColors; i++)
		{
			uint32 aColor = aSrcBits[i];

			int aAlpha = ((aColor >> 24) * theColor.mAlpha) / 255;
			int aRed = (((aColor >> 16) & 0xFF) * theColor.mRed) / 255;
			int aGreen = (((aColor >> 8) & 0xFF) * theColor.mGreen) / 255;
			int aBlue = ((aColor & 0xFF) * theColor.mBlue) / 255;

			if (aAlpha > 255)
				aAlpha = 255;
			if (aRed > 255)
				aRed = 255;
			if (aGreen > 255)
				aGreen = 255;
			if (aBlue > 255)
				aBlue = 255;

			aDestBits[i] = (aAlpha << 24) | (aRed << 16) | (aGreen << 8) | aBlue;
		}
	}

	anImage->BitsChanged();
	return anImage;
}
