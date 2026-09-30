//
//  SexyAppBase.cpp
//
//  SexyAppFramework, PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-27.
//

#include "SexyAppBase.h"
#include "AutoCrit.h"
#include "MTRand.h"
#include "Widget.h"

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

	for (WidgetSafeDeleteList::iterator anItr = mSafeDeleteList.begin(); anItr != mSafeDeleteList.end();)
	{
		if (mUpdateAppDepth > anItr->mUpdateAppDepth)
		{
			anItr++;
			continue;
		}

		if (anItr->mWidget != NULL)
			delete anItr->mWidget;

		anItr = mSafeDeleteList.erase(anItr);
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

bool SexyAppBase::ChangeDirHook(const char * i_arg)
{
	return false;
}

void SexyAppBase::Done3dTesting()
{
}

void SexyAppBase::UpdateFramesF(float i_arg)
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

bool SexyAppBase::DebugKeyDownAsync(int i_arg0, bool i_arg1, bool i_arg2)
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

void SexyAppBase::OnResourcesUpdated(ResourceUpdateType i_arg0, void* i_arg1)
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

void SexyAppBase::AccelerometerChanged(double i_arg0, double i_arg1, double i_arg2, double i_arg3)
{
}

void SexyAppBase::AppEnteredBackground()
{
}

void SexyAppBase::AppEnteredForeground()
{
}

bool SexyAppBase::HandleOpenURLRequest(const std::string& i_arg)
{
	return false;
}

void SexyAppBase::UIOrientationChanged(UI_ORIENTATION i_arg)
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
	return (UI_ORIENTATION)4;
}

UI_ORIENTATION SexyAppBase::FullScreenUIOrientationRight()
{
	return (UI_ORIENTATION)3;
}

bool SexyAppBase::KeyDown(int i_arg)
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
