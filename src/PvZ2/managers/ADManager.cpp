//
//  ADManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ADManager.h"
#include "GameEventMgr.h"
#include "LawnApp.h"
#include "Board.h"
#include "TGALogMgr.h"
#include "CustomLevelUtils.h"
#include "gameNetWork/PacketID.h"
#include "DNode/DNodeWidget.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

ADManager::~ADManager()
{
}

/////////////// Statics ///////////////

static std::map<ADType, int> sLocalToServerMap;
static std::map<ADType, ViewPositionType> sViewPositionMap;
static std::map<std::string, ADType> sNameToTypeMap;

/////////////// Helpers ///////////////

bool ADManager::isLocalReward(ADType i_type)
{
    return i_type == ADType_Reward_Sun;
}

bool ADManager::isCustomLevelAD(ADType i_type)
{
    return i_type >= ADType_CustomLevel_Mower && i_type <= ADType_CustomLevel_Sun;
}

int ADManager::LocalIdToServerId(ADType i_type)
{
    return sLocalToServerMap[i_type];
}

ViewPositionType ADManager::ToViewPositionType(ADType i_type)
{
    return sViewPositionMap[i_type];
}

void ADManager::SetADWatchCount(ADType i_type, int i_count)
{
    m_adMaps[i_type].WatchedTimes = i_count;
}

bool ADManager::HasADReward()
{
    return (m_currentADType == ADType_Reward_Sun) | (m_currentADType == 32) | (m_currentADType - ADType_Reward_Coin <= 2U) | (m_currentADType - ADType_Reward_ZTicket <= 1U);
}

void ADManager::TryRequestReward()
{
    if (isLocalReward(m_currentADType))
        RequestLocalReward();
    else
        RequestReward();
}

ADType ADManager::ServerIdToLocalId(int i_id)
{
    for (std::map<ADType, int>::iterator it = sLocalToServerMap.begin(); it != sLocalToServerMap.end(); ++it)
    {
        if (it->second == i_id)
            return it->first;
    }
    return ADType_None;
}

void ADManager::InitDefaultADMaps()
{
    m_adMaps.insert(std::make_pair(ADType_Reward_Sun, ADServerInfo(0, 3)));
}

int ADManager::GetADWatchCount(ADType i_type)
{
    std::map<ADType, ADServerInfo>::iterator it = m_adMaps.find(i_type);
    if (it != m_adMaps.end())
        return it->second.WatchedTimes;
    return 0;
}

int ADManager::GetLeftADWatchCount(ADType i_type)
{
    std::map<ADType, ADServerInfo>::iterator it = m_adMaps.find(i_type);
    if (it != m_adMaps.end())
        return it->second.MaxTimes - it->second.WatchedTimes;
    return 0;
}

bool ADManager::CanWatchAD(const std::string& i_type)
{
    return CanWatchAD(sNameToTypeMap[i_type]);
}

void ADManager::RequestLocalReward()
{
    if (m_currentADType == ADType_Reward_Sun)
    {
        gMessageRouter->Post(&Message::SunAdd, 500);
        gLawnApp->KillCoinStore();
        SetADWatchCount(ADType_Reward_Sun, GetADWatchCount(ADType_Reward_Sun) + 1);
    }
    gMessageRouter->Post(&Message::NotifyADWatchFinish, (int)m_currentADType);
}

bool ADManager::CanWatchAD(ADType i_type)
{
    std::string packageName = Android::Util::GetPackageName();
    if (i_type == ADType_DailySign || !gLawnApp->IsAdChannel(VIEW_TYPE_MEDIA_PARAM) || GetLeftADWatchCount(i_type) < 1)
        return false;
    return EASquared::Instance().IsMediaAvailable(ToViewPositionType(i_type));
}

void ADManager::InitADMaps(const std::vector<S2C_AdInfo>& i_infos)
{
    m_adMaps.clear();
    for (const S2C_AdInfo& info : i_infos)
        m_adMaps.insert(std::make_pair(ServerIdToLocalId(info.ServerId), ADServerInfo(info.WatchedTimes, info.MaxWatchedTimes)));
    InitDefaultADMaps();
}

void ADManager::RequestReward()
{
    std::map<std::string, std::string> params;
    params["id"] = DString(LocalIdToServerId(m_currentADType)).c_str();
    DNetwork* network = DNetwork::getInstance();
    _PacketId ids;
    network->requestMsg(ids.ID_REQUEST_AD_REWARD_INFO, params, 30.0f, [this](const std::string& i_response)
    {
    }, true, true, "[NET_CONNECTING]", 0);
}

void ADManager::ShowAD(ADType i_type)
{
    if (isCustomLevelAD(i_type))
    {
        TGACustomLevelADData data;
        data._step = "1";
        data._level = DString(CustomLevelUtils::GetLevelDetailsLevelID()).c_str();
        data._viewId = DString(ToViewPositionType(i_type)).c_str();
        data._viewType = "media";
        data._authorId = DString(CustomLevelUtils::GetLevelDetailsAuthorID()).c_str();
        TGALogMgr::GetInstance().LogCustomLevelAD(data);
    }
    SetCurrentADType(i_type);
    EASquared& ea = EASquared::Instance();
    ea.ShowAdvertisement("EA2World", Sexy::MakeDelegate(*this, &ADManager::onADFinished), true, VIEW_TYPE_MEDIA_PARAM, ToViewPositionType(i_type));
}

void ADManager::onADFinished(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason)
{
    bool isCustom = isCustomLevelAD(m_currentADType);
    switch (i_reason)
    {
    case EASquaredAdFinishedReason::Completed:
        if (isCustom)
        {
            TGACustomLevelADData data;
            data._step = "4";
            data._level = DString(CustomLevelUtils::GetLevelDetailsLevelID()).c_str();
            data._viewId = DString(ToViewPositionType(m_currentADType)).c_str();
            data._viewType = "media";
            data._authorId = DString(CustomLevelUtils::GetLevelDetailsAuthorID()).c_str();
            TGALogMgr::GetInstance().LogCustomLevelAD(data);
        }
        if (!HasADReward())
            gMessageRouter->Post(&Message::NotifyADWatchFinish, (int)m_currentADType);
        else
            TryRequestReward();
        break;
    case EASquaredAdFinishedReason::Clicked:
        if (isCustom)
        {
            TGACustomLevelADData data;
            data._step = "3";
            data._level = DString(CustomLevelUtils::GetLevelDetailsLevelID()).c_str();
            data._viewId = DString(ToViewPositionType(m_currentADType)).c_str();
            data._viewType = "media";
            data._authorId = DString(CustomLevelUtils::GetLevelDetailsAuthorID()).c_str();
            TGALogMgr::GetInstance().LogCustomLevelAD(data);
        }
        break;
    case EASquaredAdFinishedReason::Closed:
        if (isCustom)
        {
            TGACustomLevelADData data;
            data._step = "5";
            data._level = DString(CustomLevelUtils::GetLevelDetailsLevelID()).c_str();
            data._viewId = DString(ToViewPositionType(m_currentADType)).c_str();
            data._viewType = "media";
            data._authorId = DString(CustomLevelUtils::GetLevelDetailsAuthorID()).c_str();
            TGALogMgr::GetInstance().LogCustomLevelAD(data);
        }
        break;
    case EASquaredAdFinishedReason::Success:
        if (isCustom)
        {
            TGACustomLevelADData data;
            data._step = "2";
            data._level = DString(CustomLevelUtils::GetLevelDetailsLevelID()).c_str();
            data._viewId = DString(ToViewPositionType(m_currentADType)).c_str();
            data._viewType = "media";
            data._authorId = DString(CustomLevelUtils::GetLevelDetailsAuthorID()).c_str();
            TGALogMgr::GetInstance().LogCustomLevelAD(data);
        }
        break;
    case EASquaredAdFinishedReason::Canceled:
        if (isCustom)
        {
            TGACustomLevelADData data;
            data._step = "6";
            data._level = DString(CustomLevelUtils::GetLevelDetailsLevelID()).c_str();
            data._viewId = DString(ToViewPositionType(m_currentADType)).c_str();
            data._viewType = "media";
            data._authorId = DString(CustomLevelUtils::GetLevelDetailsAuthorID()).c_str();
            TGALogMgr::GetInstance().LogCustomLevelAD(data);
        }
        break;
    }
}

ADManager::ADManager()
    : m_currentADType(ADType_None)
{
}
