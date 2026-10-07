//
//  AudioMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AudioMgr.h"
#include "PvZ/LawnApp.h"
#include "PvZ/GameEventMgr.h"
#include "PvZ/PVZDB.h"
#include "PvZ/StreamingMusicList.h"
#include "SexyAppFramework/InteractiveSoundManager.h"

AudioMgr::AudioMgr()
{
}

AudioMgr::~AudioMgr()
{
}

/////////////// Driver forwarders ///////////////

void AudioMgr::OnLevelEnded()
{
    m_throttledAudios.clear();
}

uint32 AudioMgr::SendEvent(uint32 i_eventId, void* i_objectId)
{
    if (m_audioDriver)
        return m_audioDriver->SendEvent(i_eventId, (AudioGameObjectId)i_objectId);
    return 0;
}

uint32 AudioMgr::SendEvent(const char* i_eventName, void* i_objectId)
{
    uint32 id = 0;
    if (i_eventName != NULL && *i_eventName != '\0' && m_audioDriver)
        id = m_audioDriver->SendEvent(i_eventName, (AudioGameObjectId)i_objectId);
    return id;
}

void AudioMgr::CancelEventCallback(uint32 i_eventId)
{
    if (m_audioDriver)
        m_audioDriver->CancelEventCallback(i_eventId);
}

bool AudioMgr::SetState(uint32 i_stateGroupId, uint32 i_stateGroupValue)
{
    if (m_audioDriver)
        return m_audioDriver->SetState(i_stateGroupId, i_stateGroupValue);
    return false;
}

bool AudioMgr::SetState(const char* i_stateGroupName, const char* i_stateGroupValue)
{
    if (m_audioDriver)
        return m_audioDriver->SetState(i_stateGroupName, i_stateGroupValue);
    return false;
}

bool AudioMgr::SetSwitch(const char* i_switchGroup, const char* i_switchState, void* i_objectId)
{
    if (m_audioDriver)
        return m_audioDriver->SetSwitch(i_switchGroup, i_switchState, (AudioGameObjectId)i_objectId);
    return false;
}

void AudioMgr::RegisterForAudio(void* i_objectId)
{
    if (m_audioDriver)
        m_audioDriver->RegisterGameObject((AudioGameObjectId)i_objectId);
}

void AudioMgr::UnregisterForAudio(void* i_objectId)
{
    if (m_audioDriver)
        m_audioDriver->UnregisterGameObject((AudioGameObjectId)i_objectId);
}

void AudioMgr::SetObjectPosition(void* i_objectId, const SexyVector2& i_position)
{
    if (m_audioDriver)
        m_audioDriver->SetGameObjectPosition((AudioGameObjectId)i_objectId, i_position);
}

void AudioMgr::SetListenerPosition(const SexyVector2& i_position, int i_listenerIndex)
{
    if (m_audioDriver)
        m_audioDriver->SetListenerPosition(i_position, i_listenerIndex);
}

void AudioMgr::AddDataToCallbackQueue(uint32 i_data)
{
    CallbackDataQueue.Produce(i_data);
}

bool AudioMgr::ReadDataFromCallbackQueue(uint32& o_data)
{
    return CallbackDataQueue.Consume(o_data);
}

bool AudioMgr::SetRTPCValue(uint32 i_rtpcId, double i_rtpcValue, void* i_objectId)
{
    if (m_audioDriver)
        return m_audioDriver->SetRTPCValue(i_rtpcId, (float)i_rtpcValue, (AudioGameObjectId)i_objectId);
    return false;
}

bool AudioMgr::SetRTPCValue(const char* i_rtpcName, double i_rtpcValue, void* i_objectId)
{
    if (m_audioDriver)
        return m_audioDriver->SetRTPCValue(i_rtpcName, (float)i_rtpcValue, (AudioGameObjectId)i_objectId);
    return false;
}

bool AudioMgr::SetRTPCValue(uint32 i_rtpcId, double i_rtpcValue)
{
    if (m_audioDriver)
        return m_audioDriver->SetRTPCValue(i_rtpcId, (float)i_rtpcValue);
    return false;
}

bool AudioMgr::SetRTPCValue(const char* i_rtpcName, double i_rtpcValue)
{
    if (m_audioDriver)
        return m_audioDriver->SetRTPCValue(i_rtpcName, (float)i_rtpcValue);
    return false;
}

uint32 AudioMgr::SendEvent(const std::string& i_eventName, void* i_objectId)
{
    return SendEvent(i_eventName.c_str(), i_objectId);
}

void AudioMgr::SetListenerInternalPosition(const SexyVector2& i_position)
{
    m_internalListenerPosition = i_position;
}

void AudioMgr::Term()
{
    gLawnApp->mInteractiveSoundManager->Terminate();
    m_audioDriver = NULL;
}

uint32 AudioMgr::SendEventCallback(uint32 i_eventId, InteractiveAudioCallbackType i_callbackType, IInteractiveAudioCallbackListener* i_callbackFunction, void* i_objectId)
{
    if (m_audioDriver)
        return m_audioDriver->SendEventCallback(i_eventId, i_callbackType, i_callbackFunction, (AudioGameObjectId)i_objectId);
    return 0;
}

uint32 AudioMgr::SendEventCallback(const char* i_eventName, InteractiveAudioCallbackType i_callbackType, IInteractiveAudioCallbackListener* i_callbackFunction, void* i_objectId)
{
    uint32 id = 0;
    if (i_eventName != NULL && *i_eventName != '\0' && m_audioDriver)
        id = m_audioDriver->SendEventCallback(i_eventName, i_callbackType, i_callbackFunction, (AudioGameObjectId)i_objectId);
    return id;
}

uint32 AudioMgr::SendEventCallback(const std::string& i_eventName, InteractiveAudioCallbackType i_callbackType, IInteractiveAudioCallbackListener* i_callbackFunction, void* i_objectId)
{
    return SendEventCallback(i_eventName.c_str(), i_callbackType, i_callbackFunction, i_objectId);
}

void AudioMgr::SendPositionalAudioValue(void* i_objectId, const Sexy::SexyVector3& i_position)
{
    float dx = i_position.x - m_internalListenerPosition.x;
    if (dx <= 0.0f) {
        float c = ClampFloat(-dx * 0.0025f, 0.0f, 1.0f);
        SetRTPCValue("Panner_RTPC", (1.0f - c) * 50.0f, i_objectId);
        return;
    }
    float c = ClampFloat(dx * 0.0025f, 0.0f, 1.0f);
    SetRTPCValue("Panner_RTPC", (c + 1.0f) * 50.0f, i_objectId);
}

void AudioMgr::BroadcastCallbackMessages()
{
    uint32 data;
    bool ok;
    do {
        ok = ReadDataFromCallbackQueue(data);
        uint32 v = data;
        if (ok) {
            if (v == Sexy::IACT_MusicSyncBeat)
                gMessageRouter->Broadcast(Message::MusicBeatReceived);
            else if (v == Sexy::IACT_MusicSyncBar)
                gMessageRouter->Broadcast(Message::MusicBarReceived);
        }
    } while (ok);
}

uint32 AudioMgr::SendEventThrottled(const std::string& i_eventName, pvztime_t i_throttleTime, void* i_objectId)
{
    uint32 result;
    if (m_audioDriver == NULL) {
        result = 0;
    } else {
        std::map<const std::string, pvztime_t>::iterator it = m_throttledAudios.find(i_eventName);
        if (it != m_throttledAudios.end()) {
            pvztime_t now = PVZ_T();
            result = 0;
            if ((*it).second < now) {
                (*it).second = PVZ_T() + i_throttleTime;
                result = SendEvent((*it).first, i_objectId);
            }
        } else {
            m_throttledAudios[i_eventName] = PVZ_T() + i_throttleTime;
            result = SendEvent(i_eventName, i_objectId);
        }
    }
    return result;
}

void AudioMgr::Init()
{
    m_audioDriver = gLawnApp->mInteractiveAudioDriver;
    Sexy::InteractiveSoundManagerConfig config;
    config.mSfxVolumeParamName = "SFX_Volume_RTPC";
    config.mMusicVolumeParamName = "Music_Volume_RTPC";
    config.mLoadGroups.push_back("WiseAlwaysLoaded");
    for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_STREAMINGMUSIC); it; ++it) {
        StreamingMusicListPtr list = *it;
        for (std::vector<StreamingMusicGroup>::iterator group = list->groups.begin(); group != list->groups.end(); ++group) {
            config.mLoadIndexGroups.push_back((*group).groupName);
            for (std::vector<std::string>::iterator fileId = (*group).fileIds.begin(); fileId != (*group).fileIds.end(); ++fileId) {
                std::map<std::string, std::string>::iterator found = config.mFileIdToPathMap.find(*fileId);
                if (found != config.mFileIdToPathMap.end())
                    continue;
                config.mFileIdToPathMap[*fileId] = (*group).streamingPath + "/" + (*group).groupName;
            }
        }
    }
    gLawnApp->mInteractiveSoundManager->Initialize(config);
}
