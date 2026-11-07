//
//  WwiseInteractiveAudioDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-07.
//
//  Some static helper functions have no name in the game; their names here are not real.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/audio/wwise/WwiseInteractiveAudioDriver.h"
#include "SexyAppFramework/drivers/audio/wwise/WwiseSoundManager.h"
#include "SexyAppFramework/drivers/audio/wwise/SexyIOHookBlocking.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <AK/MusicEngine/Common/AkMusicEngine.h>

using namespace Sexy;

void WWise_LocalOutputFunc(AK::Monitor::ErrorCode in_eErrorCode, const char* in_pszError, AK::Monitor::ErrorLevel in_eErrorLevel, AkPlayingID in_playingID, AkGameObjectID in_gameObjID);

bool WwiseInteractiveAudioDriver::m_hasError = false;

/////////////// Helpers ///////////////

static AkGameObjectID ToAkGameObjectID(AudioGameObjectId in_objectId)
{
	return (AkGameObjectID)in_objectId;
}

static AudioGameObjectId ToAudioGameObjectId(AkGameObjectID in_gameObjID)
{
	return (AudioGameObjectId)in_gameObjID;
}

static AkCallbackType ToAkCallbackType(InteractiveAudioCallbackType in_callbackType)
{
	return (AkCallbackType)(in_callbackType & (AK_EndOfEvent | AK_EndOfDynamicSequenceItem | AK_Marker | AK_Duration | AK_SpeakerVolumeMatrix | AK_MusicPlayStarted | AK_MusicSyncAll));
}

static void WWise_EventCallbackFunc(AkCallbackType in_eType, AkCallbackInfo* in_pCallbackInfo)
{
	IInteractiveAudioCallbackListener* aListener = (IInteractiveAudioCallbackListener*)in_pCallbackInfo->pCookie;
	AudioGameObjectId aObjectId = ToAudioGameObjectId(in_pCallbackInfo->gameObjID);
	switch (in_eType)
	{
	case AK_EndOfEvent:
	{
		AkEventCallbackInfo* aEventInfo = (AkEventCallbackInfo*)in_pCallbackInfo;
		aListener->OnEndOfEvent(aObjectId, aEventInfo->playingID, aEventInfo->eventID);
		break;
	}
	case AK_EndOfDynamicSequenceItem:
		aListener->OnEndOfDynamicSequenceItem(aObjectId);
		break;
	case AK_Marker:
		aListener->OnMarker(aObjectId);
		break;
	case AK_Duration:
		aListener->OnDuration(aObjectId);
		break;
	case AK_SpeakerVolumeMatrix:
		aListener->OnSpeakerVolumeMatrix(aObjectId);
		break;
	case AK_MusicPlayStarted:
		aListener->OnMusicPlayStarted(aObjectId);
		break;
	case AK_MusicSyncBeat:
		aListener->OnMusicSyncBeat(aObjectId);
		break;
	case AK_MusicSyncBar:
		aListener->OnMusicSyncBar(aObjectId);
		break;
	case AK_MusicSyncEntry:
		aListener->OnMusicSyncEntry(aObjectId, ((AkMusicSyncCallbackInfo*)in_pCallbackInfo)->playingID);
		break;
	case AK_MusicSyncExit:
		aListener->OnMusicSyncExit(aObjectId, ((AkMusicSyncCallbackInfo*)in_pCallbackInfo)->playingID);
		break;
	case AK_MusicSyncGrid:
		aListener->OnMusicSyncGrid(aObjectId);
		break;
	case AK_MusicSyncUserCue:
		aListener->OnMusicSyncUserCue(aObjectId);
		break;
	case AK_MusicSyncPoint:
		aListener->OnMusicSyncPoint(aObjectId);
		break;
	default:
		break;
	}
}

/////////////// Lifecycle ///////////////

WwiseInteractiveAudioDriver::WwiseInteractiveAudioDriver()
	: mbWwiseIsInitialized(false)
{
	m_pLowLevelIO = new SexyIOHookBlocking();
}

WwiseInteractiveAudioDriver::~WwiseInteractiveAudioDriver()
{
	TermInteractiveAudioDriver();
}

InteractiveSoundManager* WwiseInteractiveAudioDriver::CreateSoundManager()
{
	return new WwiseSoundManager(this);
}

bool WwiseInteractiveAudioDriver::InitInteractiveAudioDriver()
{
	m_filePath = gFileDriver->GetLoadDataPath();

	AkInitSettings initSettings;
	AkMemSettings memSettings;
	memSettings.uMaxNumPools = 20;
	AkStreamMgrSettings stmSettings;
	AK::StreamMgr::GetDefaultSettings(stmSettings);
	AkDeviceSettings deviceSettings;
	AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);
	AK::SoundEngine::GetDefaultInitSettings(initSettings);
	initSettings.uDefaultPoolSize = 4 * 1024 * 1024;
	AkPlatformInitSettings platformInitSettings;
	AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);
	platformInitSettings.uLEngineDefaultPoolSize = 3 * 1024 * 1024;
	std::string aHardwareModel;
	Android::Diag::GetHardwareModel(aHardwareModel);
	platformInitSettings.uSampleRate = strcasecmp(aHardwareModel.c_str(), "Amazon Kindle Fire") == 0 ? 24000 : 32000;
	AkMusicSettings musicInit;
	AK::MusicEngine::GetDefaultInitSettings(musicInit);

	if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
		return false;
	if (!AK::StreamMgr::Create(stmSettings))
		return false;
	deviceSettings.uSchedulerTypeFlags = AK_SCHEDULER_BLOCKING;
	if (m_pLowLevelIO->Init(deviceSettings) != AK_Success)
		return false;
	m_pLowLevelIO->SetBasePath(m_filePath.c_str());
	if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
		return false;
	if (AK::MusicEngine::Init(&musicInit) != AK_Success)
		return false;

	AK::SoundEngine::RegisterPlugin(AkPluginTypeSource, AKCOMPANYID_AUDIOKINETIC, AKSOURCEID_SILENCE, CreateSilenceSource, CreateSilenceSourceParams);
	AK::SoundEngine::RegisterCodec(AKCOMPANYID_AUDIOKINETIC, AKCODECID_VORBIS, CreateVorbisFilePlugin, CreateVorbisBankPlugin);
	AK::Monitor::SetLocalOutput(AK::Monitor::ErrorLevel_All, WWise_LocalOutputFunc);
	mbWwiseIsInitialized = true;
	return true;
}

void WwiseInteractiveAudioDriver::TermInteractiveAudioDriver()
{
	mbWwiseIsInitialized = false;
	AK::MusicEngine::Term();
	AK::SoundEngine::Term();
	m_pLowLevelIO->Term();
	delete m_pLowLevelIO;
	if (AK::IAkStreamMgr::Get())
		AK::IAkStreamMgr::Get()->Destroy();
	AK::MemoryMgr::Term();
}

void WwiseInteractiveAudioDriver::Update()
{
	if (!m_hasError && mbWwiseIsInitialized)
		AK::SoundEngine::RenderAudio();
}

void WwiseInteractiveAudioDriver::GotFocus()
{
	if (mbWwiseIsInitialized)
		AK::SoundEngine::WakeupFromSuspend();
}

void WwiseInteractiveAudioDriver::LostFocus()
{
	if (mbWwiseIsInitialized)
		AK::SoundEngine::Suspend();
}

/////////////// Events ///////////////

AudioPlayingId WwiseInteractiveAudioDriver::SendEvent(AudioEventId eventId, AudioGameObjectId objectId)
{
	if (m_hasError)
		return IA_INVALID_PLAYING_ID;
	return AK::SoundEngine::PostEvent(eventId, ToAkGameObjectID(objectId));
}

AudioPlayingId WwiseInteractiveAudioDriver::SendEvent(const char* eventName, AudioGameObjectId objectId)
{
	if (m_hasError)
		return IA_INVALID_PLAYING_ID;
	return AK::SoundEngine::PostEvent(eventName, ToAkGameObjectID(objectId));
}

AudioPlayingId WwiseInteractiveAudioDriver::SendEventCallback(AudioEventId eventId, InteractiveAudioCallbackType callbackType, IInteractiveAudioCallbackListener* callbackObject, AudioGameObjectId objectId)
{
	return AK::SoundEngine::PostEvent(eventId, ToAkGameObjectID(objectId), ToAkCallbackType(callbackType), WWise_EventCallbackFunc, callbackObject);
}

AudioPlayingId WwiseInteractiveAudioDriver::SendEventCallback(const char* eventName, InteractiveAudioCallbackType callbackType, IInteractiveAudioCallbackListener* callbackObject, AudioGameObjectId objectId)
{
	return AK::SoundEngine::PostEvent(eventName, ToAkGameObjectID(objectId), ToAkCallbackType(callbackType), WWise_EventCallbackFunc, callbackObject);
}

/////////////// RTPCs and switches ///////////////

bool WwiseInteractiveAudioDriver::SetRTPCValue(AudioRtpcId rtpcId, float rtpcValue, AudioGameObjectId objectId)
{
	return AK::SoundEngine::SetRTPCValue(rtpcId, rtpcValue, ToAkGameObjectID(objectId)) == AK_Success;
}

bool WwiseInteractiveAudioDriver::SetRTPCValue(const char* rtpcName, float rtpcValue, AudioGameObjectId objectId)
{
	return AK::SoundEngine::SetRTPCValue(rtpcName, rtpcValue, ToAkGameObjectID(objectId)) == AK_Success;
}

bool WwiseInteractiveAudioDriver::GetRTPCValue(AudioRtpcId rtpcId, float& rtpcValue, AudioGameObjectId objectId)
{
	AkGameObjectID aGameObjID = ToAkGameObjectID(objectId);
	AK::SoundEngine::Query::RTPCValue_type aValueType = AK::SoundEngine::Query::RTPCValue_Default;
	return AK::SoundEngine::Query::GetRTPCValue(rtpcId, aGameObjID, rtpcValue, aValueType) == AK_Success;
}

bool WwiseInteractiveAudioDriver::GetRTPCValue(const char* rtpcName, float& rtpcValue, AudioGameObjectId objectId)
{
	AkGameObjectID aGameObjID = ToAkGameObjectID(objectId);
	AK::SoundEngine::Query::RTPCValue_type aValueType = AK::SoundEngine::Query::RTPCValue_Default;
	return AK::SoundEngine::Query::GetRTPCValue(rtpcName, aGameObjID, rtpcValue, aValueType) == AK_Success;
}

bool WwiseInteractiveAudioDriver::SetSwitch(const char* in_pszSwitchGroup, const char* in_pszSwitchState, AudioGameObjectId in_objectId)
{
	return AK::SoundEngine::SetSwitch(in_pszSwitchGroup, in_pszSwitchState, ToAkGameObjectID(in_objectId)) == AK_Success;
}

bool WwiseInteractiveAudioDriver::SetSwitch(AudioSwitchGroupId groupId, AudioSwitchStateId stateId, AudioGameObjectId objectId)
{
	return AK::SoundEngine::SetSwitch(groupId, stateId, ToAkGameObjectID(objectId)) == AK_Success;
}

/////////////// States ///////////////

bool WwiseInteractiveAudioDriver::SetState(AudioStateGroupId groupId, AudioStateId StateId)
{
	return AK::SoundEngine::SetState(groupId, StateId) == AK_Success;
}

bool WwiseInteractiveAudioDriver::SetState(const char* groupName, const char* stateName)
{
	return AK::SoundEngine::SetState(groupName, stateName) == AK_Success;
}

/////////////// Game objects ///////////////

void WwiseInteractiveAudioDriver::RegisterGameObject(AudioGameObjectId objectId)
{
	if (objectId != IA_GENERIC_GAME_OBJECT)
		AK::SoundEngine::RegisterGameObj((AkGameObjectID)objectId);
}

void WwiseInteractiveAudioDriver::UnregisterGameObject(AudioGameObjectId objectId)
{
	if (objectId != IA_GENERIC_GAME_OBJECT)
		AK::SoundEngine::UnregisterGameObj((AkGameObjectID)objectId);
}

void WwiseInteractiveAudioDriver::SetGameObjectPosition(AudioGameObjectId i_objectId, const SexyVector2& i_objectPosition)
{
	if (i_objectId != IA_GENERIC_GAME_OBJECT)
	{
		AkSoundPosition aPosition;
		aPosition.Orientation.X = 0.0f;
		aPosition.Orientation.Y = 0.0f;
		aPosition.Orientation.Z = 0.0f;
		aPosition.Position.X = i_objectPosition.x;
		aPosition.Position.Y = i_objectPosition.y;
		aPosition.Position.Z = 0.0f;
		AK::SoundEngine::SetPosition((AkGameObjectID)i_objectId, aPosition);
	}
}

void WwiseInteractiveAudioDriver::SetListenerPosition(const SexyVector2& i_listenerPosition, int i_listenerIndex)
{
	AkListenerPosition aPosition;
	aPosition.OrientationTop.X = 0.0f;
	aPosition.OrientationTop.Y = 0.0f;
	aPosition.OrientationTop.Z = 0.0f;
	aPosition.OrientationFront.X = 0.0f;
	aPosition.OrientationFront.Y = 0.0f;
	aPosition.OrientationFront.Z = 0.0f;
	aPosition.Position.X = i_listenerPosition.x;
	aPosition.Position.Y = i_listenerPosition.y;
	aPosition.Position.Z = 0.0f;
	AK::SoundEngine::SetListenerPosition(aPosition, i_listenerIndex);
}

/////////////// Ids ///////////////

AudioRtpcId WwiseInteractiveAudioDriver::GetIdFromString(char const* InRtpcName) const
{
	if (InRtpcName == NULL)
		return IA_INVALID_UNIQUE_ID;
	return AK::SoundEngine::GetIDFromString(InRtpcName);
}

AudioRtpcId WwiseInteractiveAudioDriver::GetRtpcIdFromString(char const* InRtpcName) const
{
	return GetIdFromString(InRtpcName);
}

AudioRtpcId WwiseInteractiveAudioDriver::GetEventIdFromString(char const* InRtpcName) const
{
	return GetIdFromString(InRtpcName);
}

/////////////// Callbacks ///////////////

void WwiseInteractiveAudioDriver::CancelEventCallback(AudioEventId eventId)
{
	AK::SoundEngine::CancelEventCallback(eventId);
}

void WwiseInteractiveAudioDriver::CancelEventCallbackByContext(void* pDeadContext)
{
	AK::SoundEngine::CancelEventCallbackCookie(pDeadContext);
}

/////////////// Android ///////////////

void WwiseInteractiveAudioDriver::HACK_SetPvZStreamingFilePathMap(std::map<std::string, std::string> fileIdToPathMap)
{
	m_pLowLevelIO->mFileIdToPathMap = fileIdToPathMap;
}

void WwiseInteractiveAudioDriver::HACK_SetAndroidAssetInfo(std::string const& in_fullPath)
{
	std::string aArchiveFilename;
	long aFileOffset = 0;
	long aFileSize = 0;
	if (Android::Resources::GetAssetFileInfo(in_fullPath, aArchiveFilename, aFileOffset, aFileSize))
	{
		m_pLowLevelIO->mAPKFilename = aArchiveFilename;
		m_pLowLevelIO->mRSBOffset = aFileOffset;
		m_pLowLevelIO->mbDataIsInAPK = !aArchiveFilename.empty();
	}
}
