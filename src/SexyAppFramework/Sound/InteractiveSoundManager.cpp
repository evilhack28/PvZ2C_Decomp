//
//  InteractiveSoundManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-06.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/InteractiveSoundManager.h"
#include "SexyAppFramework/SexyApp.h"
#include "SexyAppFramework/ResourceManager.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "SexyAppFramework/drivers/audio/wwise/WwiseInteractiveAudioDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

InteractiveSoundManager::InteractiveSoundManager(IInteractiveAudioDriver* InDriver)
	: mAudioDriver(InDriver)
	, mMasterVolumeRTPC(0)
	, mSfxVolumeRTPC(0)
	, mMusicVolumeRTPC(0)
{
	mAudioDriver = InDriver;
	mbPause = false;
}

bool InteractiveSoundManager::Initialize(const InteractiveSoundManagerConfig& config)
{
	bool aSuccess = true;
	mMasterVolumeRTPC = GetRtpcIdFromString(config.mMasterVolumeParamName);
	mSfxVolumeRTPC = GetRtpcIdFromString(config.mSfxVolumeParamName);
	mMusicVolumeRTPC = GetRtpcIdFromString(config.mMusicVolumeParamName);

	for (std::vector<std::string>::const_iterator it = config.mLoadGroups.begin(); it != config.mLoadGroups.end(); ++it)
	{
		ResourceGroup* aGroup = gSexyApp->mResourceManager->GetResourceGroupNamed(*it);
		if (aGroup != NULL && aGroup->Load())
			mLoadedGroups.push_back(aGroup);
		else
			aSuccess = false;
	}

	for (std::vector<std::string>::const_iterator it = config.mLoadIndexGroups.begin(); it != config.mLoadIndexGroups.end(); ++it)
	{
		ResourceGroup* aGroup = gSexyApp->mResourceManager->GetResourceGroupNamed(*it);
		if (aGroup != NULL && aGroup->LoadFileIndex())
			mLoadedIndexGroups.push_back(aGroup);
		else
			aSuccess = false;
	}

	if (gSexyAppBase->mResStreamsManager->GetRSBPath().size() != 0)
	{
		std::string aPath = gSexyAppBase->mResStreamsManager->GetRSBPath();
		WwiseInteractiveAudioDriver* aDriver = (WwiseInteractiveAudioDriver*)mAudioDriver;
		aDriver->HACK_SetPvZStreamingFilePathMap(config.mFileIdToPathMap);
		aDriver->HACK_SetAndroidAssetInfo(aPath);
	}

	mbResLoaded = true;
	return aSuccess;
}

void InteractiveSoundManager::Terminate()
{
	for (std::vector<ResourceGroup*>::const_iterator it = mLoadedGroups.begin(); it != mLoadedGroups.end(); ++it)
		(*it)->Unload();

	bool aMore;
	for (std::vector<ResourceGroup*>::const_iterator it = mLoadedIndexGroups.begin(); (aMore = it != mLoadedIndexGroups.end()); ++it)
		(*it)->UnloadFileIndex();

	mLoadedGroups.clear();
	mLoadedIndexGroups.clear();
	mbResLoaded = aMore;
}

/////////////// Playback ///////////////

void InteractiveSoundManager::PauseAll(bool bPause)
{
	if (mbResLoaded && mbPause != bPause)
	{
		mbPause = bPause;
		if (bPause)
			mAudioDriver->SendEvent("Pause_Master_Audio_Bus");
		else
			mAudioDriver->SendEvent("Resume_Master_Audio_Bus");
		Update();
	}
}

void InteractiveSoundManager::StopAll()
{
	mAudioDriver->SendEvent("Stop_Master_Audio_Bus");
}

void InteractiveSoundManager::Update()
{
	mAudioDriver->Update();
}

/////////////// Volume ///////////////

void InteractiveSoundManager::SetSfxVolume(float newVolume)
{
	if (mSfxVolumeRTPC != 0)
		SetRTPCValue(mSfxVolumeRTPC, newVolume * 100.0f, IA_GLOBAL_GAME_OBJECT);
}

float InteractiveSoundManager::GetSfxVolume() const
{
	float aVolume = 0.0f;
	if (mSfxVolumeRTPC != 0)
	{
		if (GetRTPCValue(mSfxVolumeRTPC, aVolume, IA_GLOBAL_GAME_OBJECT))
			aVolume *= 0.01f;
		else
			aVolume = 0.0f;
	}
	return aVolume;
}

void InteractiveSoundManager::SetMusicVolume(float newMusicVolume)
{
	if (mMusicVolumeRTPC != 0)
		SetRTPCValue(mMusicVolumeRTPC, newMusicVolume * 100.0f, IA_GLOBAL_GAME_OBJECT);
}

float InteractiveSoundManager::GetMusicVolume() const
{
	float aVolume = 0.0f;
	if (mMusicVolumeRTPC != 0)
	{
		if (GetRTPCValue(mMusicVolumeRTPC, aVolume, IA_GLOBAL_GAME_OBJECT))
			aVolume = 0.0f;
		else
			aVolume *= 0.01f;
	}
	return aVolume;
}

void InteractiveSoundManager::SetMasterVolume(float newVolume)
{
	if (mMasterVolumeRTPC != 0)
		SetRTPCValue(mMasterVolumeRTPC, newVolume, IA_GLOBAL_GAME_OBJECT);
}

float InteractiveSoundManager::GetMasterVolume() const
{
	float aVolume = 0.0f;
	if (mMasterVolumeRTPC != 0)
	{
		if (GetRTPCValue(mMasterVolumeRTPC, aVolume, IA_GLOBAL_GAME_OBJECT))
			aVolume = 0.0f;
	}
	return aVolume;
}

/////////////// Driver forwarding ///////////////

void InteractiveSoundManager::RegisterAudioGameObject(AudioGameObjectId newObject)
{
	mAudioDriver->RegisterGameObject(newObject);
}

void InteractiveSoundManager::UnregisterAudioGameObject(AudioGameObjectId newObject)
{
	mAudioDriver->UnregisterGameObject(newObject);
}

AudioPlayingId InteractiveSoundManager::SendEvent(const char* InEventName, AudioGameObjectId InGameObjectId)
{
	return mAudioDriver->SendEvent(InEventName, InGameObjectId);
}

AudioPlayingId InteractiveSoundManager::SendEvent(AudioEventId InEventId, AudioGameObjectId InGameObjectId)
{
	return mAudioDriver->SendEvent(InEventId, InGameObjectId);
}

AudioPlayingId InteractiveSoundManager::SendEventCallback(const char* InEventName, InteractiveAudioCallbackType InCallbackType, IInteractiveAudioCallbackListener* InCallbackObject, AudioGameObjectId InGameObjectId)
{
	return mAudioDriver->SendEventCallback(InEventName, InCallbackType, InCallbackObject, InGameObjectId);
}

AudioPlayingId InteractiveSoundManager::SendEventCallback(AudioEventId InEventId, InteractiveAudioCallbackType InCallbackType, IInteractiveAudioCallbackListener* InCallbackObject, AudioGameObjectId InGameObjectId)
{
	return mAudioDriver->SendEventCallback(InEventId, InCallbackType, InCallbackObject, InGameObjectId);
}

bool InteractiveSoundManager::SetRTPCValue(const char* InRtpcName, float InRtpcValue, AudioGameObjectId InGameObjectId)
{
	return mAudioDriver->SetRTPCValue(InRtpcName, InRtpcValue, InGameObjectId);
}

bool InteractiveSoundManager::SetRTPCValue(AudioRtpcId InRtpcId, float InRtpcValue, AudioGameObjectId InGameObjectId)
{
	return mAudioDriver->SetRTPCValue(InRtpcId, InRtpcValue, InGameObjectId);
}

bool InteractiveSoundManager::GetRTPCValue(const char* InRtpcName, float& OutRtpcValue, AudioGameObjectId InGameObjectId) const
{
	return mAudioDriver->GetRTPCValue(InRtpcName, OutRtpcValue, InGameObjectId);
}

bool InteractiveSoundManager::GetRTPCValue(AudioRtpcId InRtpcId, float& OutRtpcValue, AudioGameObjectId InGameObjectId) const
{
	return mAudioDriver->GetRTPCValue(InRtpcId, OutRtpcValue, InGameObjectId);
}

AudioPlayingId InteractiveSoundManager::SendEventRTPC(const char* InEventName, const char* InRtpcName, float InRtpcValue, AudioGameObjectId InGameObjectId)
{
	if (!mAudioDriver->SetRTPCValue(InRtpcName, InRtpcValue, InGameObjectId))
		return 0;
	return mAudioDriver->SendEvent(InEventName, InGameObjectId);
}

AudioPlayingId InteractiveSoundManager::SendEventRTPC(AudioEventId InEventId, AudioRtpcId InRtpcId, float InRtpcValue, AudioGameObjectId InGameObjectId)
{
	if (!mAudioDriver->SetRTPCValue(InRtpcId, InRtpcValue, InGameObjectId))
		return 0;
	return mAudioDriver->SendEvent(InEventId, InGameObjectId);
}

AudioRtpcId InteractiveSoundManager::GetRtpcIdFromString(const char* InRtpcName) const
{
	return mAudioDriver->GetRtpcIdFromString(InRtpcName);
}

void InteractiveSoundManager::CancelEventCallback(AudioEventId InEventId)
{
	mAudioDriver->CancelEventCallback(InEventId);
}

void InteractiveSoundManager::CancelEventCallbackByContext(void* InContext)
{
	mAudioDriver->CancelEventCallbackByContext(InContext);
}
