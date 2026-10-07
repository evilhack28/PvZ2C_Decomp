//
//  SocialShareMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SocialShareMgr.h"
#include "LawnApp.h"
#include "TGALogMgr.h"
#include "CustomLevelUtils.h"
#include "gameNetWork/PacketID.h"
#include "PVZ2UIDialog.h"
#include "PlatformInterface.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

void SocialShareMgr::Update()
{
}

SocialShareMgr::~SocialShareMgr()
{
}

SocialShareMgr::SocialShareMgr()
    : m_currentShareType(ShareType_None)
{
    m_requestSave = false;
    m_saving = false;
}

int SocialShareMgr::GetShareRewardCount(ShareType i_type)
{
    std::map<ShareType, int>::iterator it = m_shareInfoMaps.find(i_type);
    if (it != m_shareInfoMaps.end())
        return it->second;
    return 0;
}

void SocialShareMgr::SetShareRewardCount(ShareType i_type, int i_count)
{
    m_shareInfoMaps[i_type] = i_count;
}

bool SocialShareMgr::HasShareReward(ShareType i_type)
{
    return GetShareRewardCount(i_type) > 0;
}

void SocialShareMgr::saveResultDialogClose()
{
    gLawnApp->KillPVZ2Dialog();
    m_saving = false;
    gMessageRouter->Post(Message::NotifyShareSaveFinished);
}

void SocialShareMgr::saveScreenImageToLocal(ScreenInfo i_info)
{
    ShareDriverMgr::GetInstance().SaveScreenImageToLocal(i_info);
}

void SocialShareMgr::SaveScreenImageToLocal(int screenX, int screenY, int screenWidth, int screenHeight)
{
    gatherScreenInfo(screenX, screenY, screenWidth, screenHeight);
    saveScreenImageToLocal(m_currentScreenInfo);
}

void SocialShareMgr::ShareWithImage(SharePlatform i_platform, int screenX, int screenY, int screenWidth, int screenHeight)
{
    SaveScreenImageToLocal(screenX, screenY, screenWidth, screenHeight);
    if (!m_currentScreenInfo.ImagePath.empty())
        ShareDriverMgr::GetInstance().Share(i_platform, m_currentScreenInfo);
}

void SocialShareMgr::InitDefaultShareInfoMaps()
{
    m_shareInfoMaps.insert(std::make_pair(ShareType_DIY, 1));
    m_shareInfoMaps.insert(std::make_pair(ShareType_Invitation, 1));
}

void SocialShareMgr::InitShareInfoMaps(const std::vector<S2C_ShareInfo>& i_infos)
{
    m_shareInfoMaps.clear();
    std::vector<S2C_ShareInfo>::const_iterator it = i_infos.begin();
    std::vector<S2C_ShareInfo>::const_iterator end = i_infos.end();
    for (; it != end; ++it)
    {
        const S2C_ShareInfo& info = *it;
        m_shareInfoMaps.insert(std::make_pair((ShareType)info.ServerId, info.LeftTimes));
    }
}

void SocialShareMgr::SaveScreenImageToGallery(int screenX, int screenY, int screenWidth, int screenHeight)
{
    if (!m_saving)
    {
        m_saving = true;
        gMessageRouter->Post(Message::NotifyShareSaveBegin);
        SaveScreenImageToLocal(screenX, screenY, screenWidth, screenHeight);
        ShareDriverMgr::GetInstance().SaveScreenImageToGallery(m_currentScreenInfo);
        ShareDriverMgr::GetInstance().DeleteLocalImage(m_currentScreenInfo);
    }
}

void SocialShareMgr::SaveCallback(int i_result)
{
    SexyString title(L"[CUSTOM_LEVEL_LEVEL_DETAIL_SHARE_SAVE_GALLERY_TITLE]");
    SexyString text;
    if (i_result == SAVE_SUCCESS)
        text = L"[CUSTOM_LEVEL_LEVEL_DETAIL_SHARE_SAVE_GALLERY_SUCCESS]";
    else if (i_result == SAVE_FAILED)
        text = L"[CUSTOM_LEVEL_LEVEL_DETAIL_SHARE_SAVE_GALLERY_FAILED]";

    PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(title, text);
    dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &SocialShareMgr::saveResultDialogClose)));
}

static DString FormatTimeStamp(time_t i_time)
{
    tm* t = localtime(&i_time);
    DString result;
    result.format("%d-%02d-%02d-%02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    return result;
}

static const std::string s_shareImageName = "share_img";

void SocialShareMgr::gatherScreenInfo(int screenX, int screenY, int screenWidth, int screenHeight)
{
    std::string userDataDir = "";
    std::string externalDir = "";
    userDataDir = Android::Resources::GetUserDataFolder((Sexy::AndroidAppDriver*)gLawnApp);
    externalDir = Android::Resources::GetExternalFilesDirectory((Sexy::AndroidAppDriver*)gLawnApp);
    DString timeStr = FormatTimeStamp(time(NULL));
    std::string imagePath = externalDir + "/" + s_shareImageName + ".png";
    m_currentScreenInfo = ScreenInfo(screenX, screenY, screenWidth, screenHeight, imagePath);
}

void SocialShareMgr::RequestReward()
{
    std::map<std::string, std::string> params;
    if (m_currentShareType == ShareType_Invitation)
    {
        DNetwork* network = DNetwork::getInstance();
        network->requestMsg("V875", params, 30.0f, [this](const std::string& i_response)
        {
        }, true, true, "[NET_CONNECTING]", 0);
    }
    else
    {
        params["id"] = DString((int)m_currentShareType).c_str();
        DNetwork* network = DNetwork::getInstance();
        _PacketId ids;
        network->requestMsg(ids.ID_REQUEST_SHARE_REWARD_INFO, params, 30.0f, [this](const std::string& i_response)
        {
        }, true, true, "[NET_CONNECTING]", 0);
    }
}

void SocialShareMgr::shareResultDialogClose()
{
    gLawnApp->KillPVZ2Dialog();
    if (HasShareReward(m_currentShareType))
    {
        RequestReward();
    }
    else
    {
        std::string platform = TGALogMgr::GetInstance().GetSegForId(TGA_LOG_CUSTOM_LEVEL_SHARE, 0);
        TGACustomLevelShareData data;
        data._step = "4";
        data._result = "1";
        data._platform = platform;
        data._level = DString(CustomLevelUtils::GetLevelDetailsLevelID()).c_str();
        TGALogMgr::GetInstance().LogCustomLevelShare(data);
        TGALogMgr::GetInstance().clearSegments(TGA_LOG_CUSTOM_LEVEL_SHARE);
    }
}

void SocialShareMgr::ShareCallback(int i_result, const std::string& i_platform)
{
    SexyString title(L"[CUSTOM_LEVEL_LEVEL_DETAIL_SHARE_SHARE_TITLE]");
    SexyString text;
    PVZ2UIDialog* dialog;
    bool useClose = true;
    if (i_result == SHARE_SUCCESS)
    {
        text = L"[CUSTOM_LEVEL_LEVEL_DETAIL_SHARE_SHARE_SUCCESS]";
        TGALogMgr::GetInstance().LogSegments(TGA_LOG_CUSTOM_LEVEL_SHARE, 0, i_platform);
        dialog = gLawnApp->ShowPVZ2Dialog(title, text);
    }
    else
    {
        if (i_result == SHARE_FAILED)
            text = L"[CUSTOM_LEVEL_LEVEL_DETAIL_SHARE_SHARE_FAILED]";
        else if (i_result == SHARE_CANCELED)
            text = L"[CUSTOM_LEVEL_LEVEL_DETAIL_SHARE_SHARE_CANCELED]";
        {
            TGACustomLevelShareData data;
            data._step = "4";
            data._result = "0";
            data._platform = i_platform;
            data._level = DString(CustomLevelUtils::GetLevelDetailsLevelID()).c_str();
            TGALogMgr::GetInstance().LogCustomLevelShare(data);
        }
        dialog = gLawnApp->ShowPVZ2Dialog(title, text);
        useClose = m_currentShareType == ShareType_Invitation;
    }
    if (useClose)
        dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*this, &SocialShareMgr::shareResultDialogClose)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_SECONDARY);
    else
        dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::Delegate0(Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog)), PVZ2UIDialog::BUTTON_TYPE_GENERIC_SECONDARY);
}

static std::vector<std::string> s_shareCodes;

bool SocialShareMgr::HasShareCode(const std::string& i_packageName)
{
    return std::find(s_shareCodes.begin(), s_shareCodes.end(), i_packageName) == s_shareCodes.end();
}
