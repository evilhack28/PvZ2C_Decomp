//
//  WechatMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "WechatMgr.h"
#include "IWechat_Platform.h"
#include "LawnApp.h"

/////////////// WechatMgr ///////////////

WechatMgr::WechatMgr()
{
	m_wechat = NULL;
}

void WechatMgr::InitializeSDK()
{
	if (gLawnApp->GetPlatform() == PLATFORM_TELECOM_HUAWEI)
		return;
	if (gLawnApp->GetPlatform() == PLATFORM_TELECOM_ZHONGXING_HD)
		return;

	m_wechat = IWechatPlatform::CreateWechatPlatform();
	m_wechat->Initialize();
}

void WechatMgr::DoWechatShare(const std::string& i_url, bool toTimeLine)
{
	m_wechat->DoShare(i_url, toTimeLine);
}

bool WechatMgr::IsWechatInstalled()
{
	if (gLawnApp->GetPlatform() == PLATFORM_TELECOM_HUAWEI)
		return false;
	if (gLawnApp->GetPlatform() == PLATFORM_TELECOM_ZHONGXING_HD)
		return false;

	return m_wechat->IsWeChatInstalled();
}
