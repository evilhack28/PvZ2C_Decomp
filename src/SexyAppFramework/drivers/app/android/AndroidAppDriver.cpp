//
//  AndroidAppDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-17.
//
#include "SexyAppFramework/Common.h"
#include <android/log.h>
#include "SexyAppFramework/drivers/app/android/AndroidAppDriver.h"
#include "SexyAppFramework/SexyTime.h"
#include "SexyAppFramework/AutoCrit.h"
#include "SexyAppFramework/drivers/app/android/AndroidAppEvents.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidGraphicsDriver.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/IFileDriver.h"
#include "SexyAppFramework/IResStreamsDriver.h"
#include "SexyAppFramework/MTRand.h"
#include "SexyAppFramework/SexyCache.h"
#include "SexyAppFramework/PakLib/PakInterface.h"
#include "SexyAppFramework/drivers/graphics/opengl/OpenGLIdRegistry.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

AndroidAppDriver::AndroidAppDriver(SexyAppBase* theApp) :
	mApp(theApp),
	mGLView(NULL),
	mAndroidGraphicsDriver(NULL),
	m_loading_thread(-1),
	mScreenWidth(-1),
	mScreenHeight(-1),
	mAudioSessionActive(false),
	mScreenRotation(0),
	mStartRotTick(0),
	mbLerpOrientationChanges(false),
	mbIsOrientationChangeInProgress(false),
	mbRotatedHalfWay(false),
	mNewOrientation((UI_ORIENTATION)0),
	mInterfaceOrientation((UI_ORIENTATION)0),
	mDebugOverlayRSB(false),
	mDebugOverlayGraphics(false),
	mConfigInitted(false),
	mMiniUpdateExtraFrame(0),
	mUseMultitouch(true),
	mHasSingleTouch(false),
	mbForceReinitSurface(false),
	mbAppIsSuspended(false),
	mLostFocusCount(0)
{
	mRotationInterpolator = mbLerpOrientationChanges ? new FloatInterpolator() : NULL;
	mLastFrameTime = SexyTime();
}

AndroidAppDriver::~AndroidAppDriver()
{
	delete mRotationInterpolator;
	mRotationInterpolator = NULL;
}

void AndroidAppDriver::Start()
{
	if (mApp->mAutoStartLoadingThread)
		StartLoadingThread();

	uint64 aTime = SexyTime();
	mApp->mRunning = true;
	mApp->mLastTime = aTime;
	mApp->mLastUserInputTick = aTime;
	mApp->mLastTimerTime = aTime;
	mApp->SetSfxVolume(mApp->mSfxVolume);
	mApp->SetMusicVolume(mApp->mMusicVolume);
}

void AndroidAppDriver::Init()
{
	mApp->mRandSeed = SexyTime();
	SRand(mApp->mRandSeed);
	srand(SexyTime());
}

void AndroidAppDriver::SysMouseUp(int x, int y, int button)
{
	mApp->mWidgetManager->MouseUp(x, y, button);
}

void AndroidAppDriver::Remove3DData(MemoryImage* theMemoryImage)
{
	if (mAndroidGraphicsDriver)
		mAndroidGraphicsDriver->Remove3DData(theMemoryImage);
}

void AndroidAppDriver::Redraw()
{
	mAndroidGraphicsDriver->Redraw();
}

void AndroidAppDriver::OnBackButtonPressed()
{
	mApp->OnBackButtonPressed();
}

void AndroidAppDriver::SysMouseDown(int x, int y, int button)
{
	mApp->mWidgetManager->MouseDown(x, y, button);
}

void AndroidAppDriver::SysMouseMove(int x, int y)
{
	mApp->mWidgetManager->MouseMove(x, y);
}

void AndroidAppDriver::SysMouseDrag(int x, int y)
{
	mApp->mWidgetManager->MouseDrag(x, y);
}

void AndroidAppDriver::SysMouseWheel(int theDelta)
{
	mApp->mWidgetManager->MouseWheel(theDelta);
}

void AndroidAppDriver::TransformPoint(Point* point)
{
	mApp->mWidgetManager->RemapMouse(point->mX, point->mY);
}

void AndroidAppDriver::RotateUI(UI_ORIENTATION theSrcOrientation, UI_ORIENTATION theDestOrientation)
{
	mbIsOrientationChangeInProgress = true;
	mNewOrientation = theDestOrientation;
}

void AndroidAppDriver::SetDeviceResolution(int w, int h)
{
	mFrontBufferWidth = w;
	mFrontBufferHeight = h;
}

std::string AndroidAppDriver::GetProductVersionName()
{
	return Android::Info::SysGetProductVersion();
}

std::string AndroidAppDriver::GetPackageName()
{
	return Android::Info::SysGetPackageName();
}

void AndroidAppDriver::VibrateWithPattern(long long pattern[], int isRepeat)
{
	Android::Device::VibrateWithPattern(pattern, isRepeat);
}

void AndroidAppDriver::CopyToClipboard(const std::string& theString)
{
	Android::Device::CopyToClipBoard(theString);
}

void AndroidAppDriver::DoParseCmdLine()
{
	OutputDebugStrF("AndroidAppDriver - DoParseCmdLine");
}

void AndroidAppDriver::ParseCmdLine(const std::string& theCmdLine)
{
	OutputDebugStrF("AndroidAppDriver - ParseCmdLine");
}

bool AndroidAppDriver::DebugKeyDown(int theKey)
{
	if (theKey == 0x3f)
	{
		mDebugOverlayRSB = !mDebugOverlayRSB;
		return true;
	}
	if (theKey == 0x2c)
	{
		mDebugOverlayGraphics = !mDebugOverlayGraphics;
		return true;
	}
	return false;
}

void AndroidAppDriver::TransformTouch(Touch* touch)
{
	TransformPoint(&touch->location);
	TransformPoint(&touch->previousLocation);
}

void AndroidAppDriver::ActivateAudioSession()
{
	mApp->ActivateAudioSession();
	mAudioSessionActive = true;
}

void AndroidAppDriver::DeactivateAudioSession()
{
	mApp->DeactivateAudioSession();
	mAudioSessionActive = false;
}

bool AndroidAppDriver::ConfigReadString(const std::string& theValueName, std::string* theString)
{
	if (!InitConfig())
		return false;
	return Android::Config::ConfigReadUTF8String(theValueName, *theString);
}

bool AndroidAppDriver::ConfigReadString(const std::string& theValueName, std::wstring* theString)
{
	if (!InitConfig())
		return false;
	return Android::Config::ConfigReadWideString(theValueName, *theString);
}

bool AndroidAppDriver::ConfigReadInteger(const std::string& theValueName, int* theValue)
{
	if (!InitConfig())
		return false;
	return Android::Config::ConfigReadInteger(theValueName, *theValue);
}

bool AndroidAppDriver::ConfigReadBoolean(const std::string& theValueName, bool* theValue)
{
	if (!InitConfig())
		return false;
	return Android::Config::ConfigReadBoolean(theValueName, *theValue);
}

bool AndroidAppDriver::ConfigWriteString(const std::string& theValueName, const std::string& theString)
{
	if (!InitConfig())
		return false;
	return Android::Config::ConfigWriteUTF8String(theValueName, theString);
}

bool AndroidAppDriver::ConfigWriteString(const std::string& theValueName, const std::wstring& theString)
{
	if (!InitConfig())
		return false;
	return Android::Config::ConfigWriteWideString(theValueName, theString);
}

bool AndroidAppDriver::ConfigWriteInteger(const std::string& theValueName, int theValue)
{
	if (!InitConfig())
		return false;
	return Android::Config::ConfigWriteInteger(theValueName, theValue);
}

bool AndroidAppDriver::ConfigWriteBoolean(const std::string& theValueName, bool theValue)
{
	if (!InitConfig())
		return false;
	return Android::Config::ConfigWriteBoolean(theValueName, theValue);
}

void AndroidAppDriver::GotFocus()
{
	mbAppIsSuspended = false;
	ActivateAudioSession();
	mApp->GotFocus();
	ApplicationDidBecomeActive();
	Android::UI::DidRecieveFocus();
}

void AndroidAppDriver::LostFocus()
{
	mbAppIsSuspended = true;
	ApplicationDidEnterBackground();
	mApp->LostFocus();
	DeactivateAudioSession();
}

void AndroidAppDriver::ClearUpdateBacklog(bool relaxForASecond)
{
	mApp->mLastTimeCheck = SexyTime();
	mApp->mUpdateFTimeAcc = 0;
	if (relaxForASecond)
		mApp->mRelaxUpdateBacklogCount = 1000;
}

/////////////// Events ///////////////

void AndroidAppDriver::HandleAndroidEvents()
{
	AppEventQueue_t aEvents;
	{
		AutoCrit aCrit(sAppEventQueueCS);
		aEvents.assign(sAppEventQueue.begin(), sAppEventQueue.end());
		sAppEventQueue.clear();
	}

	for (AppEventQueue_t::iterator anItr = aEvents.begin(); anItr != aEvents.end(); ++anItr)
	{
		AndroidAppEvent* anEvent = *anItr;
		switch (anEvent->mType)
		{
		case eAAET_OrientationChange:
			HandleAndroidOrientationChange(anEvent);
			break;
		case eAAET_StartFromUrl:
			HandleAndroidStartFromUrl(anEvent);
			break;
		case eAAET_GotFocus:
			GotFocus();
			break;
		case eAAET_LostFocus:
			LostFocus();
			break;
		case eAAET_ApplicationWillBecomeForeground:
			HandleApplicationWillBecomeForeground();
			break;
		case eAAET_ApplicationDidBecomeActive:
			HandleApplicationDidBecomeActive();
			break;
		case eAAET_ApplicationWillResignActive:
			HandleApplicationWillResignActive();
			break;
		case eAAET_ApplicationDidEnterBackground:
			HandleApplicationDidEnterBackground();
			break;
		case eAAET_Lifecycle:
		case eAAET_MAX:
			OutputDebugStrF("Warning: Received unhandled android event ID");
			break;
		}
		delete anEvent;
	}
}

void AndroidAppDriver::StaticEnqueueCallback(const Delegate0& callback)
{
	__android_log_print(ANDROID_LOG_INFO, "AndroidAppDriver", "Enqueue callback delegate.");
	AutoCrit aCrit(sCallbackQueueCS);
	sCallbackQueue.push_back(callback);
}

void AndroidAppDriver::StaticEnqueueAndroidEvent(AndroidAppEvent* pEvent)
{
	AutoCrit aCrit(sAppEventQueueCS);
	sAppEventQueue.push_back(pEvent);
}

void AndroidAppDriver::StaticApplicationOpenURL(std::string theURL)
{
	StaticEnqueueAndroidEvent(new AndroidAppStartFromUrlEvent(theURL));
}

void AndroidAppDriver::StaticNotifyOrientationChanged(UI_ORIENTATION oldOrientation, UI_ORIENTATION newOrientation, int width, int height)
{
	StaticEnqueueAndroidEvent(new AndroidAppOrientationChangeEvent(oldOrientation, newOrientation, width, height));
}

void AndroidAppDriver::StaticNotifyApplicationGainFocus()
{
	StaticEnqueueAndroidEvent(new AndroidGotFocusEvent());
}

void AndroidAppDriver::StaticNotifyApplicationLoseFocus()
{
	StaticEnqueueAndroidEvent(new AndroidLostFocusEvent());
}

void AndroidAppDriver::StaticNotifyApplicationWillBecomeForeground()
{
	StaticEnqueueAndroidEvent(new AndroidApplicationWillBecomeForegroundEvent());
}

void AndroidAppDriver::StaticNotifyApplicationDidBecomeActive()
{
	StaticEnqueueAndroidEvent(new AndroidApplicationDidBecomeActiveEvent());
}

void AndroidAppDriver::StaticNotifyApplicationWillResignActive()
{
	StaticEnqueueAndroidEvent(new AndroidApplicationWillResignActiveEvent());
}

void AndroidAppDriver::StaticNotifyApplicationDidEnterBackground()
{
	StaticEnqueueAndroidEvent(new AndroidApplicationDidEnterBackgroundEvent());
}

void AndroidAppDriver::HandleAndroidSurfaceChange(int width, int height)
{
	mAndroidGraphicsDriver->ReinitForSurfaceChange(mInterfaceOrientation, width, height, mbForceReinitSurface);
	mbForceReinitSurface = false;
	SetupOrientation();
}

void AndroidAppDriver::HandleApplicationWillBecomeForeground()
{
	OutputDebugStrF("HandleApplicationWillBecomeForeground");
	mbForceReinitSurface = true;
	ApplicationWillBecomeForeground();
}

void AndroidAppDriver::HandleApplicationDidBecomeActive()
{
	OutputDebugStrF("HandleApplicationDidBecomeActive");
	GotFocus();
	ApplicationDidBecomeActive();
}

void AndroidAppDriver::InitPreAppLaunch()
{
	if (mApp->mShutdown)
		return;

	mApp->InitPropertiesHook();
	mApp->ReadFromRegistry();
	mApp->mFileDriver->InitSaveDataFolder();
	if (!mApp->mCmdLineParsed)
		DoParseCmdLine();

	gPakInterface->AddPakFile(mApp->mFileDriver->GetLoadDataPath() + "main.pak");
	mApp->PreDisplayHook();
	OutputDebugStrF("Resize: %dx%d", mApp->mWidth, mApp->mHeight);
	mApp->mWidgetManager->Resize(Rect(0, 0, mApp->mWidth, mApp->mHeight), Rect(0, 0, mApp->mWidth, mApp->mHeight));
	mApp->mInteractiveSoundManager = mApp->mInteractiveAudioDriver->CreateSoundManager();
	mApp->mResStreamsDriver->InitWithApp(mApp);
}


void AndroidAppDriver::HandleAndroidStartFromUrl(AndroidAppEvent* pEvent)
{
	AndroidAppStartFromUrlEvent* anEvent = (AndroidAppStartFromUrlEvent*)pEvent;
	std::allocator<char> anAlloc;
	std::string aStr(anEvent->mStartUrl.c_str(), anAlloc);
	SexyURL aURL(aStr);
	ApplicationOpenURL(aURL);
}

void AndroidAppDriver::HandleAndroidSurfaceCreated()
{
	OpenGLIdRegistry::StaticValidateAllIds();
}

void AndroidAppDriver::HandleApplicationWillResignActive()
{
	OutputDebugStrF("HandleApplicationWillResignActive");
	LostFocus();
	ApplicationWillResignActive();
}

void AndroidAppDriver::TouchesCanceled_Internal()
{
	mTouches.clear();
	mHasSingleTouch = false;
}

void AndroidAppDriver::TouchesCanceled()
{
	mApp->TouchesCanceled();
	TouchesCanceled_Internal();
}

void AndroidAppDriver::HandleAndroidLifecyclePause()
{
	AtomicIncrement(&mLostFocusCount);
	mbAppIsSuspended = true;
}

void AndroidAppDriver::HandleAndroidLifecycleResume()
{
	if (mLostFocusCount > 0)
	{
		mbForceReinitSurface = true;
		AtomicDecrement(&mLostFocusCount);
	}
	else
		ApplicationDidBecomeActive();
}

void AndroidAppDriver::HandleAndroidLifecycleDestroy()
{
	mApp->mShutdown = true;
}

void AndroidAppDriver::HandleAndroidLifecycleEvent(AndroidAppEvent* pEvent)
{
	switch (((AndroidAppLifeCycleEvent*)pEvent)->mLifecycleStage)
	{
	case eALC_Resume:
		HandleAndroidLifecycleResume();
		break;
	case eALC_Pause:
		HandleAndroidLifecyclePause();
		break;
	case eALC_Destroy:
		HandleAndroidLifecycleDestroy();
		break;
	}
}

/////////////// Stubs ///////////////

int AndroidAppDriver::MsgBox(const std::string& theText, const std::string& theTitle, int theFlags)
{
	return 0;
}

int AndroidAppDriver::MsgBox(const std::wstring& theText, const std::wstring& theTitle, int theFlags)
{
	return 0;
}

int AndroidAppDriver::GetCursor()
{
	return 0;
}

bool AndroidAppDriver::DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown)
{
	return false;
}

bool AndroidAppDriver::Is3DAccelerated()
{
	return true;
}

bool AndroidAppDriver::Is3DAccelerationSupported()
{
	return true;
}

bool AndroidAppDriver::Is3DAccelerationRecommended()
{
	return true;
}

bool AndroidAppDriver::CheckSignature(const Buffer& theBuffer, const std::string& theFileName)
{
	return true;
}

bool AndroidAppDriver::ReloadAllResources()
{
	return true;
}

bool AndroidAppDriver::ConfigGetSubKeys(const std::string& theKeyName, StringVector* theSubKeys)
{
	return false;
}

bool AndroidAppDriver::ConfigReadData(const std::string& theValueName, uchar* theValue, ulong* theLength)
{
	return false;
}

bool AndroidAppDriver::ConfigWriteData(const std::string& theValueName, const uchar* theValue, ulong theLength)
{
	return false;
}

bool AndroidAppDriver::ShouldPauseUpdates()
{
	return mbIsOrientationChangeInProgress;
}

const SexyMatrix4& AndroidAppDriver::GetScreenMatrix()
{
	return mScreenMatrix;
}

const SexyMatrix4& AndroidAppDriver::GetDeviceScreenMatrix()
{
	return mDeviceScreenMatrix;
}

bool AndroidAppDriver::IsUIOrientationAllowed(UI_ORIENTATION theOrientation)
{
	return Android::Device::IsSupportedUIOrientation(theOrientation);
}

void AndroidAppDriver::Vibrate(long long milliseconds)
{
	Android::Device::Vibrate(milliseconds);
}

bool AndroidAppDriver::IsKeyboardShowing()
{
	return Android::Device::IsKeyboardShowing();
}

void AndroidAppDriver::ShowKeyboard()
{
	Android::Device::ShowKeyboard();
}

void AndroidAppDriver::HideKeyboard()
{
	Android::Device::HideKeyboard();
}

void AndroidAppDriver::CancelVibrate()
{
	Android::Device::CancelVibrate();
}

void AndroidAppDriver::LaunchApp()
{
	Android::Game::SetAppDriverPointer(this);
}

int AndroidAppDriver::GetProductVersionCode()
{
	return Android::Info::SysGetProductVersionCode();
}

long AndroidAppDriver::GetMemoryUsed()
{
	return Android::Diag::GetUsedMemory();
}

long AndroidAppDriver::GetMemoryAvailable()
{
	return Android::Diag::GetAvailMemory();
}

void AndroidAppDriver::InputCancelAll()
{
	TouchesCanceled_Internal();
}

void AndroidAppDriver::Shutdown()
{
}

void AndroidAppDriver::DoExit(int theCode)
{
}

void AndroidAppDriver::BeginPopup()
{
}

void AndroidAppDriver::EndPopup()
{
}

void AndroidAppDriver::Popup(const std::wstring& theString)
{
}

void AndroidAppDriver::HandleCmdLineParam(const std::string& theParamName, const std::string& theParamValue)
{
}

void AndroidAppDriver::SetCursor(int theCursorNum)
{
}

void AndroidAppDriver::EnableCustomCursors(bool enabled)
{
}

void AndroidAppDriver::SetCursorImage(int theCursorNum, Image* theImage)
{
}

void AndroidAppDriver::SwitchScreenMode()
{
}

void AndroidAppDriver::SwitchScreenMode(bool wantWindowed)
{
}

void AndroidAppDriver::SwitchScreenMode(bool wantWindowed, bool is3d, bool force)
{
}

void AndroidAppDriver::ShowPhoneNumKeyboard()
{
}

void AndroidAppDriver::ShowEmailKeyboard()
{
}

void AndroidAppDriver::Set3DAcclerated(bool is3D, bool reinit)
{
}

void AndroidAppDriver::OrientationChange()
{
}

void AndroidAppDriver::EnableMusic(bool enable)
{
}

void AndroidAppDriver::DoVibration()
{
}

void AndroidAppDriver::SyncConfig()
{
}

void AndroidAppDriver::DeviceOrientationChanged(DeviceOrientation orientation)
{
}

void AndroidAppDriver::AccelerometerDidAccelerate(double timestamp, double ax, double ay, double az)
{
}

void AndroidAppDriver::DumpProgramInfo()
{
}

void AndroidAppDriver::Popup(const std::string& theString)
{
	printf("AndroidAppDriver::Popup: %s\n", theString.c_str());
}

std::string AndroidAppDriver::GetDeviceName()
{
	return "";
}

std::string AndroidAppDriver::GetClipboard()
{
	return "";
}

std::string AndroidAppDriver::GetGameSEHInfo()
{
	return "";
}

void AndroidAppDriver::ConfigEraseValue(const SexyString& theValueName)
{
	ConfigEraseKey(theValueName);
}

bool AndroidAppDriver::ConfigEraseKey(const SexyString& theKeyName)
{
	if (!InitConfig())
		return false;
	SexyString aKey = WStringToSexyString(theKeyName);
	if (aKey.length())
		Android::Config::ConfigEraseKey(theKeyName);
	return true;
}

void AndroidAppDriver::SetFPS(bool i_highFPS)
{
	Android::Device::SetFPS(i_highFPS);
}

bool AndroidAppDriver::IsHighFPS()
{
	return Android::Device::IsHighFPS();
}


/////////////// Files ///////////////

bool AndroidAppDriver::ReadBufferFromFile(const std::string& theFileName, Buffer* theBuffer, bool dontWriteToDemo)
{
	void* aDataPtr;
	int aDataSize;
	if (!mApp->mSexyCacheBuffers || !gSexyCache.GetData(GetFullPath(theFileName), "Buffer", &aDataPtr, &aDataSize))
	{
		PFILE* aFP = p_fopen(theFileName.c_str(), "rb");
		if (aFP == NULL)
		{
			if (mApp->mWriteToSexyCache && mApp->mSexyCacheBuffers)
			{
				uchar* aPtr = (uchar*)gSexyCache.AllocSetData(GetFullPath(theFileName), "Buffer", 1);
				if (aPtr != NULL)
				{
					*aPtr = 0;
					gSexyCache.SetFileDeps(GetFullPath(theFileName), "Buffer", GetFullPath(theFileName));
					gSexyCache.SetData(aPtr);
					return false;
				}
			}
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
		if (mApp->mWriteToSexyCache && mApp->mSexyCacheBuffers)
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

bool AndroidAppDriver::WriteBufferToFile(const std::string& theFileName, const Buffer* theBuffer)
{
	return WriteBytesToFile(theFileName, theBuffer->GetDataPtr(), theBuffer->GetDataLen());
}

bool AndroidAppDriver::WriteBytesToFile(const std::string& theFileName, const void* theData, unsigned long theDataLen)
{
	std::string aFileName = mApp->mFileDriver->FixPath(theFileName);
	MkDir(GetFileDir(aFileName, false));
	FILE* aFP = fopen(aFileName.c_str(), "w+b");
	if (aFP == NULL)
		return false;

	fwrite(theData, 1, theDataLen, aFP);
	fclose(aFP);
	if (mApp->mSexyCacheBuffers && mApp->mWriteToSexyCache)
	{
		uchar* aPtr = (uchar*)gSexyCache.AllocSetData(GetFullPath(theFileName), "Buffer", theDataLen + 1);
		if (aPtr != NULL)
		{
			*aPtr = 1;
			memcpy(aPtr + 1, theData, theDataLen);
			gSexyCache.SetFileDeps(GetFullPath(theFileName), "Buffer", GetFullPath(theFileName));
			gSexyCache.SetData(aPtr);
		}
	}
	return true;
}

bool AndroidAppDriver::WriteBytesToFileAt(const std::string& theFilePath, const void* theData, unsigned long theDataLen, unsigned long theSeekPos)
{
	std::string aFileName = mApp->mFileDriver->FixPath(theFilePath);
	MkDir(GetFileDir(aFileName, false));
	FILE* aFP = fopen(aFileName.c_str(), "r+b");
	if (aFP == NULL)
		return false;

	fseek(aFP, 0, SEEK_END);
	if (ferror(aFP))
	{
		fclose(aFP);
		return false;
	}
	unsigned long aFileSize = ftell(aFP);
	if (ferror(aFP))
	{
		fclose(aFP);
		return false;
	}
	fseek(aFP, 0, SEEK_SET);
	if (ferror(aFP))
	{
		fclose(aFP);
		return false;
	}
	if (theSeekPos + theDataLen > aFileSize)
	{
		fclose(aFP);
		return false;
	}
	fseek(aFP, theSeekPos, SEEK_SET);
	if (ferror(aFP))
	{
		fclose(aFP);
		return false;
	}
	fwrite(theData, 1, theDataLen, aFP);
	if (ferror(aFP))
	{
		fclose(aFP);
		return false;
	}
	fclose(aFP);
	return true;
}

bool AndroidAppDriver::WriteBytesToFileEnd(const std::string& theFilePath, const void* theData, unsigned long theDataLen)
{
	std::string aFileName = mApp->mFileDriver->FixPath(theFilePath);
	MkDir(GetFileDir(aFileName, false));
	FILE* aFP = fopen(aFileName.c_str(), "a+b");
	if (aFP == NULL)
		return false;

	fseek(aFP, 0, SEEK_END);
	if (ferror(aFP))
	{
		fclose(aFP);
		return false;
	}
	ftell(aFP);
	if (ferror(aFP))
	{
		fclose(aFP);
		return false;
	}
	fwrite(theData, 1, theDataLen, aFP);
	if (ferror(aFP))
	{
		fclose(aFP);
		return false;
	}
	fclose(aFP);
	return true;
}

bool AndroidAppDriver::CopyFile(const std::string& theFromFilePath, const std::string& theToFilePath)
{
	IFileDriver* aFileDriver = mApp->mFileDriver;
	std::string aFromFileName = aFileDriver->FixPath(theFromFilePath);
	std::string aToFileName = aFileDriver->FixPath(theToFilePath);
	MkDir(GetFileDir(aToFileName, false));
	FILE* aSrc = fopen(aFromFileName.c_str(), "rb");
	FILE* aDest = fopen(aToFileName.c_str(), "wb");
	if (aSrc == NULL || aDest == NULL)
	{
		if (aSrc != NULL)
			fclose(aSrc);
		if (aDest != NULL)
			fclose(aDest);
		return false;
	}

	char aBuffer[1024];
	size_t aSize;
	while ((aSize = fread(aBuffer, 1, sizeof(aBuffer), aSrc)) != 0)
		fwrite(aBuffer, 1, aSize, aDest);
	fclose(aSrc);
	fclose(aDest);
	return true;
}

bool AndroidAppDriver::RenameFile(const std::string& theFromFilePath, const std::string& theToFilePath)
{
	MkDir(GetFileDir(theToFilePath, false));
	return rename(theFromFilePath.c_str(), theToFilePath.c_str()) == 0;
}

bool AndroidAppDriver::CreateFileOfSize(const std::string& theFilePath, unsigned long theDataLen)
{
	std::string aFileName = mApp->mFileDriver->FixPath(theFilePath);
	MkDir(GetFileDir(aFileName, false));
	FILE* aFP = fopen(aFileName.c_str(), "w+b");
	if (aFP == NULL)
		return false;

	fseek(aFP, theDataLen - 1, SEEK_SET);
	if (ferror(aFP))
	{
		fclose(aFP);
		return false;
	}
	fputc('0', aFP);
	if (ferror(aFP))
	{
		fclose(aFP);
		return false;
	}
	fclose(aFP);
	return true;
}

/////////////// Images ///////////////

DeviceImage* AndroidAppDriver::GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps)
{
	if (mbAppIsSuspended)
		return NULL;
	return mAndroidGraphicsDriver->GetOptimizedImage(theFileName, commitBits, allowTriReps);
}

DeviceImage* AndroidAppDriver::GetOptimizedImage(ImageLib::Image* image, bool commitBits, bool allowTriReps, bool inShouldDeleteSrcImage)
{
	if (mbAppIsSuspended)
		return NULL;
	return mAndroidGraphicsDriver->GetOptimizedImage(image, commitBits, allowTriReps, inShouldDeleteSrcImage);
}

/////////////// Gestures ///////////////

void AndroidAppDriver::OnGesturePinch(Point i_centerPoint, int i_distanceBetweenFingersSquared, float i_scaleDelta)
{
	Point aPoint = i_centerPoint;
	TransformPoint(&aPoint);
	float aScale = (float)aPoint.mX / (float)i_centerPoint.mX;
	mApp->OnGesturePinch(aPoint, aScale * aScale * i_distanceBetweenFingersSquared, i_scaleDelta);
}

void AndroidAppDriver::OnGestureFlick(GestureFlickDirection i_direction, Point i_startingLocation)
{
	Point aPoint = i_startingLocation;
	TransformPoint(&aPoint);
	mApp->OnGestureFlick(i_direction, aPoint);
}

void AndroidAppDriver::OnGestureLongPress(Point i_startingLocation)
{
	Point aPoint = i_startingLocation;
	TransformPoint(&aPoint);
	mApp->OnGestureLongPress(aPoint);
}

/////////////// Loading ///////////////

void AndroidAppDriver::StartLoadingThread()
{
	if (!mApp->mLoadingThreadStarted)
	{
		mApp->mYieldMainThread = true;
		pthread_attr_t aAttr;
		pthread_attr_init(&aAttr);
		pthread_create(&m_loading_thread, &aAttr, _android_loading_thread_start_routine, this);
		pthread_attr_destroy(&aAttr);
		mApp->mLoadingThreadStarted = true;
	}
}

double AndroidAppDriver::GetLoadingThreadProgress()
{
	if (mApp->mLoaded)
		return 1.0;
	if (!mApp->mLoadingThreadStarted)
		return 0.0;
	if (mApp->mNumLoadingThreadTasks == 0)
		return 0.0;
	return std::min((double)mApp->mCompletedLoadingThreadTasks / mApp->mNumLoadingThreadTasks, 1.0);
}

void AndroidAppDriver::InitWindowCreated()
{
	mApp->PreDDInterfaceInitHook();
	mAndroidGraphicsDriver = new AndroidGraphicsDriver(this, mApp);
	mApp->mGraphicsDriver = mAndroidGraphicsDriver;
	mApp->mResStreamsDriver->AttachGraphicsDriver(mAndroidGraphicsDriver);
	mInterfaceOrientation = (UI_ORIENTATION)Android::Device::GetStartupUIOrientation();
	mAndroidGraphicsDriver->Init(mInterfaceOrientation);
	mApp->PostDDInterfaceInitHook();
	mApp->InitHook();
	mApp->mInitialized = true;
}

void AndroidAppDriver::InitPostAppLaunch()
{
	InitWindowCreated();
	mUseMultitouch = mApp->GetBoolean("drivers.android.use_multitouch", true);
}

/////////////// Touch ///////////////

void AndroidAppDriver::TouchBegan(const Touch& touch)
{
	Touch aTouch = touch;
	TransformTouch(&aTouch);
	if (mUseMultitouch || !mHasSingleTouch)
	{
		mApp->TouchBegan(aTouch);
		mCurSingleTouch = aTouch;
		mHasSingleTouch = true;
	}
	mTouches.push_back(aTouch);
}

void AndroidAppDriver::TouchMoved(const Touch& touch)
{
	Touch aTouch = touch;
	TransformTouch(&aTouch);
	if (mUseMultitouch || (mHasSingleTouch && mCurSingleTouch == aTouch))
		mApp->TouchMoved(aTouch);
	TouchList::iterator anItr = std::find(mTouches.begin(), mTouches.end(), aTouch);
	if (anItr != mTouches.end())
		*anItr = aTouch;
}

/////////////// Orientation ///////////////

void AndroidAppDriver::SetupScreenMatrix(float theRotation)
{
	mScreenMatrix.LoadIdentity();
	mScreenMatrix.Translate(-(mApp->mScreenBounds.mWidth / 2), -(mApp->mScreenBounds.mHeight / 2), 0);
	if (theRotation != 0)
		mScreenMatrix.RotateRadZ(theRotation * (M_PI / 180));
	mScreenMatrix.Scale(1.0f / (mScreenWidth / 2), -1.0f / (mScreenHeight / 2), 1.0f);
	mScreenRotation = theRotation;
}

void AndroidAppDriver::HandleAndroidOrientationChange(AndroidAppEvent* pEvent)
{
	AndroidAppOrientationChangeEvent* anEvent = (AndroidAppOrientationChangeEvent*)pEvent;
	if (anEvent && (anEvent->mNewWidth || anEvent->mNewHeight))
		Android::UI::ShowAlertDialog("温馨提示", "检测到应用程序尺寸变更，请重启游戏。", "确定", true);
	else
		RotateUI(anEvent->mOldOrientation, anEvent->mNewOrientation);
}

bool AndroidAppDriver::OpenURL(const std::string& theURL, bool shutdownOnOpen)
{
	bool aResult = mApp->mIsOpeningURL;
	if (!aResult || theURL != mApp->mOpeningURL)
	{
		mApp->mIsOpeningURL = true;
		mApp->mShutdownOnURLOpen = shutdownOnOpen;
		mApp->mOpeningURL = theURL;
		mApp->mOpeningURLTime = SexyTime();
		aResult = Android::Web::SysOpenURL(theURL);
		if (aResult)
		{
			mApp->URLOpenSucceeded(theURL);
			mApp->mIsOpeningURL = false;
			return aResult;
		}
		mApp->URLOpenFailed(theURL);
		mApp->mIsOpeningURL = aResult;
	}
	return aResult;
}

void AndroidAppDriver::SetupOrientation()
{
	Android::Graphics::GetGLViewSize(this, &mScreenWidth, &mScreenHeight);
	int aX = mApp->mWidescreenTranslate;
	int aY = aX;
	int aWidth = mAndroidGraphicsDriver->mWidth;
	int aHeight = mAndroidGraphicsDriver->mHeight;
	if (mApp->mWidescreenTranslate)
	{
		aX = (mApp->mWidth - aWidth) / 2;
		aY = (mApp->mHeight - aHeight) / 2;
	}
	mApp->mScreenBounds.mX = aX;
	mApp->mScreenBounds.mY = aY;
	mApp->mScreenBounds.mWidth = aWidth;
	mApp->mScreenBounds.mHeight = aHeight;
	SetupScreenMatrix(0);
	mApp->mWidgetManager->Resize(mApp->mScreenBounds, Rect(0, 0, mApp->mOrigScreenWidth, mApp->mOrigScreenHeight));
	mApp->mWidgetManager->mImage = mAndroidGraphicsDriver->GetScreenImage();
	mApp->mWidgetManager->MarkAllDirty();
}

void AndroidAppDriver::UpdateFTimeAcc()
{
	uint64 aTime = SexyTime();
	if (mApp->mLastTimeCheck != 0)
	{
		int aDeltaTime = (int)aTime - (int)mApp->mLastTimeCheck;
		mApp->mUpdateFTimeAcc = std::min(aDeltaTime + mApp->mUpdateFTimeAcc, 200.0);
		if (mApp->mRelaxUpdateBacklogCount > 0)
			mApp->mRelaxUpdateBacklogCount = std::max(mApp->mRelaxUpdateBacklogCount - aDeltaTime, 0);
	}
	mApp->mLastTimeCheck = aTime;
}

void AndroidAppDriver::DoUpdateFramesF(float theFrac)
{
	if (mApp->mVSyncUpdates && !mApp->mMinimized)
		mApp->mWidgetManager->UpdateFrameF(theFrac);
}

bool AndroidAppDriver::DoUpdateFrames()
{
	if (mApp->mLoadingThreadCompleted && !mApp->mLoaded)
	{
		mApp->mYieldMainThread = false;
		mApp->mLoaded = true;
		mApp->LoadingThreadCompleted();
	}

	if (mbLerpOrientationChanges)
	{
		if (mbIsOrientationChangeInProgress)
		{
			uint64 aElapsed = SexyTime() - mStartRotTick;
			float aRotation = (*mRotationInterpolator)((float)aElapsed);
			if (!mbRotatedHalfWay)
			{
				if (aElapsed >= mRotationInterpolator->LastTick() / 2)
				{
					mInterfaceOrientation = mNewOrientation;
					OrientationChange();
					mApp->UIOrientationChanged(mNewOrientation);
					mbRotatedHalfWay = true;
				}
			}
			SetupScreenMatrix(aRotation);
			if (aElapsed > mRotationInterpolator->LastTick())
				mbIsOrientationChangeInProgress = false;
		}
	}
	else if (mbIsOrientationChangeInProgress)
	{
		mInterfaceOrientation = mNewOrientation;
		OrientationChange();
		mApp->UIOrientationChanged(mNewOrientation);
		mbIsOrientationChangeInProgress = false;
	}
	mApp->UpdateFrames();
	return true;
}

/////////////// Update ///////////////

void AndroidAppDriver::DisplayLinkUpdateAppStep()
{
	bool aAppIsSuspended = mbAppIsSuspended;
	mAndroidGraphicsDriver->ClearBuffers();
	HandleCallbacks();
	HandleAndroidEvents();
	Android::UI::ProcessEvents(this);
	if (!aAppIsSuspended)
	{
		OrientationChange();
		{
			MTAutoDisallowRand aDisallowRand;
			mAndroidGraphicsDriver->DetermineScreenImageType();
			mApp->mIsDrawing = true;
			mApp->DrawScreen();
			mApp->mIsDrawing = false;
		}
		DoUpdateFrames();
		DoUpdateFramesF(1.0f);
		mApp->ProcessSafeDeleteList();
		Redraw();
	}
	else
	{
		DoUpdateFrames();
		DoUpdateFramesF(1.0f);
		mApp->ProcessSafeDeleteList();
	}
}

void AndroidAppDriver::HandleCallbacks()
{
	CallbackQueue_t aCallbacks;
	{
		AutoCrit aCrit(sCallbackQueueCS);
		aCallbacks.assign(sCallbackQueue.begin(), sCallbackQueue.end());
		sCallbackQueue.clear();
	}
	if (!aCallbacks.empty())
		__android_log_print(ANDROID_LOG_INFO, "AndroidAppDriver", "Dispatch %d callbacks.", (int)aCallbacks.size());
	for (CallbackQueue_t::iterator anItr = aCallbacks.begin(); anItr != aCallbacks.end(); ++anItr)
		(*anItr)();
}

void AndroidAppDriver::StaticRemoveCallbacksForInstanceContext(void* instanceContext)
{
	AutoCrit aCrit(sCallbackQueueCS);
	CallbackQueue_t::iterator anItr = std::remove_if(sCallbackQueue.begin(), sCallbackQueue.end(), CallbackInstanceEquals(instanceContext));
	__android_log_print(ANDROID_LOG_INFO, "AndroidAppDriver", "StaticRemoveCallbacksForInstanceContext( %p ) - %d removed.", instanceContext, (int)(sCallbackQueue.end() - anItr));
	sCallbackQueue.erase(anItr, sCallbackQueue.end());
}

bool AndroidAppDriver::UpdateAppStep(bool* updated)
{
	if (updated != NULL)
		*updated = false;

	if (mApp->mExitToTop)
		return false;

	if (mApp->mUpdateAppState == UPDATESTATE_PROCESS_DONE)
		mApp->mUpdateAppState = UPDATESTATE_MESSAGES;

	mApp->mUpdateAppDepth++;

	if (mApp->mUpdateAppState == UPDATESTATE_MESSAGES)
	{
		Android::UI::ProcessEvents(this);
		if (mApp->mUpdateAppState == UPDATESTATE_MESSAGES)
			mApp->mUpdateAppState = UPDATESTATE_PROCESS_1;
	}
	else
	{
		if (mApp->mStepMode == 0)
		{
			int aCount = mApp->mUpdateCount;
			Process();
			if (updated != NULL)
				*updated = mApp->mUpdateCount != aCount;
		}
		else if (mApp->mStepMode == 2)
		{
			SexySleep((uint)mApp->mFrameTime);
			mApp->mUpdateAppState = UPDATESTATE_PROCESS_DONE;
		}
		else
		{
			mApp->mStepMode = 2;
			DoUpdateFrames();
			DoUpdateFramesF(1.0f);
			DrawDirtyStuff(false);
		}
	}

	mApp->mUpdateAppDepth--;
	return true;
}

/////////////// Device ///////////////

int AndroidAppDriver::GetNotchPlatformByPackageName(const std::string& i_package)
{
	if (!(i_package == "pvz2cthdhwct") && !(i_package == "com.popcap.pvz2cthdhwct") && !(i_package == "com.popcap.pvz2nHWCM"))
	{
		if (i_package == "pvz2cthdhwct" || i_package == "com.popcap.pvz2cthdhwct" || i_package == "com.popcap.pvz2nHWCM")
			return NOTCH_XIAOMI;
		if (i_package == "pvz2bbg" || i_package == "pvz2cthdbbg" || i_package == "com.popcap.pvz2bbg" || i_package == "com.popcap.pvz2cthdbbg")
			return NOTCH_VIVO;
	}
	return NOTCH_HUAWEI;
}

int AndroidAppDriver::CalcOppoFullScreenOffset()
{
	std::string aPackage = Android::Util::GetPackageName();
	if (aPackage == "pvz2cthdhwct" || aPackage == "com.popcap.pvz2cthdhwct" || aPackage == "com.popcap.pvz2nHWCM" || aPackage == "com.popcap.pvz2cthdnxm" || aPackage == "com.popcap.pvz2bbg" || aPackage == "com.popcap.pvz2cthdbbg")
		return Android::Diag::GetNotchHeight(GetNotchPlatformByPackageName(aPackage));
	return (int)(Android::Graphics::GetGLViewScaleFactor(this) * 80);
}

void AndroidAppDriver::KeyDown(KeyCode theKeyCode, SexyChar theChar)
{
	if (mApp->KeyDown(theKeyCode))
		return;
	mApp->mWidgetManager->KeyDown(theKeyCode);
	mApp->mWidgetManager->KeyChar(theChar);
}
